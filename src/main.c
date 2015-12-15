#include "routines.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timer.h"

#include <string.h>


//This task sends every 2 sec. message "Hello"
void vTaskSENDREAD(void *pvParameters){

	char mess[10] = "Hello=)\r\n";
	for(;;){
		for(uint32_t i=0; i < 10; i++){
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
			USART_SendData(USART1, mess[i]);
		}
		vTaskDelay(2000);
	}
}

//Following 2 tasks blinking LED1 and LED2
void vTaskLED1(void *pvParameters) {
        for (;;) {
                GPIOE->ODR = GPIO_Pin_12;
                vTaskDelay(1000);
                GPIOE->ODR = 0;
                vTaskDelay(1000);
        }
}

void vTaskLED2(void *pvParameters) {
        for (;;) {
                GPIOE->ODR = GPIO_Pin_11;
                vTaskDelay(80);
								GPIOE->ODR = 0;
                vTaskDelay(1000);
        }
}

void Init_ALL(void);



int main(void){

	init_ALL();
	xTaskCreate( vTaskLED1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 2,
	                        ( xTaskHandle * ) NULL);
	xTaskCreate( vTaskLED2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, 2,
	                        ( xTaskHandle * ) NULL);
	xTaskCreate( vTaskSENDREAD, ( signed char * ) "DD", 2*configMINIMAL_STACK_SIZE, NULL, 2,
		                        ( xTaskHandle * ) NULL);

	vTaskStartScheduler();


	return 0;
}
