
// Niki Nezakati - 98522094
/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
? Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :  LAB 8
Version : 
Date    :  4/23/2022
Author  :  Niki Nezakati - 98522094
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
#include <delay.h>      
#include <stdlib.h>

// Declare your global variables here

#define KEYPAD_R1 PORTD.0
#define KEYPAD_R2 PORTD.1
#define KEYPAD_R3 PORTD.2
#define KEYPAD_R4 PORTD.3
#define KEYPAD_C1 PIND.4
#define KEYPAD_C2 PIND.5
#define KEYPAD_C3 PIND.6
#define KEYPAD_C4 PIND.7

#define KEYPAD_NUM0 0
#define KEYPAD_NUM1 1
#define KEYPAD_NUM2 2
#define KEYPAD_NUM3 3
#define KEYPAD_NUM4 4
#define KEYPAD_NUM5 5
#define KEYPAD_NUM6 6
#define KEYPAD_NUM7 7
#define KEYPAD_NUM8 8
#define KEYPAD_NUM9 9
#define KEYPAD_DIV  10
#define KEYPAD_MUL  11
#define KEYPAD_PLS  12
#define KEYPAD_MNS  13
#define KEYPAD_EQU  14
#define KEYPAD_ON   15

float number[3];
char operand;
int counter = 0;
char show[5];
unsigned char key_result;  

unsigned char keypad_scan()
{
    unsigned char result=255;
    ////////////////////////  ROW1 ////////////////////////
    KEYPAD_R1 = 1; KEYPAD_R2 = 0;  KEYPAD_R3 = 0;  KEYPAD_R4 = 0; //set Row1 for Keypad
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_NUM7;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM8;
    else if (KEYPAD_C3)
        result = KEYPAD_NUM9;
    else if (KEYPAD_C4)
        result = KEYPAD_DIV;

    ////////////////////////  ROW2 ////////////////////////
    KEYPAD_R1 = 0; KEYPAD_R2 = 1;  KEYPAD_R3 = 0;  KEYPAD_R4 = 0; //set Row2 for Keypad
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_NUM4;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM5;
    else if (KEYPAD_C3)
        result = KEYPAD_NUM6;
    else if (KEYPAD_C4)
        result = KEYPAD_MUL;

    ////////////////////////  ROW3 ////////////////////////
    KEYPAD_R1 = 0; KEYPAD_R2 = 0;  KEYPAD_R3 = 1;  KEYPAD_R4 = 0; //set Row3 for Keypad
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_NUM1;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM2;
    else if (KEYPAD_C3)
        result = KEYPAD_NUM3;
    else if (KEYPAD_C4)
        result = KEYPAD_MNS;

    ////////////////////////  ROW4 ////////////////////////
    KEYPAD_R1 = 0; KEYPAD_R2 = 0;  KEYPAD_R3 = 0;  KEYPAD_R4 = 1; //set Row4 for Keypad
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_ON;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM0;
    else if (KEYPAD_C3)
        result = KEYPAD_EQU;
    else if (KEYPAD_C4)
        result = KEYPAD_PLS;

    return result;
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

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


DDRC=0xFF;
DDRD=0x0F;
PORTC=0x00;

lcd_init(16);
lcd_clear();
lcd_gotoxy(3,0);
lcd_puts("Calculator");
lcd_gotoxy(5,1);
lcd_puts("Project");
delay_ms(2000);
lcd_clear();

while (1)
    {
          key_result = keypad_scan();
          if(key_result != 255)
          { 
              while(keypad_scan() != 255);
              delay_ms(20);  
              
              if (key_result == KEYPAD_DIV)
              {
                  lcd_putchar('%');
                  counter++;
                  operand = '%';
              }
              else if (key_result == KEYPAD_MUL)
              {
                  lcd_putchar('*');
                  counter++;
                  operand = '*';
              } 
              else if (key_result == KEYPAD_MNS)
              {
                  lcd_putchar('-');
                  counter++;
                  operand = '-';
              }
              else if (key_result == KEYPAD_PLS)
              {
                  lcd_putchar('+');
                  counter++;
                  operand = '+';
              }
              else if (key_result == KEYPAD_EQU)
              {
                  lcd_putchar('=');
                  if(operand == '%')
                  {         
                    number[2] = number[0] / number[1];
                  }  
                  else if(operand == '*')
                  {         
                    number[2] = number[0] * number[1];
                  }              
                  else if(operand == '-')
                  {         
                    number[2] = number[0] - number[1];
                  }
                  else if(operand == '+')
                  {         
                    number[2] = number[0] + number[1];
                  }                
                  ftoa(number[2],2,show);  
                  lcd_puts(show); 
              }
              else if (key_result == KEYPAD_ON)
              {
                  lcd_clear();
                  lcd_gotoxy(0,0);
                  number[2] = 0;   
                  number[1] = 0;
                  number[0] = 0;  
                  operand = '';
                  counter = 0;    
                  lcd_clear();
              }                               
              else
              {
                  lcd_putchar(key_result + 48);
                  number[counter] *= 10;
                  number[counter] += key_result;
              }    
              
          }
      }
}
