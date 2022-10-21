/*
 * GPPIO_main.c
 *
 * Created: 18/09/2021 01:10:12 AM
 * Author : Toothless XII
 */ 

#include <avr/io.h>
#include "../../../../1- LIB/STD_types.h"
#include "../../../../1- LIB/BIT_math.h"
#include "../MCAL/GPIO_int.h"
#include <util/delay.h>



int main(void)
{
	MGPIO_void_SetPinDirection(GPIO_PORTB,0,GPIO_OUTPUT);
	
   
    while (1) 
    {
		MGPIO_void_SetPinValue(GPIO_PORTB,0,GPIO_HIGH);
		_delay_ms(100);
		MGPIO_void_SetPinValue(GPIO_PORTB,0,GPIO_LOW);
		_delay_ms(100);
		
    }
}

