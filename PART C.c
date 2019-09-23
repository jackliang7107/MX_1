/* 

This code continually scans ADC0 for an analog signal, using 16Mhz processor clock

*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <myFirstLibrary.h>
#define Trigvalue 100



volatile uint8_t ADCvalue;            // Global variable , set to volatile the value of the variable may change. if used with ISR 


int main(void)
{

  ADC_inti();
  sei();                    
  pinMode(PINB1,OUTPUT);

  while (1)
  {
  }
}


ISR(ADC_vect)
{
    ADCvalue = ADCH;                     // only need to read the high value for 8 bit
    
    if (ADCvalue > Trigvalue)
    {
      digitalWrite(PINB1,HIGH);  
    }
    else 
    {
      //digitalWrite(PINB1,LOW);
      PORTB &= ~(1<<PINB1);
    }                                    
}


