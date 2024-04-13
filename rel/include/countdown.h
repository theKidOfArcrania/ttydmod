#ifndef __COUNTDOWN
#define __COUNTDOWN

#ifdef __cplusplus
extern "C" {
#endif

#include <platform.h>

typedef struct CountdownWork {
  u8 field_0x0[0x40 - 0x0]; //0x0
} CountdownWork;

void countDownInit(void);
void countDownSaveReStart(void);



void countDownMain(void);

#ifdef __cplusplus
}
#endif

#endif
