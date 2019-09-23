//*****Control an LED at a specific frequency********//


#include <avr/io.h>
#include <myFirstLibrary.h>



//*************************//

double data,value;
char LOW,HIGH,mode;


//************************//


int main(void)

{
  //PIN SETUP
  digitalWrite(PINB0,HIGH);  
  digitalWrite(PINB1,LOW);

  while (1)
  {
  if (PINB & (1<<PINB1))
      {
        PORTB |= (1 << PINB0);
      }

      else
      {
        PORTB &= ~(1 << PINB0);
      }
  }

  
}



//*********************************************//