/*
 * main.c
 *
 * Created: 22/09/2022 7:53:40 PM
 *  Author: SEIFELDIN AHMED ISMAIL
 */
#include <avr/io.h>
#define F_CPU 8000000UL
#include "util\delay.h"

#include "../LIB/STD_Types.h"
#include "../HAL/PORT/PORT_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/ICU/ICU_int.h"
#include "../MCAL/PWM/PWM_int.h"
 int main(void)
 {
	 u32 frequency ;
	 u8 duty_cycle;
	 ICU_tstrConfigure object;
	 object.ICU_u8Prescaler =ICU_u8_NO_PRESCALER_1;
	 object.ICU_u8NoiseCanceller = ICU_u8_NOISE_CANCELLER_ACTIVATE;
	 object.ICU_u8InterruptOption=ICU_u8_Interrupt_Enable;
	 INT_vidEnableGlobalINT();
	 PORT_vidInit();
	 LCD_VidInit();
	 
	 PWM_enuInit( PWM_u8_TIMER0 ,  PWM_u8_Fast_PWM_MODE);
	 PWM_enuStart( PWM_u8_TIMER0, PWM_u8_NO_PRESCALER_1024,220, 0, PWM_u8_NON_INVERTING_MODE, PWM_u8_OC0);

	 ICU_enuConfigure(&object);
	 _delay_ms(2000);
	 ICU_enuGetDutyCycle(&duty_cycle);
	 ICU_enuGetFrequency(&frequency);
	 LCD_enuSendString("duty:");
	 LCD_enuSendNumber(duty_cycle);
	 LCD_enuSendCharacter('%');
	 LCD_enuGoTo(1,0);
	 LCD_enuSendString("freq:");
	 LCD_enuSendNumber(frequency);
	 LCD_enuSendString("HZ");


	 while (1)
	 {
	 }

	 
	 
	 return 0;
 }