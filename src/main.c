#include "routines.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"

#include "diag/Trace.h"

QueueHandle_t blink_mess_q;

//This task sends every 2 sec. message "Hello"
void vTaskSENDREAD(void *pvParameters){

	char mess[10] = "Hello=)\r\n";
	snprintf(mess, sizeof(mess), "Hello=)\r\n");
	send_str(mess);

	for(;;){
		if(uxQueueMessagesWaiting(blink_mess_q) > 0){
			int32_t rec_blk;
			xQueueReceive( blink_mess_q, &( rec_blk ), portMAX_DELAY);
			if(rec_blk > 0){
				char message[100];
				snprintf(message, sizeof(message), "PD12 blinked :%d times\r\n", rec_blk);
			} else{
				char message[100];
				snprintf(message, sizeof(message), "PD11 blinked :%d times\r\n", (rec_blk*(-1)));
				send_str(message);
			}
		}
		vTaskDelay(20);
	}
}

SemaphoreHandle_t xBlinkMTX;
//Following 2 tasks blinking LED1 and LED2
void vTaskLED1(void *pvParameters) {
	int32_t blink_cnt = 0;
        for (;;) {

							GPIO_SetBits(GPIOE, GPIO_Pin_12);
              vTaskDelay(1000);
          		GPIO_ResetBits(GPIOE, GPIO_Pin_12);
              vTaskDelay(1000);
    	  	xSemaphoreTake( xBlinkMTX, portMAX_DELAY);
							blink_cnt--;
					xQueueSend(blink_mess_q, ( void * ) &blink_cnt, portMAX_DELAY);
					xSemaphoreGive(xBlinkMTX);

        }
}

void vTaskLED2(void *pvParameters) {
	int32_t blink_cnt = 0;
        for (;;) {

						GPIO_SetBits(GPIOE, GPIO_Pin_11);
	          vTaskDelay(80);
	          GPIO_ResetBits(GPIOE, GPIO_Pin_11);
	          vTaskDelay(1000);
	    xSemaphoreTake( xBlinkMTX, portMAX_DELAY);
	          blink_cnt++;
			xQueueSend(blink_mess_q, ( void * ) &blink_cnt, portMAX_DELAY);
			xSemaphoreGive(xBlinkMTX);

        }
}


int main(void){

	init_ALL();
	trace_puts("Hello we are initializing our periph");

	//Initializing queue
	blink_mess_q = xQueueCreate(10, sizeof(int32_t));

	//Initializing mutex
	xBlinkMTX	= xSemaphoreCreateMutex();

	xTaskCreate( vTaskLED1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 2,
	                        ( xTaskHandle * ) NULL);
	xTaskCreate( vTaskLED2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, 2,
	                        ( xTaskHandle * ) NULL);
	xTaskCreate( vTaskSENDREAD, ( signed char * ) "DD", 2*configMINIMAL_STACK_SIZE, NULL, 2,
		                        ( xTaskHandle * ) NULL);

	vTaskStartScheduler();


	return 0;
}
