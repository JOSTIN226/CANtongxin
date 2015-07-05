#ifndef MSCAN_H_
#define MSCAN_H_

#define CAN_OK1      0                 //���ͳɹ���־����
#define CAN_OK2      0                 //��ȡ�ɹ���־����
#define CAN_EMPTY    2                 //������Ϊ�ձ�־����
#define CAN_ID_IDE   0x00080000UL      //MSCAN IDR�Ĵ���������չ֡λ
#define CAN_TXFULL  1                 //������������־����

byte CAN0_TX(ulong id, byte priority, byte length, byte *txdata);
byte CAN0_RX(ulong *id,byte *length,byte *rxdata);
#endif /* MSCAN_H_ */