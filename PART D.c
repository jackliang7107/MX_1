#include <avr/io.h>
#include <myFirstLibrary.h>
#include <avr/interrupt.h>
#

volatile uint8_t ADCvalue; 
volatile float delay_value ;
volatile uint16_t theTenBitResults;
int main(void)

{

  ADC_inti();
  sei();                    

  while (1)
  {
    float adcResult = theTenBitResults;
    float scaled = ((adcResult/1023.0)*(2 - 0.1))+0.1;
    delay_value = scaled;
    Toggle(PINB0,PINB1,delay_value);
  }

}

ISR(ADC_vect)
  {

    // ADCvalue = ADCL;                             // read the low value for 10 bit
    theTenBitResults = ADC;   

  }