/*
 * EXTI_private.h
 *
 * Created: 19/09/2021 04:06:52 PM
 *  Author: Toothless XII
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

typedef struct {
	
	u8 EXTI_PCIFR;
	u8 EXTI_EIFR;
	
}EXTI_FLAGS;

typedef struct {
	
	u8 EXTI_PCMSK0;
	u8 EXTI_PCMSK1;
	u8 EXTI_PCMSK2;
}EXTI_PCMSK;

#define EXTI_EICRA				*((volatile u8*) 0x69)
#define EXTI_EIMSK				*((volatile u8*) 0x3D)
#define EXTI_PCICR				*((volatile u8*) 0x68)
#define EXTI_FLAGS_REG		     ((volatile EXTI_FLAGS*)0x3B)
#define EXTI_PCMSK_REG		     ((volatile EXTI_PCMSK*)0x6B)

#define EXTI_VECTOR_ISR_EXTIO		__vector_1
#define EXTI_VECTOR_ISR_EXTI1		__vector_2
#define EXTI_VECTOR_ISR_PCINT0		__vector_3
#define EXTI_VECTOR_ISR_PCINT1		__vector_4
#define EXTI_VECTOR_ISR_PCINT2		__vector_5

#define PC_MASK_0_7					0
#define PC_MASK_8_14				1
#define PC_MASK_16_23				2


void EXTI_VECTOR_ISR_EXTIO  (void)   __attribute__((signal,used));
void EXTI_VECTOR_ISR_EXTI1  (void)	 __attribute__((signal,used));
void EXTI_VECTOR_ISR_PCINT0 (void)	 __attribute__((signal,used));
void EXTI_VECTOR_ISR_PCINT1 (void)	 __attribute__((signal,used));
void EXTI_VECTOR_ISR_PCINT2 (void)	 __attribute__((signal,used));

void (*PEXTI_void_CallBacks[5])(void)={0,0,0,0,0};

#endif /* EXTI_PRIVATE_H_ */