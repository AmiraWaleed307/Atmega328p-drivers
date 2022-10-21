/*
 * Timers_Driver.c
 *
 * Created: 30/09/2021 01:03:04 AM
 * Author : Toothless XII
 */ 

#include "../../../../1- LIB/STD_types.h"
#include "../../../../1- LIB/BIT_math.h"
#include "../MCAL/Clock_Driver/CLOCK_interface.h"
#include "../MCAL/GPIO_Driver/GPIO_int.h"
#include "../MCAL/GPIO_Driver/GPIO_int.h"
#include "../MCAL/INTERRUPTS_Driver/INTERRUPT.h"
#include "../MCAL/Timers_Driver/TIM_int.h"


void Toggle_LED (void)
{
	MGPIO_void_TogglePin(GPIO_PORTB,0);
}
void Toggle_LED2 (void)
{
	MGPIO_void_TogglePin(GPIO_PORTB,1);
}
int main(void)
{
    MGPIO_void_SetPinDirection(GPIO_PORTB,0,GPIO_OUTPUT);
	MGPIO_void_SetPinDirection(GPIO_PORTB,1,GPIO_OUTPUT);
    MGPIO_void_SetPinDirection(GPIO_PORTD,5,GPIO_OUTPUT);
    MGPIO_void_SetPinDirection(GPIO_PORTD,6,GPIO_OUTPUT);

	MTIM8_void_initialize (TIM0, TIM_FAST_PWM, TIM_FAST_PWM_NON_INVERTING,TIM_FAST_PWM_INVERTING,TIM_CS_1024_PRESCALER);
	//MTIM8_void_CTCSetFrequency(TIM0,1000);  //128

	//MTIM8_void_CTCSetFrequency(TIM0,TIM_CHANNEL_A,488); //51
	
	MTIM8_void_SetDutyCycle(TIM0,TIM_CHANNEL_A,100);
	MTIM8_void_SetDutyCycle(TIM0,TIM_CHANNEL_B,50);
	
	//MTIM8_void_initialize (TIM2, TIM_NORMAL_MODE, 0,0,TIM_CS_256_PRESCALER);

	MTIM8_void_SetPeriodicFunction (TIM0,1000000,Toggle_LED);
//	MTIM8_void_SetPeriodicFunction (TIM2,1000000,Toggle_LED2);

//	MTIM8_void_StopTimer(TIM0);
//	MTIM8_void_StopTimer(TIM2);

//	MTIM8_void_StartTimer(TIM2,0);

	//MTIM8_void_EnableInterrupt(TIM2,TIM_OVF_INTERRUPT);
	//MTIM8_void_SetCallBack(TIM2,TIM_OVF_INTERRUPT,&Toggle_LED);
    while (1) 
    {
    }
}

