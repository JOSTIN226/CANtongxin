#ifndef MSCAN_H_
#define MSCAN_H_

#define CAN_OK1      0                 //发送成功标志定义
#define CAN_OK2      0                 //读取成功标志定义
#define CAN_EMPTY    2                 //缓存区为空标志定义
#define CAN_ID_IDE   0x00080000UL      //MSCAN IDR寄存器组中扩展帧位
#define CAN_TXFULL  1                 //缓冲区已满标志定义

byte CAN0_TX(ulong id, byte priority, byte length, byte *txdata);
byte CAN0_RX(ulong *id,byte *length,byte *rxdata);
#endif /* MSCAN_H_ */