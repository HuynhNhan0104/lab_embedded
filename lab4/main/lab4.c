#include <stdio.h>
#include <string.h>
// #include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

struct Data{
    char key[30];
    int value;
};

QueueHandle_t myqueue ;

    char message[100][255] = {"floor0:1","floor1:2","floor2:3", "floor3:4","floor4:5","floor5:6"};


void receptionTask(){
    char str[30];
    int x = 0;
    //read the message and send to the queue
    for (int i = 0; i < 100; i++) {

        if(strlen(message[i])!=0){
            sscanf(message[i],"%[^:]:%d", str, &x);
            struct  Data dataSending;
            strcpy(dataSending.key,str);
            dataSending.value = x;
            if(xQueueSendToBack(myqueue, &dataSending ,portMAX_DELAY ) != pdPASS  ){
                printf("SENDING DATA ERROR!");
            }
        }
            vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void taskA(){
    struct Data dataReceive = {0};
    while (1){
        if(xQueuePeek(myqueue, &dataReceive , portMAX_DELAY) != pdPASS ){
            printf("RECEIVE DATA ERROR!");
        }
        else{
            if(strcmp(dataReceive.key,"floor1")){
                xQueueReceive(myqueue, &dataReceive , portMAX_DELAY);
            }
            printf("key: %s, value: %d\n", dataReceive.key, dataReceive.value);

        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}
void taskB();
void taskC();


void app_main(void)
{
    myqueue = xQueueCreate (100,sizeof(struct Data));
    if(myqueue == NULL) printf("Memory is not enough \n");
    else printf("create a queue \n"); 
    xTaskCreate(receptionTask,"reception",2048,NULL,configMAX_PRIORITIES,NULL);
    xTaskCreate(taskA,"reception",2048,NULL,configMAX_PRIORITIES,NULL);
}
