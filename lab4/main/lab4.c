#include <stdio.h>
#include <string.h>
// #include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "sdkconfig.h"


//  source message
char message[100][255] = {
    "house1:lamp0:1","house1:lamp1:0","house1:lamp2:1", "house1:fan2:30","house1:fan1:70","house1:fan0:60",
    "house2:lamp2:1","house2:fan1:50","house2:fan2:0", "house2:fan0:100","house2:lamp1:1","house2:lamp0:1",
    "house7:lamp1:0",
    "house0:lamp1:0","house0:lamp2:1","house0:fan2:50", "house0:lamp0:0","house0:fan1:80","house0:fan0:100",
    "house4:lamp1:0"
};

QueueHandle_t myqueue;
struct Data{
    int houseId;
    char equipmentName [30];
    int equipmentId;
    int value;
};
/**
 * @brief task rececpt message and send it to the control node
 * 
 */

void receptionTask(){
    int houseId = 0;
    char equipmentName [30];
    int equipmentId = 0;
    int value = 0;
    //read the message and send to the queue
    for (int i = 0; i < 100; i++) {

        if(strlen(message[i])!=0){
            // message with format "housei:equipmentj:value" will be split to 
            // houseId = i, equipmentName = equipmentName, equipmentId = j,  value = value
            sscanf(message[i],"house%d:%[^0-9]%d:%d", &houseId,equipmentName,&equipmentId, &value);
            // printf("%d %s %d %d \n", houseId,equipmentName,equipmentId, value);
            struct  Data dataSending = {
                .houseId = houseId,
                .equipmentId = equipmentId,
                .value = value,
            };
            strcpy(dataSending.equipmentName,equipmentName);
            // create data to data sending
            
            if(xQueueSendToBack(myqueue, &dataSending ,portMAX_DELAY ) != pdPASS  ){
                printf("SENDING DATA ERROR!");
            }
        }
            vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}


void set_equipment(char equipmentName [30],int equipmentId,int value){
    printf("the %s %d ",equipmentName,equipmentId);
    if(strcmp(equipmentName,"fan") == 0) 
        printf("is setting to %d \n",value);
    else if (strcmp(equipmentName,"lamp") == 0) 
        printf("is turning %s \n", value ? "on": "off");
    else printf("ERROR\n");
}


bool checkRecievedHouse0 = true;
void house0Controller(){
    struct Data dataReceive = {0};
    while (1){
        if(xQueuePeek(myqueue, &dataReceive , portMAX_DELAY) != pdPASS ){
            printf("RECEIVE DATA ERROR!");
        }
        else{
            if(dataReceive.houseId == 0){
                checkRecievedHouse0 = true;
                printf("in house %d: ", dataReceive.houseId);
                xQueueReceive(myqueue, &dataReceive , portMAX_DELAY);
                set_equipment(dataReceive.equipmentName,dataReceive.equipmentId,dataReceive.value);
            }
            else checkRecievedHouse0 = false;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

bool checkRecievedHouse1 = true;
void house1Controller(){
    struct Data dataReceive = {0};
    while (1){
        if(xQueuePeek(myqueue, &dataReceive , portMAX_DELAY) != pdPASS ){
            printf("RECEIVE DATA ERROR!");
        }
        else{
            if(dataReceive.houseId == 1){
                checkRecievedHouse1 = true;
                printf("in house %d: ", dataReceive.houseId);
                xQueueReceive(myqueue, &dataReceive , portMAX_DELAY);
                set_equipment(dataReceive.equipmentName,dataReceive.equipmentId,dataReceive.value);
            }
            else checkRecievedHouse1 = false;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

bool checkRecievedHouse2 = true;
void house2Controller(){
    struct Data dataReceive = {0};
    while (1){
        if(xQueuePeek(myqueue, &dataReceive , portMAX_DELAY) != pdPASS ){
            printf("RECEIVE DATA ERROR!");
        }
        else{
            if(dataReceive.houseId == 2){
                checkRecievedHouse2 = true;
                printf("in house %d: ", dataReceive.houseId);
                xQueueReceive(myqueue, &dataReceive , portMAX_DELAY);
                set_equipment(dataReceive.equipmentName, dataReceive.equipmentId, dataReceive.value);
            }
            else checkRecievedHouse2 = false;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void watchingNoTaskHandleRequest(){
    while(1) {
        if(!(checkRecievedHouse0 | checkRecievedHouse1 | checkRecievedHouse2) ){
            printf("ERROR: No task received\n");
            checkRecievedHouse0 = true;
            checkRecievedHouse1 = true;
            checkRecievedHouse2 = true;
            struct Data dataReceive = {0};
            xQueueReceive(myqueue, &dataReceive , portMAX_DELAY);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    myqueue = xQueueCreate (100,sizeof(struct Data));
    if(myqueue == NULL) printf("Memory is not enough \n");
    else printf("create a queue \n"); 
    xTaskCreate(receptionTask,"reception",2048,NULL,configMAX_PRIORITIES,NULL);
    xTaskCreate(house0Controller,"house1",2048,NULL,configMAX_PRIORITIES,NULL);
    xTaskCreate(house1Controller,"house2",2048,NULL,configMAX_PRIORITIES,NULL);
    xTaskCreate(house2Controller,"house3",2048,NULL,configMAX_PRIORITIES,NULL);
    xTaskCreate(watchingNoTaskHandleRequest,"hanlde error",2048,NULL,configMAX_PRIORITIES,NULL);

    while(1){
        vTaskDelay(1000);
    }
    
}
    