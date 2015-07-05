#include "includes.h"

byte data[]=0x55;

//1msÑÓÊ±³ÌÐò
void delay(word  xms) 
{
       word i,j;
       for(i=xms;i>0;i--)
       for(j=110;j>0;j--);
}
 
 
void main(void) 
{
  /* put your own code here */
    CAN_INIT();


	EnableInterrupts;


  for(;;) 
  {
           while(CAN0_TX(0x0000013F,0,1,data)!=CAN_OK);
           delay(2000);
           
  } /* loop forever */
  /* please make sure that you never leave main */
}



#pragma CODE_SEG NON_BANKED

void interrupt 38 ISR_CAN0Rx(void) 
{
      ulong id;
      byte length;
      byte data[8];
      if(CAN_OK==CAN0_RX(&id,&length,&data[0])) 
      {
            PORTA_PA0=~PORTA_PA0;
      }
}
#pragma CODE_SEG DEFAULT