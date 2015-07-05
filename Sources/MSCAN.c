#include "includes.h"



#define CAN_ID_IDE   0x00080000UL      //MSCAN IDR寄存器组中扩展帧位

 //CAN发送程序
byte CAN0_TX(ulong id,                //标识符，四个字节
             byte isextend,           //扩展帧为1，否则为0
             byte isdataframe,        //数据帧为1，否则为0
             byte priority,           //优先级，最高为0
             byte length,             //数据长度
             byte *txdata)            //指向发送数据段的字节指针
  {           
  byte i;
  ulong idreg = 0;
  if (! (CAN0TFLG & 7)) {             
    return CAN_TXFULL;                //缓冲区已满
  }
  CAN0TBSEL = CAN0TFLG;               //选择发送缓冲区
  if (isextend) {                     //将ID格式转换为MSCAN中IDR的格式
    idreg = (((id & 0x1FFC0000UL) << 3)
                  | 0x00180000UL
                  | ((id & 0x0003FFFFUL) << 1));
  }else{
    idreg = id << 21;
  }
  if (!isdataframe) {                 //设置远程帧标志
    if (isextend) {
      idreg |= 1;  
    }else{
      idreg |= 0x100000UL;
    }
  }else{
    for (i = 0; i < length; i ++)     //设置数据
      * (&CAN0TXDSR0+i) = txdata[i];
  }
  * ((ulong*)((ulong)(&CAN0TXIDR0))) = idreg;    //设置ID
  
  CAN0TXDLR = length;                 //设置数据段长度
  CAN0TXTBPR = priority;              //设置优先级
  CAN0TFLG = CAN0TBSEL;               //启动发送
  return CAN_OK;
}



//CAN接收程序
byte CAN0_RX(ulong *id,               //接收的标识符
             byte *isextend,          //是否为扩展帧
             byte *isdataframe,       //是否为数据帧
             byte *length,            //接收的数据帧长度
             byte *rxdata)            //接收的数据段
{
  byte i;
  ulong idreg;
  if(!CAN0RFLG_RXF){
    return CAN_EMPTY;
  }
  idreg=*((ulong*)((ulong)(&CAN0RXIDR0)));
  if(idreg&CAN_ID_IDE){
    *isextend=1;
    *id=((idreg>>1)&0x3FFFFUL)|((idreg>>3)&0x1FFC0000UL);
    *isdataframe=(idreg&1)   ?0:1;
  } else{
    *isextend=0;
    *id=idreg>>21;
    *isdataframe=(idreg&0x100000UL) ?0:1;
  }
  if(*isdataframe){
    *length=CAN0RXDLR_DLC;
    for(i=0;i<*length;i++)
    rxdata[i]=*(&CAN0RXDSR0+i);
  }
  CAN0RFLG_RXF=1;
  return CAN_OK;
}







