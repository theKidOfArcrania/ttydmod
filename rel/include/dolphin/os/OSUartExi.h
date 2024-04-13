#ifndef DOLPHIN_OS_OSUARTEXI_H
#define DOLPHIN_OS_OSUARTEXI_H

#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

s32 ReadUARTN(void);
void WriteUARTN(void);
s32 InitializeUART(void);

#ifdef __cplusplus
}
#endif

#endif
