#ifndef DOLPHIN_OS_OSSYNC_H
#define DOLPHIN_OS_OSSYNC_H

#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

void __OSSystemCallVector(void);
void __OSInitSystemCall(void);

#ifdef __cplusplus
}
#endif

#endif
