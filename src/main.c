#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_usart.h"

#include "FreeRTOS.h"
#include "task.h"

#include <string.h>


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

void vTaskLED1(void *pvParameters) {
        for (;;) {
                GPIO_SetBits(GPIOE, GPIO_Pin_12);
                vTaskDelay(1000);
                GPIO_ResetBits(GPIOE, GPIO_Pin_12);
                vTaskDelay(1000);
        }
}

void vTaskLED2(void *pvParameters) {
        for (;;) {
                GPIO_SetBits(GPIOE, GPIO_Pin_11);
                vTaskDelay(80);
                GPIO_ResetBits(GPIOE, GPIO_Pin_11);
                vTaskDelay(80);
        }
}

void Init_ALL(void);



int main(void){

	Init_ALL();
	xTaskCreate( vTaskLED1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 2,
	                        ( xTaskHandle * ) NULL);
	xTaskCreate( vTaskLED2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, 2,
	                        ( xTaskHandle * ) NULL);
	xTaskCreate( vTaskSENDREAD, ( signed char * ) "DD", 2*configMINIMAL_STACK_SIZE, NULL, 2,
		                        ( xTaskHandle * ) NULL);

	vTaskStartScheduler();


	return 0;
}

void Init_ALL(void){

	// Enable GPIO Peripheral clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
	// RCC->APB2RSTR = RCC_APB2Periph_USART1;

	GPIO_InitTypeDef GPIO_InitStructure,sec;
	USART_InitTypeDef myUsart;

	// Configure pin in output push/pull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);


	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
	sec.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	sec.GPIO_Speed = GPIO_Speed_50MHz;
	sec.GPIO_Mode = GPIO_Mode_AF;
	sec.GPIO_OType = GPIO_OType_PP;
	sec.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &sec);

	myUsart.USART_BaudRate = 115200;
	myUsart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	myUsart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	myUsart.USART_Parity = USART_Parity_No;
	myUsart.USART_StopBits = USART_StopBits_1;
	myUsart.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART1, &myUsart);
	USART_Cmd(USART1, ENABLE);

}


