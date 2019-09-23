//*****Control an LED at a specific frequency********//


#include <avr/io.h>
#include <myFirstLibrary.h>


//************************//
int main(void)

{


  while (1)
  {
    Blink(PINB1,PINB0,0.5);
  }
}

