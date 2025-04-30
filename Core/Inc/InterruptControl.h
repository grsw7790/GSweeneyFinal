/*
 * Interrupt_Control.h
 *
 *  Created on: Feb 13, 2025
 *      Author: griff
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_
 
#include "stdint.h"
#include "stm32f4xx_hal.h"
 
#define EXTI0_IRQ_NUMBER 	6
#define CLR_EXTI 			1
 
void IRQ_en(uint8_t irq_num);
void IRQ_dis(uint8_t irq_num);
void IRQ_clr_PR(uint8_t irq_num);
void IRQ_set_PR(uint8_t irq_num);
void IRQ_clr_EXTI(uint8_t pin);
 
#endif /* INTERRUPTCONTROL_H_ */