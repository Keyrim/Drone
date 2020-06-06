/*
 * esc.c
 *
 *  Created on: 16 mars 2020
 *      Author: Theo
 */
#include "esc.h"

uint32_t duty_from_position(uint16_t position);

//Le servo accepte des positions allant de 500 (0 degr�) � 2500 (180 degr�)
uint32_t duty_from_position(uint16_t position){
	uint32_t duty = position ;							//On recupere le temps a l'etat haut de notre signal
	duty = MIN(2500, position);
	duty = MAX(500, position);
	duty = duty * 100 ;
	duty = duty / PERIODE_PWM ;		//On obtient le rapport cyclique en divisant par la p�riode du signal
	return duty ;
}

/*
 * @brief Cette fonction configure le pin sur lequel le servo pass� en param�tre est branch�
 */
void ESC_init(Esc_e * esc, GPIO_TypeDef GPIOx, uint32_t GPIO_Pin, timer_id_e timer_id, uint16_t timer_chanel, uint16_t position){
	//Configure tous les param�tres dans la struct
	esc->GPIOx = GPIOx ;
	esc->GPIO_Pin = GPIO_Pin ;
	esc->position = position ;
	esc->timer_chanel = timer_chanel ;
	esc->timer_id = timer_id ;
	//Configure le pin et le pwm
	BSP_GPIO_PinCfg(esc->GPIOx, esc->GPIO_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	PWM_run(esc->timer_id, esc->timer_chanel, FALSE, PERIODE_PWM, duty_from_position(esc->position),  FALSE);

}

/*
 * @brief Cette fonction change le duty de la pwm associ� au servo pass� en param�tre
 */
void ESC_set_position(Esc_e esc){
	PWM_set_duty(esc.timer_id, esc.timer_chanel, duty_from_position(esc.position));
}
