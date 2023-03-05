/*
 * PWM_cfg.c
 *
 *  Created on: Sep 6, 2022
 *      Author: Dell
 */
#include "../../LIB/STD_Types.h"
#include "PWM_int.h"
#include "PWM_prv.h"

PWM_tenuErrorStatus PWM_enuInit(u8 Copy_u8Timer , u8 Copy_u8Mode)
{
	PWM_tenuErrorStatus Local_enuErrorStatus = PWM_OK;
    u8 var=0;
	if(Copy_u8Timer > PWM_u8_TIMER2)
	{
		Local_enuErrorStatus= PWM_NOK;
	}
	else
	{
		switch (Copy_u8Timer)
		{
	      	case PWM_u8_TIMER0:
	      		                 PWM_u8_TCCR0_REG |=Copy_u8Mode;
	      		                    break;
	      	case PWM_u8_TIMER1:
	      		          var=(Copy_u8Mode) &  (0X01);
	      		                   PWM_u8_TCCR1A |= var;
	      		          var=(Copy_u8Mode) & (0X01<<1);
	      				           PWM_u8_TCCR1A |= var;
	     	      		  var=(Copy_u8Mode) & (0X01<<3);
	      			           	   PWM_u8_TCCR1B |= var;
	     	      		  var=(Copy_u8Mode) & (0X01<<4);
	      			           	   PWM_u8_TCCR1B |= var;
	      		//PWM_u8_TCCR1A|=0X02;
	      		//PWM_u8_TCCR1B |=0X18;
	      			               break;

	      	 case PWM_u8_TIMER2:
	      		                 PWM_u8_TCCR2_REG  |=0X48;
	      	                      break;
		}


	}
	return Local_enuErrorStatus;
}


PWM_tenuErrorStatus PWM_enuStart(u8 Copy_u8Timer,u8 Copy_u8Prescaler,u16 Copy_u16CompareValue,u16 Copy_u16TopValue,u8 Copy_u8CompareOutputMode,u8 Copy_u8DesiredPin)
{
	PWM_tenuErrorStatus Local_enuErrorStatus = PWM_OK;
	if(Copy_u8Timer > PWM_u8_TIMER2)
	{
		Local_enuErrorStatus= PWM_NOK;
	}
	else
	{
		switch (Copy_u8Timer)
				{
			      	case PWM_u8_TIMER0:
		                         PWM_u8_TCCR0_REG  |= Copy_u8CompareOutputMode;  // non inverting for example
		  		                 PWM_u8_OCR0_REG    = Copy_u16CompareValue;
		  		                 PWM_u8_TCCR0_REG  |= Copy_u8Prescaler;        // set prescaler

			      		                   break;
			      	case PWM_u8_TIMER1:
			      		      PWM_u8_TCCR1A  |= Copy_u8CompareOutputMode;  // non inverting for example
			      		      if(Copy_u8DesiredPin==PWM_u8_OC1A)
			      		         {
			      		    	   PWM_u16_OCR1AL  = Copy_u16CompareValue;
			      		         }
			      		      else if (Copy_u8DesiredPin==PWM_u8_OC1B)
				      		      {
			      		    	    PWM_u16_OCR1BL = Copy_u16CompareValue;
				      		      }
			      		      else
			      				  {
			      		    	    Local_enuErrorStatus= PWM_NOK;
			      				  }
			      		      PWM_u16_ICR1L   = Copy_u16TopValue; // top value to set frequency
			      		      PWM_u8_TCCR1B  |= Copy_u8Prescaler;        // set prescaler

			      			               break;

			      	 case PWM_u8_TIMER2:
			      		PWM_u8_TCCR2_REG  |=Copy_u8CompareOutputMode;  // non inverting for example
  		                PWM_u8_OCR2_REG    =Copy_u16CompareValue;
			      		PWM_u8_TCCR2_REG  |=Copy_u8Prescaler;        // set prescaler

			      	                     break;
				}
	}

		return Local_enuErrorStatus;
}

PWM_tenuErrorStatus PWM_enuStop(u8 Copy_u8Timer)
{
	PWM_tenuErrorStatus Local_enuErrorStatus = PWM_OK;
	if(Copy_u8Timer > PWM_u8_TIMER2)
	{
		Local_enuErrorStatus= PWM_NOK;
	}
	else
	{

		switch (Copy_u8Timer)
				{
			      	case PWM_u8_TIMER0:
			      	                  	 PWM_u8_TCCR0_REG &= ~(1<<0);
			      	                   	 PWM_u8_TCCR0_REG &= ~(1<<1);
			      	                  	 PWM_u8_TCCR0_REG &= ~(1<<1);
			      		                   break;
			      	case PWM_u8_TIMER1:
							             PWM_u8_TCCR1B &= ~(1<<0);
			       		                 PWM_u8_TCCR1B &= ~(1<<1);
 			      		                 PWM_u8_TCCR1B &= ~(1<<1);
			      			               break;
			      	 case PWM_u8_TIMER2:
			         	                 PWM_u8_TCCR2_REG &= ~(1<<0);
						              	 PWM_u8_TCCR2_REG &= ~(1<<1);
				   	                  	 PWM_u8_TCCR2_REG &= ~(1<<1);
						      		                   break;
			      	                     break;
				}

	}

		return Local_enuErrorStatus;
}
