/************************************************/
/* Title       : BIT MATH file				    */
/* Author      : XII & Mohamed Alaa             */
/* Release     : 1.0                            */
/* Last Update : Aug 15, 2021                   */
/************************************************/
 
#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(VAR,BIT)					        (VAR |= (1<<BIT))
#define CLR_BIT(VAR,BIT)					        (VAR &= ~(1<<BIT))
#define TOG_BIT(VAR,BIT)					        (VAR ^= (1<<BIT))
#define GET_BIT(VAR,BIT)					        ((VAR>>BIT) & 1)


#define SET_REG(REG)								(REG=0xFF)
#define CLR_REG(REG)								(REG=0)
#define TOG_REG(REG)								(REG ^= 0xFF)

#define SET_DWORD(DWORD)							(DWORD=0xFFFF)
#define CLR_DWORD(DWORD)							(DWORD=0)
#define TOG_DWORD(DWORD)							(DWORD ^= 0xFFFF)


#define CONC_BIT(A7,A6,A5,A4,A3,A2,A1,A0)			CONC_HELP(A7,A6,A5,A4,A3,A2,A1,A0)
#define CONC_HELP(A7,A6,A5,A4,A3,A2,A1,A0)			0b##A7##A6##A5##A4##A3##A2##A1##A0	
 
#define CONC_BIT_2(A7,A6,A5,A4,A3,A2,A1,A0)			(A7<<7|A6<<6|A5<<5|A4<<4|A3<<3|A2<<2|A1<<1|A0<<0)
 
#endif
