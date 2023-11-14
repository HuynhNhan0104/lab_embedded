#include <stdio.h>
// #include ""
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
// #ifdef configUSE_TIME_SLICING
//     #undef configUSE_TIME_SLICING
//     #define configUSE_TIME_SLICING 0
// #endif
long unsigned int buf1 = 0, buf2 = 0, buf3 = 0;


void task1(){
    while (1){
        printf("task 1 is running at: %lu, on core %d\n",xTaskGetTickCount(), xPortGetCoreID());
        for(int i = 0; i < 1000000; i++) buf1++;
        // taskYIELD();
        // vTaskDelay(pdMS_TO_TICKS(1));
    }
    
}

void task2(){
    while (1){
        printf("task 2 is running at: %lu, on core %d\n",xTaskGetTickCount(), xPortGetCoreID());
        for(int i = 0; i < 1000000; i++) buf2++;

        // vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void task3(){
    while (1){
        printf("task 3 is running at: %lu, on core %d\n",xTaskGetTickCount(), xPortGetCoreID());
        for(int i = 0; i < 1000000; i++) buf3++;
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    
}

void preemptiveAndTimeSliding(){
    printf("time slicing: %u\n", configUSE_TIME_SLICING);
    xTaskCreate(task1, "Task1", 2048, NULL, 0, NULL);
    xTaskCreate(task2, "Task2", 2048, NULL, 0, NULL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    xTaskCreate(task3, "Task3", 2048, NULL, 5, NULL);
}
// void preemptiveAndTimeSliding(){

// }
// void cooperative(){

// }



void app_main(void)
{
    preemptiveAndTimeSliding();


    // task1();
    
}
