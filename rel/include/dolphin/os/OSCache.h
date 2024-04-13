#ifndef _OSCACHE_H_
#define _OSCACHE_H_

#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

void DCFlushRange(void* addr, size_t nbytes);
void DCStoreRange(void* addr, size_t nbytes);
void DCInvalidateRange(void* addr, size_t nbytes);
void DCFlushRangeNoSync(void* addr, size_t nbytes);
void ICFlashInvalidate(void);
void ICInvalidateRange(void* addr, size_t nbytes);
void LCDisable(void);
void __OSCacheInit(void);

void DCZeroRange(REGISTER void* addr, REGISTER size_t nbytes);
void ICEnable(void);
void __LCEnable(void);
void DCEnable(void);
void LCEnable(void);
u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes);
void LCQueueWait(REGISTER u32 len);
void L2GlobalInvalidate(void);
void L2Enable(void);
void LCStoreBlocks(void* dst, void* src, u32 nblocks);

#ifdef __cplusplus
}
#endif

#endif
