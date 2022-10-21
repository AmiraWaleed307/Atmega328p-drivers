/*
 * EXTI_interface.h
 *
 * Created: 19/09/2021 04:06:32 PM
 *  Author: Toothless XII
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

enum EXTI_t {EXTI_0,EXTI_1,PCINT_0,PCINT_1,PCINT_2};
enum EXTI_Trigger_t {TRIGGER_LOW_LEVEL , TRIGGER_LOGICAL_CHANGE , TRIGGER_FALLING_EDGE , TRIGGER_RISING_EDGE };
enum EXTI_PC_PIN_s {EXTI_PC_PIN_DISABLE, EXTI_PC_PIN_ENABLE };
	
void MEXTI_void_EnableInterrupt (enum EXTI_t Interrupt);
void MEXTI_void_DisableInterrupt (enum EXTI_t Interrupt);
void MEXTI_void_SetTrigger(enum EXTI_t Interrupt, enum EXTI_Trigger_t Trigger);
void MEXTI_void_SetPC_Pin ( u8 PinNum , enum EXTI_PC_PIN_s State);
void MEXTI_void_ClearFlag (enum EXTI_t Interrupt);
void MEXTI_void_SetCallBack (enum EXTI_t Interrupt, void (*CallBack)(void));



#endif /* EXTI_INTERFACE_H_ */