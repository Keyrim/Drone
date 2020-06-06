/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
//#include "esc.h"

#define PERIODE_LOOP 	4

static volatile uint16_t TIME_loop = PERIODE_LOOP ;

void process_ms(void)
{
	if(TIME_loop){

	}

}



int main(void)
{
	//Init des trucs
	HAL_Init();

	//Init la liaison série pour le débug
	UART_init(UART1_ID,115200);
	SYS_set_std_usart(UART1_ID, UART1_ID, UART1_ID);

	//Init servo moteur
	//Esc_e escs[4] ;
//	Esc_init(&escs[0], GPIOA, GPIO_PIN_8, TIMER1_ID, TIM_CHANNEL_1, 1000);
//	Esc_init(&escs[1], GPIOB, GPIO_PIN_8, TIMER4_ID, TIM_CHANNEL_3, 1000);
//	Esc_init(&escs[2], GPIOA, GPIO_PIN_6, TIMER3_ID, TIM_CHANNEL_1, 1000);
//	Esc_init(&escs[3], GPIOA, GPIO_PIN_1, TIMER2_ID, TIM_CHANNEL_2, 1000);



	//BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);
	//BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//Ajoute la fonction process_ms aux fonction appelées toutes les ms
	Systick_add_callback_function(&process_ms);



	while(1)	//boucle de tâche de fond
	{

	}
}
