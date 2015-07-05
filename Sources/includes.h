#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "MSCAN.h"
#include "initial.h"

#define CAN_OK      0                 //发送成功标志定义
#define CAN_TXFULL  1                 //缓冲区已满标志定义
#define CAN_EMPTY    2                 //缓存区为空标志定义
