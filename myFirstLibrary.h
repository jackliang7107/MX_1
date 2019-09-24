
#ifndef myFirstLibrary_h
#define myFirstLibrary_h
#include <avr/interrupt.h>
#include <avr/io.h>


int pin;
char OUTPUT;
char INPUT;
char HIGH;
char LOW; 
double sec; 
double data;
char State;
char pinOne;
char pinTwo;
double Input_value;
double delay;
volatile uint8_t ADCvalue;

void digitalWrite(int pin, char State)
{

  if (State == HIGH) 
  {                                         //If the mode == INPUT, turn the PORT to HIGH 
    PORTB |= (1<<pin);                      //HIGHT
  }
  else 
  {
    PORTB &= ~(1<<pin);                
  }
}

void pinMode(int pin, char mode)
{

  if (mode == OUTPUT) 
  {                                       //If the mode == INPUT, turn the PORT to HIGH 
    DDRB |= (1<<pin);                     //HIGHT
  }
  
  else if (mode == INPUT)
  {
    DDRB &= ~(1<<pin);                    //If the mode == OUTPUT, turn the PORT to LOW
  }
  
}

void ADC_inti()
{
    ADMUX = 0;                // use ADC0
    ADMUX |= (1 << REFS0);    // use AVcc as the reference page 257
    ADMUX &= ~(1<<ADLAR);

    ADCSRA |= (1 << ADPS2)| (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz 
    ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
    
    ADCSRB = 0;               // 0 for free running mode

    ADCSRA |= (1 << ADEN);    // Enable the ADCSRA see datasheet page 258
    ADCSRA |= (1 << ADIE);    // Enable interrrupts function in ADC 

    ADCSRA |= (1 << ADSC);    // Start the ADC conversion

}

void Time_Delay(double sec)

{
  data = sec*15625;
  Input_value = 65535-data; 
  TCCR1B |= (1<<CS10)|(1<<CS12);          //Setting cs10 and 12 to TCCR1B Register
  TCNT1 = Input_value;                           //Timer 1    
  while((TIFR1 & (1<<TOV1))==0);          //whenevey the TCNT1 get to my input_value, TOV1 bit will be set to 1 in TIFR1
  TCNT1 =0;   
  TIFR1 =(1<<TOV1);                       //clear the flag
}


void Blink (int pinOne, int pinTwo, double delay)

{

 
    //set up two LED
    pinMode(pinOne,OUTPUT);
    pinMode(pinTwo,OUTPUT);

    digitalWrite(pinOne,HIGH);
    digitalWrite(pinTwo,HIGH);
    Time_Delay(delay);


    //digitalWrite(pinOne,LOW);
    //digitalWrite(pinTwo,LOW);
    PORTB &= ~(1<<PINB0);
    PORTB &= ~(1<<PINB1);
    Time_Delay(delay);
  
} 
void Toggle (int pinOne, int pinTwo, double delay)

{

    pinMode(pinOne,OUTPUT);
    pinMode(pinTwo,OUTPUT);

    PORTB ^= (1<<pinOne);
    Time_Delay(delay);
    PORTB ^= (1<<pinTwo);
    Time_Delay(delay);
  
}



#endif