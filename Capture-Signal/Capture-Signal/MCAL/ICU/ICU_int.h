/*
 * ICU_int.h
 *
 *  Created on: Sep 7, 2022
 *      Author: Dell
 */

#ifndef MCAL_ICU_ICU_INT_H_
#define MCAL_ICU_ICU_INT_H_

// check error status //
typedef enum
{
	ICU_OK,
	ICU_NOK
}ICU_tenuErrorStatus;


// options for configuration //
typedef struct
{
	u8 ICU_u8Prescaler;
	u8 ICU_u8NoiseCanceller;
	u8 ICU_u8InterruptOption;
}ICU_tstrConfigure;


//******************************************************* Noise Canceller Section *****************************************************
#define ICU_u8_NOISE_CANCELLER_ACTIVATE                 0X80
#define ICU_u8_NOISE_CANCELLER_DEACTIVATE               0X00
//*************************************************************************************************************************************

#define ICU_u8_Interrupt_Enable                          0X24 
#define ICU_u8_Interrupt_Disable                         0X04



//******************************************************* Prescaler Section ***********************************************************
// macros for prescaler
#define ICU_u8_NO_CLOCK_SOURCE                          0X00
#define ICU_u8_NO_PRESCALER_1                           0X01
#define ICU_u8_NO_PRESCALER_8                           0X02
#define ICU_u8_NO_PRESCALER_64                          0X03
#define ICU_u8_NO_PRESCALER_256                         0X04
#define ICU_u8_NO_PRESCALER_1024                        0X05
#define ICU_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE          0X06
#define ICU_EXTERNAL_CLOCK_SOURCE_RISING_EDGE           0X07
//**************************************************************************************************************************************




ICU_tenuErrorStatus ICU_enuConfigure(ICU_tstrConfigure* Add_pstrConfigue);


ICU_tenuErrorStatus ICU_enuGetFreqAndDutyCycle_Synchronise(u32 *Add_pu32Frequency,u8* Add_pu8DutyCycle);

ICU_tenuErrorStatus ICU_enuGetFrequency(u32 *Add_pu32Frequency);
ICU_tenuErrorStatus ICU_enuGetDutyCycle(u8* Add_pu8DutyCycle);

ICU_tenuErrorStatus ICU_vidGetTimeForPulse(u32 *Add_pu32Time);

#endif /* MCAL_ICU_ICU_INT_H_ */
