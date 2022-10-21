/*
 * EXTI_Driver.c
 *
 * Created: 19/09/2021 04:05:28 PM
 * Author : Toothless XII
 */ 

#include "STD_types.h"
#include "BIT_math.h"
#include "../MCAL/EXTI_Driver/EXTI_int.h"
#include "../MCAL/INTERRUPTS_Driver/INTERRUPT.h"
#include "../MCAL/GPIO_Driver/GPIO_int.h"

#include <util/delay.h>

void Toggle_LED1 (void);
void Toggle_LED2 (void);
void Toggle_LED3 (void);


int main(void)
{
	
	
	MGPIO_void_SetPinDirection (GPIO_PORTD, 5,GPIO_OUTPUT);
	MGPIO_void_SetPinDirection (GPIO_PORTC, 5,GPIO_OUTPUT);
	MGPIO_void_SetPinDirection (GPIO_PORTB, 2,GPIO_OUTPUT);
	MGPIO_void_SetPinDirection (GPIO_PORTD, 2,GPIO_INPUT_PULLUP);
	MGPIO_void_SetPinDirection (GPIO_PORTD, 3,GPIO_INPUT_PULLUP);
	MGPIO_void_SetPinDirection (GPIO_PORTB, 6,GPIO_INPUT_PULLUP);
	
	MEXTI_void_EnableInterrupt(EXTI_0);
	MEXTI_void_EnableInterrupt(EXTI_1);
	MEXTI_void_EnableInterrupt(PCINT_0);
	MEXTI_void_SetPC_Pin(6, EXTI_PC_PIN_ENABLE);
	
	MEXTI_void_SetTrigger(EXTI_0,TRIGGER_LOGICAL_CHANGE);
	MEXTI_void_SetTrigger(EXTI_1,TRIGGER_LOGICAL_CHANGE);
	
	MEXTI_void_SetCallBack(EXTI_0,Toggle_LED1);
	MEXTI_void_SetCallBack(EXTI_1,Toggle_LED2);
	MEXTI_void_SetCallBack(PCINT_0,Toggle_LED3);  
	 
    while (1) 
    {
		
    }
}

void Toggle_LED1 (void)
{
	MGPIO_void_TogglePin (GPIO_PORTD, 5);
}
void Toggle_LED2 (void)
{
	MGPIO_void_TogglePin (GPIO_PORTC, 5);
}
void Toggle_LED3 (void)
{
	MGPIO_void_TogglePin (GPIO_PORTB, 2);
}


