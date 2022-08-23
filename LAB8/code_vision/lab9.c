
//Niki Nezakati - 98522094
/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :  LAB 9
Version : 
Date    : 4/30/2022
Author  : Niki Nezakati - 98522094
Company : 
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here

// Standard Input/Output functions
#include <stdio.h>

unsigned char i;

void usart_send_string(char *str)
{
    for(i=0; str[i]; i++)
    putchar(str[i]);
}


void main(void)
{
unsigned char ch, counter=0;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 16

lcd_init(16);

while (1)
      {
        ch = getchar();
        lcd_putchar(ch);
        putchar(ch);
        if(ch == 'C')      
        {
            lcd_clear();  
            putchar(0x0D); //CL 
            putchar(0x0A); //RF
        } 
        else if(ch == 'N')
        {       
            putchar(0x0D); 
            putchar(0x0A); 
            usart_send_string("Niki Nezakati");
            putchar(0x0D); 
            putchar(0x0A); 
            
        } 
        else if(ch == 'c')
        {
            for(counter =0; counter < 24; counter++)
            {          
                putchar(0x0D);   
                putchar(0x0A);
            }
        }
        else if(ch == 'M')
        {
            putchar(0x0D);   
            putchar(0x0A);
            lcd_clear();
            lcd_gotoxy(6,0);
            lcd_puts("Niki");
            lcd_gotoxy(4,1);
            lcd_puts("Nezakati");          
        }
          
      }        
}

