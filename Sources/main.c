#include "includes.h"

void main(void) 
{
  /* put your own code here */
  CAN_INIT();


	EnableInterrupts;


  for(;;) {
  
 //   _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}



#pragma CODE_SEG NON_BANKED

void interrupt 38 ISR_CAN0Rx(void) 
{
      ulong id;
      byte isextend, isdataframe, length;
      byte data[8];
      if(CAN_OK==CAN0_RX(&id,&isextend,&isdataframe,&length,&data[0])) 
      {
        PORTA_PA0=~PORTA_PA0;
      }
}
#pragma CODE_SEG DEFAULT