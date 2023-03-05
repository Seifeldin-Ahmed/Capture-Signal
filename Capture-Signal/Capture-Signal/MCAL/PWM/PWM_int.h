/*
 * PWM_int.h
 *
 *  Created on: Sep 6, 2022
 *      Author: Dell
 */

#ifndef MCAL_PWM_PWM_INT_H_
#define MCAL_PWM_PWM_INT_H_



typedef enum
{
	PWM_OK,
	PWM_NOK
}PWM_tenuErrorStatus;

// Macros for pins //
#define PWM_u8_OC0     0
#define PWM_u8_OC1A    1
#define PWM_u8_OC1B    2
#define PWM_u8_OC2     3

// macros for timers
#define PWM_u8_TIMER0                    0
#define PWM_u8_TIMER1                    1
#define PWM_u8_TIMER2                    2

//*** HINTS ***//
// 1) A special case occurs when OCRn equals TOP and COM21 is set(means inverting or non inverting mode). In this case, the compare match is ignored, but the set or clear is done at TOP (this happens in timer0,1,2)
// 2) When the ICR1 is used as TOP value (see description of the WGM13:0 bits located in the TCCR1A and the TCCR1B Register), the ICP1 is disconnected and consequently the Input Capture function is disabled.


//**************************************************** Compare Output Mode Section **********************************************
// macros for Compare Output Mode, Fast PWM Mode (0C0) and (0C2)
#define PWM_u8_DISCONNECTED                           0X00
#define PWM_u8_NON_INVERTING_MODE                     0X20
#define PWM_u8_INVERTING_MODE                         0X30

// macros for Compare Output Mode, Fast PWM (OC1A)
#define PWM_u8_OC1A_DISCONNECTED                       0X00
#define PWM_u8_NON_INVERTING_MODE_0C1A                 0X80
#define PWM_u8_INVERTING_MODE_OC1A                     0XC0

// macros for Compare Output Mode, Fast PWM (OC1B)
#define PWM_u8_OC1B_DISCONNECTED                       0X00
#define PWM_u8_NON_INVERTING_MODE_0C1B                 0X20
#define PWM_u8_INVERTING_MODE_OC1B                     0X30
//*********************************************************************************************************************************



//**************************************************** Operation Modes Section ******************************************************
// macros for Operation modes for TIMER1  //
#define PWM_u8_Fast_PWM_ICR1_TOP                        0X1A

// macros for Operation modes for TIMER0 and TIMER2  //
#define PWM_u8_Fast_PWM_MODE                            0X48
#define PWM_u8_Phase_CORRECT_MODE                       0X40

//************************************************************************************************************************************


//******************************************************* Prescaler Section ***********************************************************
//*************** macros for Prescaler for Timer 0 and Timer 1 ***************/
#define PWM_u8_NO_CLOCK_SOURCE                          0X00
#define PWM_u8_NO_PRESCALER_1                           0X01
#define PWM_u8_NO_PRESCALER_8                           0X02
#define PWM_u8_NO_PRESCALER_64                          0X03
#define PWM_u8_NO_PRESCALER_256                         0X04
#define PWM_u8_NO_PRESCALER_1024                        0X05
#define PWM_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE          0X06  // FOR TIMER 0 and TIMER 1 ONLY
#define PWM_EXTERNAL_CLOCK_SOURCE_RISING_EDGE           0X07 // FOR TIMER 0 and TIMER 1 ONLY


//*************** macros for Prescaler for Timer 2 **************************/
#define PWM_CHANNEL2_NO_CLK_SOURCE								0X00
#define PWM_CHANNEL2_PRESCALER_1								0X01
#define PWM_CHANNEL2_PRESCALER_8								0X02
#define PWM_CHANNEL2_PRESCALER_32								0X03
#define PWM_CHANNEL2_PRESCALER_64								0X04
#define PWM_CHANNEL2_PRESCALER_128								0X05
#define PWM_CHANNEL2_PRESCALER_256								0X06
#define PWM_CHANNEL2_PRESCALER_1024								0X07


//**************************************************************************************************************************************
PWM_tenuErrorStatus PWM_enuInit(u8 Copy_u8Timer , u8 Copy_u8Mode);

// Name: PWM_enuStart
// Description: Start PWM
// Arguments:            First : The Desired Timer  options(PWM_u8_TIMER0,PWM_u8_TIMER1,PWM_u8_TIMER2)
//                       Second: Prescaler Value
//                       Third : Compare Value  at which the generated form will change
//                       Fourth: Top Value for Timer1 used only with timer1 [because of ICR Register]
//                       Fifth : Compare output mode for pins OC0, OC1A, OC1B, OC2
//                       last : used only with timer one to choose OC1A or OC1B
// Retrun : Error Status
PWM_tenuErrorStatus PWM_enuStart(u8 Copy_u8Timer,u8 Copy_u8Prescaler,u16 Copy_u16CompareValue,u16 Copy_u16TopValue,u8 Copy_u8CompareOutputMode,u8 Copy_u8DesiredPin);


PWM_tenuErrorStatus PWM_enuStop(u8 Copy_u8Timer);


#endif /* MCAL_PWM_PWM_INT_H_ */
