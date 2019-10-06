#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <UARTInit.h>

#define ctrl PORTD
#define en 2                         // enable signal
#define rw 1                       // read/write signal
#define rs 0                     // register select signal
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)



void LCD_cmd(unsigned char cmd);
void lcd_ini(void);
void LCD_write(unsigned char data);
void dis_cmd(char);  
void dis_data(char); 
void LCD_write_string(unsigned char *str);
void ADC_inti();
volatile double theTenBitResults;
volatile unsigned char receivedByte;

int main(void)
{
      
      
      DDRD=0xFF;                                  // setting the port c    // setting for port D
      ADC_inti();                                  
      lcd_ini();                                 // initialization of LCD
      _delay_ms(50);                             // delay of 50 mili seconds
      LCD_write_string("SID:12487118");
      dis_cmd(0xC0);
      LCD_write_string("MECHATRONICS 1");
      _delay_ms(1000);
      
      
      while(1)
      {
         USART_init();
         _delay_ms(1000);
         USART_putstring(String);    //Pass the string to the USART_putstring function and sends it over the serial_delay_ms(5000);
         _delay_ms(1000);   
         sei(); 
      }
      
}

ISR(USART_RX_vect) 
{         

      //TransmitUART('J');
      //receivedByte = UDR0;
      //PORTB ^= 1<<PINB0;  
}


/*
ISR(ADC_vect)
{                  
      theTenBitResults = ADC;   // read the low value for 10 bit
      
}
*/

void lcd_ini(void)
{
	dis_cmd(0x02); 					// to initialize LCD in 4-bit mode.
	_delay_ms(1);
	dis_cmd(0x28); 					//to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	_delay_ms(1);
	dis_cmd(0x01);                  // clear LCD
	_delay_ms(1);
	dis_cmd(0x0E);                  // cursor ON
	_delay_ms(1);
	dis_cmd(0x80);                  // —8 go to first line and –0 is for 0th position
	_delay_ms(1);
	return;
}
 
void dis_cmd(char cmd_value)  
{  
      char cmd_value1;  
      cmd_value1 = cmd_value & 0xF0;          	//mask lower nibble  
                         					 	//because PA4-PA7 pins are used.   
      LCD_cmd(cmd_value1);               		// send to LCD  
      cmd_value1 = ((cmd_value<<4) & 0xF0);     //shift 4-bit and mask  
                                   				 
      LCD_cmd(cmd_value1);               		// send to LCD  
}      

void dis_data(char data_value)  
{  
	char data_value1;  
	data_value1=data_value & 0xF0;  
	LCD_write(data_value1);  
	data_value1=((data_value<<4) & 0xF0);  
	LCD_write(data_value1);  
}  
                                                                                                     
void LCD_cmd(unsigned char cmd)
{
      ctrl=cmd;
      ctrl&=~(1<<rs);  
      ctrl&=~(1<<rw);  
      ctrl|=(1<<en);  
      _delay_ms(1);  
      ctrl&=~(1<<en);
      _delay_ms(40);  
       return;
}
 
void LCD_write(unsigned char data)
{
   ctrl= data;
   ctrl|=(1<<rs);  
   ctrl&=~(1<<rw);     
   ctrl|=(1<<en);  
   _delay_ms(1);  
   ctrl&=~(1<<en); 
   _delay_ms(1);
return ;
}
 
void LCD_write_string(unsigned char *str)             //store address value of the string in pointer *str
{
      int i=0;
      while(str[i]!='\0')                               // loop will go on till the NULL character in the string
      {
      dis_data(str[i]);                            // sending data on LCD byte by byte
      i++;
      }
      return;
}

void ADC_inti()
{
    ADMUX = 0;                // use ADC0
    ADMUX |= (1 << REFS0);    // use AVcc as the reference page 257


    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz. 16MHz/128 = 125 KHz ADC clock
    ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable. use Timer/Counters and the Analog Comparator as a trigger source to start the ADC conversions
    
    ADCSRB = 0;               // 0 for free running mode

    ADCSRA |= (1 << ADEN);    // Enable the ADCSRA see datasheet page 258
    ADCSRA |= (1 << ADIE);    // Enable interrrupts function in ADC 
    ADCSRA |= (1 << ADSC);    // Start the ADC conversion

}


