/*
 * ICU_prv.h
 *
 *  Created on: Sep 7, 2022
 *      Author: Dell
 */

#ifndef MCAL_ICU_ICU_PRV_H_
#define MCAL_ICU_ICU_PRV_H_


#define ICU_u8_TCCR1B                (*(volatile u8*)0X4E)
#define ICU_u8_TCCR1A                (*(volatile u8*)0X4F)

#define ICU_u16_ICR1L                (*(volatile u16*)0X46)  //Timer/Counter1 – Input Capture Register Low Byte

#define ICU_u16_TCNT1L               (*(volatile u16*)0X4C)  //Timer/Counter1 – Input Capture Register Low Byte


#define ICU_u8_TIMSK_REG             (*(volatile u8*)0X59) // for interrupts

#define ICU_u8_TIFR_REG              (*(volatile u8*)0X58) // for Flags

typedef enum
{
	ICU_FirstRising,
	ICU_FirstFalling,
	ICU_SecondRising
}ICU_tenuStateMachine;



typedef struct
{
	u32 ICU_u32FirstSnapShot;
	u32 ICU_u32SecondSnapShot;
	u32 ICU_u32ThirdSnapShot;
}ICU_tstrSnapShots;


#endif /* MCAL_ICU_ICU_PRV_H_ */
