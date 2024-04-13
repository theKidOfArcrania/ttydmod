#ifndef __EVT_EVT_LOTTERY
#define __EVT_EVT_LOTTERY

#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lottery_info {
  u16 mFlags; //0x0
  u8 field_0x2[0x40 - 0x2]; //0x2
} lottery_info;

lottery_info* lotteryGetPtr(void);

#ifdef __cplusplus
}
#endif

#endif
