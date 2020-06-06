/*
 * esc.h
 *
 *  Created on: 16 mars 2020
 *      Author: Theo
 */

#ifndef ESC_H_
#define ESC_H_

#include "stm32f1_pwm.h"

#define PERIODE_PWM 4000

typedef struct {
	uint16_t 		position ;
	timer_id_e 		timer_id;
	uint16_t		timer_chanel;
	GPIO_TypeDef 	GPIOx;
	uint32_t 		GPIO_Pin;
}Esc_e;

void ESC_Init(Esc_e * esc);

void ESC_set_position(Esc_e esc);

#endif /* ESC_H_ */
