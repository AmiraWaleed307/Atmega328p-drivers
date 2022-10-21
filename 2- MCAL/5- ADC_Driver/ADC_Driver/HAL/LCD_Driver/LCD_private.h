#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H


#define LCD_INSTRUCTION_CLR_DISPLAY						1
#define LCD_INSTRUCTION_RETURN_HOME						2
#define LCD_INSTRUCTION_ENTRY_MODE_SET(ID,SH)			((1<<2)|(ID<<1)|SH)
#define LCD_INSTRUCTION_DISP_ON_OFF_CTRL(D,C,B)			((1<<3)|(D<<2)|(C<<1)|(B))
#define LCD_INSTRUCTION_CURSOR_DISPLAY_SHIFT(SC,RL)		((1<<4)|(SC<<3)|(RL<<2))
#define LCD_INSTRUCTION_FUNCTION_SET(DL,N,F)			((1<<5)|(DL<<4)|(N<<3)|(F<<2))
#define LCD_INSTRUCTION_SET_CGRAM_ADDR(ADDR)			((1<<6)|(ADDR&0x3F))
#define LCD_INSTRUCTION_SET_DDRAM_ADDR(ADDR)			((1<<7)|(ADDR&0x7F))


#define LCD_RS_LOW(LCD)						(MGPIO_void_SetPinValue(LCD->ControlPorts[0],LCD->ControlPins[0],GPIO_LOW))
#define LCD_RS_HIGH(LCD)					(MGPIO_void_SetPinValue(LCD->ControlPorts[0],LCD->ControlPins[0],GPIO_HIGH))

#define LCD_RW_LOW(LCD)						(MGPIO_void_SetPinValue(LCD->ControlPorts[1],LCD->ControlPins[1],GPIO_LOW))
#define LCD_RW_HIGH(LCD)					(MGPIO_void_SetPinValue(LCD->ControlPorts[1],LCD->ControlPins[1],GPIO_HIGH))



u8 PYPositions[4] = {0,64,20,84};

void PLCD_voidWrite8Bits(LCD_t* LCD, u8 Byte);
void PLCD_voidWrite4Bits(LCD_t* LCD, u8 HalfByte);
void PLCD_voidEnable(LCD_t* LCD);
void PLCD_voidSetReadMode(LCD_t* LCD);
void PLCD_voidSetWriteMode(LCD_t* LCD);
void PLCD_voidWaitForBusyFlag(LCD_t* LCD);
void PLCD_voidWriteCommand(LCD_t* LCD, u8 Command);
void PLCD_voidWriteData(LCD_t* LCD, u8 Data);






#endif


