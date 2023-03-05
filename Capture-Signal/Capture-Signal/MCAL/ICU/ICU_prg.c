/*
 * ICU_prg.c
 *
 *  Created on: Sep 7, 2022
 *      Author: Dell
 */

#include "../../LIB/STD_Types.h"
#include "ICU_int.h"
#include "ICU_prv.h"
#include "ICU_cfg.h"

ICU_tstrSnapShots Global_strSnapShots;
static u8  ICU_u8Prescaler =0;
volatile u8 ICU_u8_OVFCOUNTER=0;



ICU_tenuErrorStatus ICU_enuConfigure(ICU_tstrConfigure* Add_pstrConfigue)
{
	ICU_tenuErrorStatus Local_enuErrorStatus= ICU_OK;

	if(Add_pstrConfigue == NULL)
	{
		Local_enuErrorStatus= ICU_NOK;
	}
	else
	{ 
		 ICU_u8_TIFR_REG |= (1<<5); // clear flag of ICF1
		 ICU_u8_TCCR1A = 0; // Because the bit 0,1 for wave generation mode and we want normal mode, bit 2,3 for force output compare , bit 4,5,6,7 for COM1A/1B we don't need all of this here
	
		//Clear the register for next configuration //
		ICU_u8_TCCR1B=0x00;

		// Set Noise Prescaler //
		ICU_u8_TCCR1B |= Add_pstrConfigue->ICU_u8NoiseCanceller;

		//Set the edge select to rising edge //
		ICU_u8_TCCR1B |= 0x40;

		// enable interrupts for OVF and InputCapture //
		ICU_u8_TIMSK_REG |= Add_pstrConfigue->ICU_u8InterruptOption;
		 //Buffering  Prescaler //
		ICU_u8Prescaler = Add_pstrConfigue->ICU_u8Prescaler;
		if(Add_pstrConfigue->ICU_u8InterruptOption == ICU_u8_Interrupt_Enable)
		       ICU_u8_TCCR1B |=  ICU_u8Prescaler;           // start timer //	 	
	}

	return Local_enuErrorStatus;
}
ICU_tenuErrorStatus ICU_enuGetFreqAndDutyCycle_Synchronise(u32 *Add_pu32Frequency,u8* Add_pu8DutyCycle)
{
	ICU_tenuErrorStatus Local_enuErrorStatus= ICU_OK;

	if(Add_pu32Frequency == NULL || Add_pu8DutyCycle == NULL)
	{
		Local_enuErrorStatus= ICU_NOK;
	}
	else
	{
       
		 ICU_tstrSnapShots  Local_Snap;
		 u32 Local_u32Total = 0;
	 	 u32 Local_u32Ton=0;
		 ICU_u8_TIFR_REG |= (1<<5); // clear flag of ICF1 
		 ICU_u8_TCCR1B |=  ICU_u8Prescaler; // start timer //		
	     while ((ICU_u8_TIFR_REG&(1<<5)) == 0); //polling on the flag		
		 Local_Snap.ICU_u32FirstSnapShot = (ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1))); // 0xffff is 2 byte , 1 is int so it'2 = 2 byte (2 byte + 2 byte = 2 byte so (0xffff +1 ) will be casted to 0xffff , so it's important to make it unsigned long( 4 byte + 2 byte = 4 byte)
		 ICU_u8_TIFR_REG |= (1<<5); // clear flag of ICF1 
		
		 // set the edge select to falling edge //
		 ICU_u8_TCCR1B &= ~(1<<6); //10111111		
		 while ((ICU_u8_TIFR_REG&(1<<5)) == 0); //polling on the flag
		 Local_Snap.ICU_u32SecondSnapShot = (ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1)));
		  ICU_u8_TIFR_REG |= (1<<5); // clear flag of ICF1 
		
       
         // set the edge select to rising edge //
         ICU_u8_TCCR1B |= (1<<6);		
		 while ((ICU_u8_TIFR_REG&(1<<5)) == 0); //polling on the flag
	  	 Local_Snap.ICU_u32ThirdSnapShot = (ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1)));
		 ICU_u8_TIFR_REG |= (1<<5); // clear flag of ICF1 

		 // Stop Timer and clear //
		 ICU_u8_TCCR1B = 0X00;
		 ICU_u16_TCNT1L = 0;
		 ICU_u16_ICR1L=0;

         Local_u32Ton = (Local_Snap.ICU_u32SecondSnapShot) - (Local_Snap.ICU_u32FirstSnapShot) ;
         Local_u32Total = (Local_Snap.ICU_u32ThirdSnapShot) - (Local_Snap.ICU_u32FirstSnapShot);

	 	 *Add_pu8DutyCycle =((Local_u32Ton*100.0)/Local_u32Total);
		 *Add_pu32Frequency =Freq_CPU/(Local_u32Total);
	}	
	return Local_enuErrorStatus;	 
		
}


ICU_tenuErrorStatus ICU_enuGetFrequency(u32 *Add_pu32Frequency)
{
 u32 Local_u32Total = 0;
 u32 Local_u32Ton=0;
	ICU_tenuErrorStatus Local_enuErrorStatus= ICU_OK;
    u16    Local_u16RealPrescaler=0;
 		if(Add_pu32Frequency == NULL)
		{
			Local_enuErrorStatus= ICU_NOK;
		}
		else
		{
             switch (ICU_u8Prescaler)
             {

                 case ICU_u8_NO_CLOCK_SOURCE:
	                             Local_u16RealPrescaler=0;
                	             break;
                 case ICU_u8_NO_PRESCALER_1:
                            	 Local_u16RealPrescaler=1;
                            	 break;
                 case ICU_u8_NO_PRESCALER_8:
                            	 Local_u16RealPrescaler=8;
                            	 break;
                 case ICU_u8_NO_PRESCALER_64:
                            	 Local_u16RealPrescaler=64;
                            	 break;
                 case ICU_u8_NO_PRESCALER_256:
                            	 Local_u16RealPrescaler=256;
                            	 break;
                 case ICU_u8_NO_PRESCALER_1024:
                            	 Local_u16RealPrescaler=1024;
                            	 break;
             }
			 Local_u32Ton = (Global_strSnapShots.ICU_u32SecondSnapShot) - (Global_strSnapShots.ICU_u32FirstSnapShot) ;
			 Local_u32Total = (Global_strSnapShots.ICU_u32ThirdSnapShot) - (Global_strSnapShots.ICU_u32FirstSnapShot);
              *Add_pu32Frequency =Freq_CPU/(Local_u16RealPrescaler*Local_u32Total);
		}

		return Local_enuErrorStatus;
}

ICU_tenuErrorStatus ICU_enuGetDutyCycle(u8* Add_pu8DutyCycle)
{
	 u32 Local_u32Total = 0;
	 u32 Local_u32Ton=0;
	ICU_tenuErrorStatus Local_enuErrorStatus= ICU_OK;
		if(Add_pu8DutyCycle == NULL)
		{
			Local_enuErrorStatus= ICU_NOK;
		}
		else
		{
			Local_u32Ton = (Global_strSnapShots.ICU_u32SecondSnapShot) - (Global_strSnapShots.ICU_u32FirstSnapShot) ;
			Local_u32Total = (Global_strSnapShots.ICU_u32ThirdSnapShot) - (Global_strSnapShots.ICU_u32FirstSnapShot);
			
			 *Add_pu8DutyCycle =((Local_u32Ton*100.0)/Local_u32Total);
		}

		return Local_enuErrorStatus;

}

//***************** For UltraSonic ****************//
ICU_tenuErrorStatus ICU_vidGetTimeForPulse(u32 *Add_pu32Time)
{
	ICU_tenuErrorStatus Local_enuErrorStatus= ICU_OK;

	if(Add_pu32Time == NULL)
	{
		Local_enuErrorStatus= ICU_NOK;
	}
	else
	{
		u32 Local_u32FirstSnap  = 0;
		u32 Local_u32SecondSnap=0;
	
	    ICU_u8_TCCR1B |=  ICU_u8Prescaler; // start timer //
		while ((ICU_u8_TIFR_REG&(1<<5)) == 0); //polling on the flag
		Local_u32FirstSnap = (ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1)));
		ICU_u8_TIFR_REG |= (1<<5); // clear flag of ICF1
		
		
		ICU_u8_TCCR1B &= ~(1<<6); //10111111   // set the edge select to falling edge //
		while ((ICU_u8_TIFR_REG&(1<<5)) == 0); //polling on the flag
		Local_u32SecondSnap = (ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1)));
		ICU_u8_TIFR_REG |= (1<<5); // clear flag of ICF1
		
		ICU_u8_TCCR1B &=0XF8; //stop timer;  // 1111 1000
		ICU_u16_TCNT1L=0;
		ICU_u8_OVFCOUNTER=0;
		*Add_pu32Time = Local_u32SecondSnap - Local_u32FirstSnap;
		// for next configuration
		ICU_u8_TCCR1B |= (1<<6);  // set the edge select to risingF edge //
		
	}
	return Local_enuErrorStatus;
}

// ISR FOR OVER FLOW //

void __vector_9(void)    __attribute__((signal,used));
void __vector_9(void)
{
	ICU_u8_OVFCOUNTER++;
}	
//ISR FOR Input Capture Interrupt //

void __vector_6(void)    __attribute__((signal,used));
void __vector_6(void)
{
	static ICU_tenuStateMachine  Local_enuStateMachine = ICU_FirstRising;
	switch (Local_enuStateMachine)
	{

	               case ICU_FirstRising:
	              // it's better not to start the timer here, because when a rising edge happen, an interrupt occur ---> push instructions first , so with very large freq like 5KHZ and 7.5KHZ 
				  // the processor already spend some time in push instructions may be for 2 micro or 3 micro second for example , and 5KHZ means 200Micro second period time 
				  // so it's better to start the timer  at configuration, cause when rising edge happen , the ICR will already has a screen shot from TCNT at this moment, and it will yeild at better accuracy 
	                 	Global_strSnapShots.ICU_u32FirstSnapShot = (ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1)));	 	                            	 
	         	         ICU_u8_TCCR1B &= ~(1<<6);    //1011 1111    // set the edge select to falling edge //
						 Local_enuStateMachine = ICU_FirstFalling;  // Prepare for next state //
                         break;

	               case ICU_FirstFalling:
  	         	         
  	                      Global_strSnapShots.ICU_u32SecondSnapShot = (ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1)));   // Take Second snap shot from Input Capture Register //          	                  	                    	          	           	          
	           	          ICU_u8_TCCR1B |= (1<<6);                   //0100 0000      // set the edge select to rising edge //
						  Local_enuStateMachine = ICU_SecondRising;                  // Prepare for next state //
	                      break;

	               case ICU_SecondRising:      	    
				        
	          	          Global_strSnapShots.ICU_u32ThirdSnapShot =(ICU_u16_ICR1L + (ICU_u8_OVFCOUNTER * (0xffffUL+1)));   // Take Third snap shot from Input Capture Register //   
	           	          Local_enuStateMachine = ICU_FirstRising;                    // Prepare for next state //

						   // Stop Timer and clear //
					  	    ICU_u8_TCCR1B = 0X00;
				            ICU_u16_TCNT1L = 0;
				            ICU_u16_ICR1L=0;
                            ICU_u8_TIMSK_REG  &= (~ICU_u8_Interrupt_Enable); // 0x24 0010 0100 ---->   1101 1011  0XDB
	                        break;
	 }
}
