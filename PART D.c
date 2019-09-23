#include <avr/io.h>
#include <myFirstLibrary.h>
#include <avr/interrupt.h>
#define conver_val 0.1
float delay_vale ;

int main(void)

{

  ADC_inti();
  sei();                    
  

  while (1)
  {
  }

}


ISR(ADC_vect)
  {
    ADCvalue = ADCH; 
    delay_vale = ADCvalue* conver_val; 
    Blink(PINB0,PINB1,delay_vale);                              
  }