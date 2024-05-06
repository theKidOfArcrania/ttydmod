#ifndef _PMARIO_SOUND_H
#define _PMARIO_SOUND_H

#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BGMList {
  const char* name;
  u32 field_0x4; //0x4, all of them are SND_ID_STREAMING?
  const char* field_0x8; //0x8, .stm name
  u8 field_0xC; //0xC
  u8 field_0xD; //0xD
  u8 field_0xE; //0xE
  u8 field_0xF; //0xF
} BGMList;

extern BGMList psbgmlist[];

#ifdef __cplusplus
}
#endif

#endif
