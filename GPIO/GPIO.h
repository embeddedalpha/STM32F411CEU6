#ifndef _GPIO_H_
#define _GPIO_H_



#include "stm32f411xe.h"


#define GEN_PushPull_Output                    0x2C
#define GEN_PushPull_Output_PullUP             0x2D
#define GEN_PushPull_Output_PullDown           0x2E

#define GEN_PushPull_Output_OpenDrain          0x3C
#define GEN_PushPull_Output_OpenDrain_PullUP   0x3C
#define GEN_PushPull_Output_OpenDrain_PullDown 0x3C

#define ALT_PushPull_Output                    0x4C
#define ALT_PushPull_Output_PullUP             0x4D
#define ALT_PushPull_Output_PullDown           0x4E

#define ALT_PushPull_Output_OpenDrain          0x5C
#define ALT_PushPull_Output_OpenDrain_PullUP   0x5C
#define ALT_PushPull_Output_OpenDrain_PullDown 0x5C



void GPIO_Init(GPIO_TypeDef *GPIO,uint8_t pin, uint8_t config);











#endif

