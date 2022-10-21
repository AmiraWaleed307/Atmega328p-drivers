/*
 * ADC_Driver.c
 *
 * Created: 20/09/2021 09:57:26 PM
 * Author : Toothless XII
 */ 

#include "../../../../1- LIB/STD_types.h"
#include "../../../../1- LIB/BIT_math.h"
#include "../MCAL/GPIO_Driver/GPIO_int.h"
#include "../MCAL/EXTI_Driver/EXTI_int.h"
#include "../MCAL/ADC_Driver/ADC_int.h"
#include "../MCAL/Clock_Driver/CLOCK_interface.h"
#include "../HAL/LCD_Driver/LCD_interface.h"

void WriteOnLCD (u16 Value);
LCD_t X;

int main(void)
{
	MEXTI_void_EnableInterrupt(EXTI_0);
	MGPIO_void_SetPinDirection (GPIO_PORTD,2,GPIO_INPUT_PULLUP);
	MEXTI_void_SetTrigger(EXTI_0,TRIGGER_FALLING_EDGE);
	
	//u16 ADC_Val=0;
	MGPIO_void_SetPinDirection(GPIO_PORTC,0,GPIO_INPUT);
	MADC_void_Initialize(ADC_MODE_CONTINOUS_CONVERSION,ADC_AREF,ACD_128_PRE,ADC_10BIT);
	MADC_void_SetAutoTriggerSource (ADC_EXTI0);
	MADC_void_ReadChannelAsynch (ADC_0, WriteOnLCD );
	
	
	//MADC_void_DisableDigitalInputBuffer (ADC_0);
	//MADC_void_EnableDigitalInputBuffer (ADC_0);
    
	u8 Data_Pins[4] = {3,4,5,6};
	enum GPIOPORT_t Data_Ports [4] = {GPIO_PORTB,GPIO_PORTB,GPIO_PORTB,GPIO_PORTB};
	X.Mode = LCD_MODE_4_BIT;
	X.Size [0] = 2;
	X.Size [1] = 16;
	X.ControlPins [0] = 0;
	X.ControlPins [1] = 1;  
	X.ControlPins [2] = 2;
	X.ControlPorts [0] = GPIO_PORTB;
	X.ControlPorts [1] = GPIO_PORTB;
	X.ControlPorts [2] = GPIO_PORTB;
	X.DataPins = Data_Pins;
	X.DataPorts = Data_Ports;
	
	HLCD_voidInit(&X);
	MADC_void_StartContinousMode();
// 	MCLOCK_voidDelayMS(1000);
// 	HLCD_voidClearScreen(&X);
// 	MCLOCK_voidDelayMS(1000);
// 	HLCD_voidWriteNumber(&X,475,10);
	
//	MADC_void_StopContinousMode();
	
    while (1) 
    {
		
		
		
    }
	
}

void WriteOnLCD (u16 Value)
{
	    //ADC_Val = MADC_u16_ReadChannelSynch(ADC_0);
		Value = ((float)Value) *5000/1023;
		HLCD_voidWriteNumber(&X,Value,10);
		HLCD_voidWriteString (&X,"mV ");
		//HLCD_voidWriteNumber(&X,MGPIO_u8_GetPinValue(GPIO_PORTC,0),10);
		//HLCD_voidWriteString (&X," Dis_Buff");
		MCLOCK_voidDelayMS(1000);
		HLCD_voidClearScreen(&X);

}

