#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "MSCAN.h"
#include "initial.h"

#define CAN_OK      0                 //���ͳɹ���־����
#define CAN_TXFULL  1                 //������������־����
#define CAN_EMPTY    2                 //������Ϊ�ձ�־����
