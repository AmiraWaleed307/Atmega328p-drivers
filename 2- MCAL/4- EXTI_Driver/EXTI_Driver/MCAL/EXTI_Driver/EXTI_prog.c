/*
 * EXTI_program.c
 *
 * Created: 19/09/2021 04:07:21 PM
 *  Author: Toothless XII
 */ 
#include "../../../../../1- LIB/STD_types.h"
#include "../../../../../1- LIB/BIT_math.h"
#include "EXTI_int.h"
#include "EXTI_priv.h"
#include "../INTERRUPTS_Driver/INTERRUPT.h"

void MEXTI_void_EnableInterrupt (enum EXTI_t Interrupt)
{
	switch (Interrupt)
	{
		case EXTI_0:
			SET_BIT(EXTI_EIMSK,0);
		break;
		
		case EXTI_1:
			SET_BIT(EXTI_EIMSK,1);
		break;
		
		case PCINT_0:
			SET_BIT(EXTI_PCICR,0);
		break;
		
		case PCINT_1:
			SET_BIT(EXTI_PCICR,1);
		break;
		
		case PCINT_2:
			SET_BIT(EXTI_PCICR,2);
		break;
		
		default:
		return;

	}
	INT_ENABLE_GLOBAL_INT;
	
}

void MEXTI_void_DisableInterrupt (enum EXTI_t Interrupt)
{
	switch (Interrupt)
	{
		case EXTI_0:
		CLR_BIT(EXTI_EIMSK,0);
		break;
		
		case EXTI_1:
		CLR_BIT(EXTI_EIMSK,1);
		break;
		
		case PCINT_0:
		CLR_BIT(EXTI_PCICR,0);
		break;
		
		case PCINT_1:
		CLR_BIT(EXTI_PCICR,1);
		break;
		
		case PCINT_2:
		CLR_BIT(EXTI_PCICR,2);
		break;
		
		default:
		return;

	}

	
}

void MEXTI_void_SetTrigger(enum EXTI_t Interrupt, enum EXTI_Trigger_t Trigger)
{
		switch (Interrupt)
		{
			case EXTI_0:
			EXTI_EICRA &= 0xFC ;
			EXTI_EICRA |= Trigger;
			break;
			
			case EXTI_1:
			EXTI_EICRA &= 0xF3 ;
			EXTI_EICRA |= Trigger<<2;

			break;

			default:
			return;

		}

	
	}

void MEXTI_void_SetPC_Pin ( u8 PinNum , enum EXTI_PC_PIN_s State)
{
	if (PinNum==15||PinNum>23)
		return;
	u8 Local_Mask = PinNum/8;
	switch (Local_Mask)
	{
		case PC_MASK_0_7 :
		CLR_BIT(EXTI_PCMSK_REG->EXTI_PCMSK0,(PinNum%8));
		EXTI_PCMSK_REG->EXTI_PCMSK0 |= (State<<(PinNum%8));
		break;
		
		case PC_MASK_8_14:
		CLR_BIT(EXTI_PCMSK_REG->EXTI_PCMSK1,(PinNum%8));
		EXTI_PCMSK_REG->EXTI_PCMSK1 |= (State<<(PinNum%8));

		break;
		
		case PC_MASK_16_23:
		CLR_BIT(EXTI_PCMSK_REG->EXTI_PCMSK2,(PinNum%8));
		EXTI_PCMSK_REG->EXTI_PCMSK2 |= (State<<(PinNum%8));

		break;
		
		default:
		return;
	}
	
}


void MEXTI_void_ClearFlag (enum EXTI_t Interrupt)
{
		switch (Interrupt)
		{
			case EXTI_0:
				SET_BIT(EXTI_FLAGS_REG->EXTI_EIFR,0);
				break;
			
			case EXTI_1:
				SET_BIT(EXTI_FLAGS_REG->EXTI_EIFR,1);
				break;
			
			case PCINT_0:
				SET_BIT(EXTI_FLAGS_REG->EXTI_PCIFR,0);
				break;
			
			case PCINT_1:
				SET_BIT(EXTI_FLAGS_REG->EXTI_PCIFR,1);
				break;
			
			case PCINT_2:
				SET_BIT(EXTI_FLAGS_REG->EXTI_PCIFR,2);
				break;
			
			default:
				return;
		}
	
}
	
void MEXTI_void_SetCallBack (enum EXTI_t Interrupt, void (*CallBack)(void))
{
		switch (Interrupt)
		{
			case EXTI_0:
			PEXTI_void_CallBacks[0] = CallBack;
			break;
			
			case EXTI_1:
			PEXTI_void_CallBacks[1] = CallBack;
			break;
			
			case PCINT_0:
			PEXTI_void_CallBacks[2] = CallBack;
			break;
			
			case PCINT_1:
			PEXTI_void_CallBacks[3] = CallBack;
			break;
			
			case PCINT_2:
			PEXTI_void_CallBacks[4] = CallBack;
			break;
			
			default:
			return;
		}
		
	}

void EXTI_VECTOR_ISR_EXTIO  (void)
{
	
	if(PEXTI_void_CallBacks[0] != 0)
	{
		PEXTI_void_CallBacks[0]();
	}
}
void EXTI_VECTOR_ISR_EXTI1  (void)
{
	
	if(PEXTI_void_CallBacks[1] != 0)
	{
		PEXTI_void_CallBacks[1]();
	}
}
void EXTI_VECTOR_ISR_PCINT0 (void)
{
	
	if(PEXTI_void_CallBacks[2] != 0)
	{
		PEXTI_void_CallBacks[2]();
	}
}
void EXTI_VECTOR_ISR_PCINT1 (void)
{
	
	if(PEXTI_void_CallBacks[3] != 0)
	{
		PEXTI_void_CallBacks[3]();
	}
}
void EXTI_VECTOR_ISR_PCINT2 (void)
{
	
	if(PEXTI_void_CallBacks[4] != 0)
	{
		PEXTI_void_CallBacks[4]();
	}
}