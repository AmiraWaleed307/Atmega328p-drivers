

#include "../../../../../1- LIB/STD_types.h"
#include "../../../../../1- LIB/BIT_math.h"
#include "../../MCAL/GPIO_Driver/GPIO_int.h"
#include "../../MCAL/Clock_Driver/CLOCK_interface.h"
#include <stdio.h>


#include "LCD_interface.h"
#include "LCD_private.h"



void PLCD_voidWrite8Bits(LCD_t* LCD, u8 Byte){
	for(u8 i = 0 ; i < 8 ; i++){
		MGPIO_void_SetPinValue(LCD->DataPorts[i],LCD->DataPins[i],GET_BIT(Byte,i));
	}
	PLCD_voidEnable(LCD);
}

void PLCD_voidWrite4Bits(LCD_t* LCD, u8 HalfByte){
	for(u8 i = 0 ; i < 4 ; i++){
		MGPIO_void_SetPinValue(LCD->DataPorts[i],LCD->DataPins[i],GET_BIT(HalfByte,i));
	}
	PLCD_voidEnable(LCD);
}


void PLCD_voidEnable(LCD_t* LCD){
	MGPIO_void_SetPinValue(LCD->ControlPorts[2],LCD->ControlPins[2],GPIO_HIGH);
	MCLOCK_voidDelayMS(2);

	MGPIO_void_SetPinValue(LCD->ControlPorts[2],LCD->ControlPins[2],GPIO_LOW);
	MCLOCK_voidDelayMS(2);

}


void PLCD_voidSetReadMode(LCD_t* LCD){
	
	u8 Local_u8Pins = LCD->Mode == LCD_MODE_4_BIT?	4:8;
	for(u8 i = 0; i < Local_u8Pins ; i++)
		MGPIO_void_SetPinDirection(LCD->DataPorts[i],LCD->DataPins[i],GPIO_INPUT);
}

void PLCD_voidSetWriteMode(LCD_t* LCD){
	
	u8 Local_u8Pins = LCD->Mode == LCD_MODE_4_BIT?	4:8;
	for(u8 i = 0; i < Local_u8Pins ; i++)
	MGPIO_void_SetPinDirection(LCD->DataPorts[i],LCD->DataPins[i],GPIO_OUTPUT);
	
}

void PLCD_voidWaitForBusyFlag(LCD_t* LCD){
	
	u8 Local_u8BusyFlag = 1;
	u8 Local_u8DB7 = LCD->Mode == LCD_MODE_4_BIT? 3:7;
	PLCD_voidSetReadMode(LCD);
	
	LCD_RS_LOW(LCD);
	LCD_RW_HIGH(LCD);
	while(Local_u8BusyFlag);
	Local_u8BusyFlag = MGPIO_u8_GetPinValue(LCD->ControlPorts[Local_u8DB7],LCD->ControlPins[Local_u8DB7]);
	
	PLCD_voidSetWriteMode(LCD);
	LCD_RS_LOW(LCD);
	LCD_RW_LOW(LCD);
	
	//return Local_u8BusyFlag;
}

void PLCD_voidWriteCommand(LCD_t* LCD, u8 Command){
	
	LCD_RS_LOW(LCD);
	LCD_RW_LOW(LCD);
	
	if(LCD->Mode == LCD_MODE_8_BIT){
		PLCD_voidWrite8Bits(LCD,Command);
	}
	else{
		PLCD_voidWrite4Bits(LCD,Command>>4);
		PLCD_voidWrite4Bits(LCD,Command&0xF);
	}


	
}

void PLCD_voidWriteData(LCD_t* LCD, u8 Data){
	
	LCD_RS_HIGH(LCD);
	LCD_RW_LOW(LCD);
	
	if(LCD->Mode == LCD_MODE_8_BIT){
		PLCD_voidWrite8Bits(LCD,Data);	
	}
	else{
		PLCD_voidWrite4Bits(LCD,Data>>4);
		PLCD_voidWrite4Bits(LCD,Data&0xF);
	}	
}


//Initializes the LCD with the set values in LCD pointer
void HLCD_voidInit(LCD_t* LCD){
	
	u8 Local_u8Pins = LCD->Mode == LCD_MODE_4_BIT?	4:8;
	u8 Local_u8Lines = LCD->Size[0] > 1? 1:0;
	u8 Local_u8DataLine = LCD->Mode == LCD_MODE_4_BIT?	0:1;
	//Pins' Direction as output
	for(u8 i = 0; i< 3; i++){
		MGPIO_void_SetPinDirection(LCD->ControlPorts[i],LCD->ControlPins[i],GPIO_OUTPUT);
	}
	for(u8 i = 0; i< Local_u8Pins; i++){
		MGPIO_void_SetPinDirection(LCD->DataPorts[i],LCD->DataPins[i],GPIO_OUTPUT);
	}
	MCLOCK_voidDelayMS(50);

	if(Local_u8DataLine == 0)
		PLCD_voidWrite4Bits(LCD,(LCD_INSTRUCTION_FUNCTION_SET(Local_u8DataLine,Local_u8Lines,0))>>4);
	
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_FUNCTION_SET(Local_u8DataLine,Local_u8Lines,0));
	
	MCLOCK_voidDelayMS(1);
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_DISP_ON_OFF_CTRL(1,0,0));
	
	MCLOCK_voidDelayMS(1);
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_CLR_DISPLAY);
	
	MCLOCK_voidDelayMS(5);
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_ENTRY_MODE_SET(1,0));
}

//Writes a single char to LCD
void HLCD_voidWriteChar(LCD_t* LCD,char c){
	PLCD_voidWriteData(LCD,c);
}

//Writes a string to the LCD starting from the current cursor position
void HLCD_voidWriteString(LCD_t* LCD, char* string){
	
	u8 i = 0, c = 0;
	while(*string){
		PLCD_voidWriteData(LCD,*string++);
		i++;
		if(i >= LCD->Size[1]){
			HLCD_voidSetPosition(LCD,0,++c);
			i = 0;
		}
	}
}

//Writes an Array to the LCD starting from the current cursor position
void HLCD_voidWriteArray(LCD_t* LCD, u8* Array, u8 Len){
	u8 i = 0,c = 0;
	while(Len--){
		PLCD_voidWriteData(LCD,*Array++);
		i++;
		if(i >= LCD->Size[1]){
			i = 0;
			HLCD_voidSetPosition(LCD,0,++c);
		}
	}
}

//Writes an Integer number to the LCD starting from the current cursor position
void HLCD_voidWriteNumber(LCD_t* LCD, s32 Number, u8 Basis){
	
	s8 Array[20];
	if(Basis == 10)
		sprintf(Array,"%ld",Number);
	else if(Basis == 8)
		sprintf(Array,"%lo",Number);
	else if (Basis == 16)
		sprintf(Array,"%lX",Number);
	HLCD_voidWriteString(LCD,Array);
}



//Sets the Cursor Position
void HLCD_voidSetPosition(LCD_t* LCD,u8 x_position, u8 y_position){
	
	if(y_position > 3)
		return;
	u8 Local_u8Position = x_position+PYPositions[y_position];
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_SET_DDRAM_ADDR(Local_u8Position));
}

//Clears the Display, and returns the Cursor to the starting position
void HLCD_voidClearScreen(LCD_t* LCD){
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_CLR_DISPLAY);
}

//Sets the cursor to initial position
void HLCD_voidGoHome(LCD_t* LCD){
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_RETURN_HOME);
}

//Sets the Cursor Mode
void HLCD_voidSetCursorMode(LCD_t* LCD, enum LCDCursorMode_t CursorMode){
		
	u8 Local_u8CursorMode = (CursorMode == LCD_CURSOR_ON_BLINK_OFF || CursorMode == LCD_CURSOR_ON_BLINK_ON)? 1:0;
	u8 Local_u8BlinkMode = (CursorMode == LCD_CURSOR_OFF_BLINK_ON || CursorMode == LCD_CURSOR_ON_BLINK_ON)? 1:0;
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_DISP_ON_OFF_CTRL(1,Local_u8CursorMode,Local_u8BlinkMode));
}

void HLCD_voidRotateDisplayRight(LCD_t* LCD){
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_CURSOR_DISPLAY_SHIFT(1,1));
}

void HLCD_voidRotateDisplayLeft(LCD_t* LCD){
	PLCD_voidWriteCommand(LCD,LCD_INSTRUCTION_CURSOR_DISPLAY_SHIFT(1,0));
	
}