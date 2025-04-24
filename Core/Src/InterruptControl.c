/*
 * InterruptControl.c
 *
 *  Created on: Feb 13, 2025
 *      Author: griff
 */

 #include <InterruptControl.h>

 void IRQ_en(uint8_t irq_num)
     {HAL_NVIC_EnableIRQ(irq_num);}
 
 void IRQ_dis(uint8_t irq_num)
     {HAL_NVIC_DisableIRQ(irq_num);}
 
 void IRQ_clr_PR(uint8_t irq_num)
     {HAL_NVIC_ClearPendingIRQ(irq_num);}
 
 void IRQ_set_PR(uint8_t irq_num)
     {HAL_NVIC_SetPendingIRQ(irq_num);}
 
 void IRQ_clr_EXTI(uint8_t pin)
     {EXTI->PR |= (CLR_EXTI << pin);}