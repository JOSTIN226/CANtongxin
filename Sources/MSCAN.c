#include "includes.h"


 //CAN���ͳ���
byte CAN0_TX(ulong id,                //��ʶ�����ĸ��ֽ�
             byte priority,           //���ȼ������Ϊ0
             byte length,             //���ݳ���
             byte *txdata)            //ָ�������ݶε��ֽ�ָ��
  {           
        byte i;
        ulong idreg = 0;
        if (! (CAN0TFLG & 7)) 
        {             
              return CAN_TXFULL;                //����������
        }
        CAN0TBSEL = CAN0TFLG;               //ѡ���ͻ�����

        idreg = id << 21;

        for (i = 0; i < length; i ++)     //��������
            * (&CAN0TXDSR0+i) = txdata[i];
            
        * ((ulong*)((ulong)(&CAN0TXIDR0))) = idreg;    //����ID
        
        CAN0TXDLR = length;                 //�������ݶγ���
        CAN0TXTBPR = priority;              //�������ȼ�
        CAN0TFLG = CAN0TBSEL;               //��������
        return CAN_OK;
}



//CAN���ճ���
byte CAN0_RX(ulong *id,               //���յı�ʶ��
             byte *length,            //���յ�����֡����
             byte *rxdata)            //���յ����ݶ�
{
        byte i;
        ulong idreg;
        if(!CAN0RFLG_RXF)
        {
              return CAN_EMPTY;
        }
        
        idreg=*((ulong*)((ulong)(&CAN0RXIDR0)));
        *id=idreg>>21;
        *length=CAN0RXDLR_DLC;
        
        for(i=0;i<*length;i++)
              rxdata[i]=*(&CAN0RXDSR0+i);
              
        CAN0RFLG_RXF=1;
        return CAN_OK;
}







