#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy_as4(void *dst, void *src, u32 size);
// mtxGetRotationElement

float sysMsec2FrameFloat(float milliseconds);
u32 sysMsec2Frame(u32 milliseconds);
float sysFrame2SecFloat(float frames);
// getV60FPS
void sysDummyDraw(float matrix[3][4]);
void sysWaitDrawSync();
u16 sysGetToken();

u32 irand(u32 range);
void movePos(float magnitude, float direction, float *x, float *y);
void sincosf(float angle, float *sin, float *cos);

u8 padGetRumbleStatus(u32 padId);
void padRumbleHardOff(u32 padId);
void padRumbleOff(u32 padId);
void padRumbleOn(u32 padId);

s8 keyGetSubStickY(u32 padId);
s8 keyGetStickY(u32 padId);
s8 keyGetStickX(u32 padId);
u32 keyGetButtonTrg(u32 padId);
u32 keyGetDirTrg(u32 padId);
u32 keyGetButtonRep(u32 padId);
u32 keyGetDirRep(u32 padId);
u32 keyGetButton(u32 padId);
u32 keyGetDir(u32 padId);
void makeKey();

// qqsort
// intplGetValue
// angleABf
// compAngle
// distABf
// reviseAngle
const char *getMarioStDvdRoot();

#ifdef __cplusplus
}
#endif
