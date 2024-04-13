#ifndef _DRV_DISPDRV_H
#define _DRV_DISPDRV_H

#include <platform.h>
#include <drv/camdrv.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*DispCallback)(CameraId cameraId, void* param);

typedef struct DispEntry {
	u8 cameraId; //0x0, CameraId
	u8 renderMode; //0x1
  u16 padding; //0x2
	f32 order; //0x4
	DispCallback callback; //0x8
	void* param; //0xC
} DispEntry;

void dispInit(void);
void dispReInit(void);
void dispEntry(CameraId cameraId, s32 renderMode, f32 order, DispCallback callback, void* param);
void dispSort(void);
void dispDraw(CameraId cameraId);
f32 dispCalcZ(Vec* input);
DispEntry* dispGetCurWork(void);

#ifdef __cplusplus
}
#endif

#endif
