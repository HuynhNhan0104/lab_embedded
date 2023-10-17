#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_timer.h"

#define BUTTON_RELEASED  1
#define BUTTON_PRESSED   0

/**
 * @brief config GPIO of program with io 19 is button, io2 is config led on board
 * 
 */
int toggle = 1;
void config_IO(){
    gpio_set_direction ( GPIO_NUM_19 , GPIO_MODE_INPUT );
    gpio_set_pull_mode ( GPIO_NUM_19, GPIO_PULLUP_ONLY);
    gpio_set_direction ( GPIO_NUM_2 , GPIO_MODE_OUTPUT );
    gpio_set_level (GPIO_NUM_2, 0);

}


/**
 * @brief print studen identify every 1 second 
 * 
 */

void print_mssv(){
    while (1)
    {
        printf("2013961 \n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
}



/**
 * @brief read unbounded button input signal from button and print "ESP32"
 * 
 */
int register_key3 = BUTTON_RELEASED,  register_key2 = BUTTON_RELEASED, register_key1 = BUTTON_RELEASED;
int register_key0 = BUTTON_RELEASED; 
void read_input(){
    while (1)
    {
        register_key3 = register_key2;
        register_key2 = register_key1;
        register_key1 = register_key0;
        register_key0 = gpio_get_level(GPIO_NUM_19);
        //prevent noise 
        if(register_key3 == register_key2 && register_key2 == register_key1){
            // when button change from hign to low or low to high
            if(register_key0 != register_key1){
                //just process when button is pressed(high to low)
                if(register_key0 == BUTTON_PRESSED ){ 
                    printf("ESP32 \n");
                    gpio_set_level(GPIO_NUM_2, toggle);
                    toggle = 1 - toggle;
                }
            }


        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
}


void app_main(void)
{
    
    config_IO();
    
    xTaskCreate(print_mssv,"print mssv",1024,NULL,configMAX_PRIORITIES,NULL);
    xTaskCreate(read_input,"read signal button",1024,NULL,configMAX_PRIORITIES,NULL);
       

}
