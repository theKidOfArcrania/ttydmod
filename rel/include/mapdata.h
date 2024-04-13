#ifndef __MAPDATA
#define __MAPDATA

#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

void relSetEvtAddr(const char *name, int *script);

// TODO: flesh out these arguments
void relSetBtlAddr(const char *name, void *arg2, void *arg3);

#ifdef __cplusplus
}
#endif

#endif
