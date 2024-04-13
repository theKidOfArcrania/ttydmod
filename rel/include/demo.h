#ifndef _DEMO_H
#define _DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <platform.h>

void DEMOInitCaption(s32 type, s32 width, s32 height);
void DEMOPuts(s16 x, s16 y, s16 z, const char *text);
void DEMOPrintf(s16 x, s16 y, s16 z, char const* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
