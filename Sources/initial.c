#include "includes.h"



void CAN_INIT(void) 
{
//        CAN0CTL0_SLPRQ=1
//        while (CAN0CTL1_SLPAK==0);  
          CAN0CTL0_INITRQ=1;
          while (CAN0CTL1_INITAK==0);  //等待进入初始化状态
          CAN0CTL1=0x81;
          CAN0BTR0=0xc7;     //BRP=7  SJW=3
          CAN0BTR1=0x3A;  //TSEG1=10      TSEG2=3 sample=1
          CAN0IDAC=0;       //滤波方式
          CAN0IDAR0=0x27;        //0x13F
          CAN0IDAR1=0xE0;
          CAN0IDAR2=0x00;
          CAN0IDAR3=0x00;
          CAN0IDAR4=0x27;        //0x13F
          CAN0IDAR5=0xE0;
          CAN0IDAR6=0x00;
          CAN0IDAR7=0x00;
          CAN0IDMR0=0x00;    //全部比对
          CAN0IDMR1=0x00;      
          CAN0IDMR2=0x00;
          CAN0IDMR3=0x00;
          CAN0IDMR4=0x00;
          CAN0IDMR5=0x00;          
          CAN0IDMR6=0x00;
          CAN0IDMR7=0x00;          
          CAN0CTL0_INITRQ=0;//退出初始化
          while (CAN0CTL1_INITAK);
          CAN0CTL0=0x08;
          CAN0RIER=0x01;   //打开接收中断
          CAN0TIER=0x00;   //关闭发送中断
}