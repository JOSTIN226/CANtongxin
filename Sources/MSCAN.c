#include "includes.h"



#define CAN_ID_IDE   0x00080000UL      //MSCAN IDR�Ĵ���������չ֡λ

 //CAN���ͳ���
byte CAN0_TX(ulong id,                //��ʶ�����ĸ��ֽ�
             byte isextend,           //��չ֡Ϊ1������Ϊ0
             byte isdataframe,        //����֡Ϊ1������Ϊ0
             byte priority,           //���ȼ������Ϊ0
             byte length,             //���ݳ���
             byte *txdata)            //ָ�������ݶε��ֽ�ָ��
  {           
  byte i;
  ulong idreg = 0;
  if (! (CAN0TFLG & 7)) {             
    return CAN_TXFULL;                //����������
  }
  CAN0TBSEL = CAN0TFLG;               //ѡ���ͻ�����
  if (isextend) {                     //��ID��ʽת��ΪMSCAN��IDR�ĸ�ʽ
    idreg = (((id & 0x1FFC0000UL) << 3)
                  | 0x00180000UL
                  | ((id & 0x0003FFFFUL) << 1));
  }else{
    idreg = id << 21;
  }
  if (!isdataframe) {                 //����Զ��֡��־
    if (isextend) {
      idreg |= 1;  
    }else{
      idreg |= 0x100000UL;
    }
  }else{
    for (i = 0; i < length; i ++)     //��������
      * (&CAN0TXDSR0+i) = txdata[i];
  }
  * ((ulong*)((ulong)(&CAN0TXIDR0))) = idreg;    //����ID
  
  CAN0TXDLR = length;                 //�������ݶγ���
  CAN0TXTBPR = priority;              //�������ȼ�
  CAN0TFLG = CAN0TBSEL;               //��������
  return CAN_OK;
}



//CAN���ճ���
byte CAN0_RX(ulong *id,               //���յı�ʶ��
             byte *isextend,          //�Ƿ�Ϊ��չ֡
             byte *isdataframe,       //�Ƿ�Ϊ����֡
             byte *length,            //���յ�����֡����
             byte *rxdata)            //���յ����ݶ�
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







