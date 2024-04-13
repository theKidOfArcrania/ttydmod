#ifndef DOLPHIN_OS_OSREBOOT_H
#define DOLPHIN_OS_OSREBOOT_H

#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

void __OSReboot(u32 resetCode, bool forceMenu);

void Run(Event);
void __OSReboot(u32 resetCode, bool forceMenu);

#ifdef __cplusplus
}
#endif

#endif
