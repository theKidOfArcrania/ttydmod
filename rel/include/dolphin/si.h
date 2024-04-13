#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

bool SIBusy();
bool SIIsChanBusy(u32 channel);
// local: CompleteTransfer
// local: SIInterruptHandler
// local: SIEnablePollingInterrupt
bool SIRegisterPollingHandler(void *handler);
bool SIUnregisterPollingHandler(void *handler);
void SIInit();
// local: __SITransfer
u32 SIGetStatus(u32 channel);
void SISetCommand(u32 channel, u32 command);
void SITransferCommands();
u32 SISetXY(u16 lineInterval, u8 count);
u32 SIEnablePolling(u32 pollMask);
u32 SIDisablePolling(u32 pollMask);
// local: SIGetResponseRaw
u32 SIGetResponse(u32 channel, void *buffer);
// local: AlarmHandler
u32 SITransfer(u32 channel, const void *bufferOut, u32 lengthOut, void *bufferIn, u32 lengthIn, void *callback);
// local: GetTypeCallback
u32 SIGetType(u32 channel);
u32 SIGetTypeAsync(u32 channel, void *callback);
u32 SIDecodeType(u32 value);
u32 SIProbe(u32 channel);
void SISetSamplingRate(u32 rate);
void SIRefreshSamplingRate();

#ifdef __cplusplus
}
#endif
