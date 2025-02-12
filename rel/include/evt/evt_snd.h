#ifndef __EVT_SND_H_
#define __EVT_SND_H_

#include <platform.h>
#include <mgr/evtmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

USERFUNC_DEF(evt_snd_bgmon);
USERFUNC_DEF(evt_snd_bgmoff);
USERFUNC_DEF(evt_snd_bgmoff_f);
USERFUNC_DEF(evt_snd_bgm_scope);
USERFUNC_DEF(evt_snd_envon);
USERFUNC_DEF(evt_snd_envoff);
USERFUNC_DEF(evt_snd_envoff_f);
USERFUNC_DEF(evt_snd_env_lpf);
USERFUNC_DEF(evt_snd_sfxon);
USERFUNC_DEF(evt_snd_sfx_pos);
USERFUNC_DEF(evt_snd_sfxon_3d);
USERFUNC_DEF(evt_snd_sfxoff);

#ifdef __cplusplus
}
#endif

#endif
