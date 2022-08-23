// must run on Matrix_5x7_Col
// Moving an Arrow 
#include <mega32.h>
#include <delay.h>

unsigned char Code[]= {
    0xFF,    //    0001        # # # # # # # # 
    0xFF,    //    0002        # # # # # # # # 
    0xFF,    //    0003        # # # # # # # # 
    0xFF,    //    0004        # # # # # # # # 
    0xFF,    //    0005        # # # # # # # # 
   
    0x03,    //    0010        . . . . . . # # 
    0xEC,    //    0011        # # # . # # . . 
    0xEE,    //    0012        # # # . # # # . 
    0xEC,    //    0013        # # # . # # . . 
    0x03,    //    0014        . . . . . . # # 
    
    0x00,    //    0016        . . . . . . . . 
    0x6E,    //    0017        . # # . # # # . 
    0x6E,    //    0018        . # # . # # # . 
    0x6E,    //    0019        . # # . # # # . 
    0x91,    //    001A        # . . # . . . # 
    
    0x81,    //    001C        # . . . . . . # 
    0x7C,    //    001D        . # # # # # . . 
    0x7E,    //    001E        . # # # # # # . 
    0x7E,    //    001F        . # # # # # # . 
    0x7E,    //    0020        . # # # # # # . 
    0x9D,    //    0021        # . . # # # . #   
           
    0xFF,    //    000A        # # # # # # # # 
    0xFF,    //    000B        # # # # # # # # 
    0xFF,    //    000C        # # # # # # # # 
    0xFF,    //    000D        # # # # # # # # 
    0xFF,    //    000E        # # # # # # # # 
    0xFF,    //    000F        # # # # # # # # 
   
    };
void main(void)
{
unsigned char Col,Scan,Refresh,Index,S;
DDRC=0xFF;
DDRD=0xFF;

while (1)
      {
      // Place your code here
      for (S=0; S<16; S++)
      {
        for (Refresh=1; Refresh<17; Refresh++)
        {
            Scan = 0b00000001;
            for (Col=0; Col<5; Col++)
            {
                Index = S + Col;
                PORTD = Code[Index];
                PORTC = Scan;
                delay_ms(4);
                Scan = Scan << 1;
                PORTC = 0x00;
            }
        }
      }
      }
}