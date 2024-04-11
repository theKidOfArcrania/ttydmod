#ifndef __MAPDATA
#define __MAPDATA

#include <platform.h>

void relSetEvtAddr(const char *name, int *script);

// TODO: flesh out these arguments
void relSetBtlAddr(const char *name, void *arg2, void *arg3);

#endif
