#ifndef __EVT_UNSORTED_H_
#define __EVT_UNSORTED_H_

#include <platform.h>
#include <mgr/evtmgr.h>


//TODO: move this into proper sorted files

extern Bytecode door_open_se[];
extern Bytecode evt_door_entry[];
extern Bytecode evt_door_open_quick[];
extern Bytecode evt_sub_mail_vibration[];
extern Bytecode evt_sub_tree_access_entry[];
extern Bytecode evt_sub_kusa_access_entry[];

USERFUNC_DEF(evt_mario_balloon_bikkuri);
USERFUNC_DEF(evt_key_get_buttontrg);
USERFUNC_DEF(evt_sub_rumble_onoff);

USERFUNC_DEF(evt_party_stop);
USERFUNC_DEF(evt_party_get_pos);
USERFUNC_DEF(evt_party_set_pos);

USERFUNC_DEF(evt_mario_get_pos);
USERFUNC_DEF(evt_mario_set_pos);
USERFUNC_DEF(evt_mario_jump_pos);
USERFUNC_DEF(evt_mario_set_pose);
USERFUNC_DEF(evt_mario_mov_pos2);
USERFUNC_DEF(evt_mario_adjust_dir);
USERFUNC_DEF(evt_mario_set_dir);
USERFUNC_DEF(evt_mario_key_onoff);
USERFUNC_DEF(evt_mario_kill_party);
USERFUNC_DEF(evt_mario_balloon_off);

USERFUNC_DEF(evt_msg_print);

USERFUNC_DEF(evt_eff_fukidashi);

USERFUNC_DEF(evt_sub_intpl_msec_init);
USERFUNC_DEF(evt_sub_intpl_msec_get_value);

USERFUNC_DEF(evt_bg_set_color);

USERFUNC_DEF(evt_item_entry);
USERFUNC_DEF(evt_item_set_scale);
USERFUNC_DEF(evt_item_delete);

USERFUNC_DEF(evt_cam_shake);
USERFUNC_DEF(evt_eff64);

#endif
