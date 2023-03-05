# Measure Frequency and Duty Cycle Of a Signal 
Embedded System Project Using AVR

MicroController: AVR atmega 32

Drivers: DIO, LCD, PWM, ICU.

measure clock signal with 20Hz
![c1](https://user-images.githubusercontent.com/120275931/222934574-1f5fae78-cf8a-4e12-bea4-79ccd1f73b2f.png)

![c2](https://user-images.githubusercontent.com/120275931/222934575-6f94ff27-14cb-4ab9-bde6-fa4bf037f847.png)


generating a pwm signal on timer0 with freqeuncy = 30Hz 
F-CPU = 8 MHZ, prescaler = 1024, tick time = 1024/ 8000 000=0.000128 second so freq = 1/(256*0.000128)   
set OCR0 to 220 so in count number 221 an compare match will occur and OCO will be cleared , Ton= 0.000128*221 , Tperiod= 0.000128 * 256

![c3](https://user-images.githubusercontent.com/120275931/222934577-664f0b37-6abb-4ca0-9157-bd6fded864cc.png)

![c4](https://user-images.githubusercontent.com/120275931/222934578-5ce6bfaf-8a3d-4301-a4fe-c53615be9700.png)
