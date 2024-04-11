#include <platform.h>
#include <dolphin/gx.h>
#include <drv/dispdrv.h>
#include <evt/evt_bero.h>
#include <evt/evt_cam.h>
#include <evt/evt_fade.h>
#include <evt/evt_npc.h>
#include <evt/evt_map.h>
#include <evt/evt_seq.h>
#include <evt/evt_snd.h>
#include <evt/evt_sub.h>
#include <evt/evt_unsorted.h>
#include <mgr/evtmgr.h>
#include <mgr/evtmgr_cmd.h>
#include "aaa.h"
#include "aaa_00.h"

typedef struct MarioHouseWork {
	FileEntry* texture; //0x0
	s32 alpha; //0x4
} MarioHouseWork;

static const char str_A_ie_door_aaa_000004ac[] = "A_ie_door";
static const char str_A_ie_door_u_aaa_000004b8[] = "A_ie_door_u";
static const char str_S_ie_soto_aaa_000004c4[] = "S_ie_soto";
static const char str_A_ie_soto_aaa_000004d0[] = "A_ie_soto";
static const char str_A_naka1_aaa_000004e4[] = "A_naka1";
static const Vec vec3_aaa_000005d0 = { 0.0, 0.0, 0.0 };
static const Vec vec3_aaa_000005dc = { 1.0, 1.0, 1.0 };
static const char dat_aaa_000005e8[] = { 0, 0, 0, 0 };
static const float float_1000_aaa_000009ac = 1e3;
static NpcSetupInfo npcEnt[] = {
    {"\203p\203\214\203b\203^", 1073743360, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0 /* NpcTerritoryTypeNothing */, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.0, 0.0, 0.0, 0.0, 0},
    {"\203\213\203C\201[\203W", 1073743360, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0 /* NpcTerritoryTypeNothing */, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.0, 0.0, 0.0, 0.0, 0},
    {NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0 /* NpcTerritoryTypeNothing */, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.0, 0.0, 0.0, 0.0, 0}
};
static int evt_door[] = {
    MULF(LW(0), FLOAT(-0.55469))
    MULF(LW(0), FLOAT(-1.00000))
    CALL_CPP_SYNC(PTR(&evt_mapobj_rotate), 1, PTR("S_ie_door"), 0, LW(0), 0)
    RETURN()
    END_SCRIPT()
};
static int evt_door2[] = {
    MULF(LW(0), FLOAT(-0.50000))
    CALL_CPP_SYNC(PTR(&evt_mapobj_rotate), 1, PTR("S_ie_door"), 0, 0, LW(0))
    RETURN()
    END_SCRIPT()
};
static int evt_wall[] = {
    MULF(LW(0), FLOAT(0.75000))
    CALL_CPP_SYNC(PTR(&evt_mapobj_rotate), 1, PTR("S_ie_kaiten2"), LW(0), 0, 0)
    MULF(LW(0), FLOAT(-1.00000))
    CALL_CPP_SYNC(PTR(&evt_mapobj_rotate), 1, PTR("S_ie_kaiten1"), LW(0), 0, 0)
    RETURN()
    END_SCRIPT()
};
static void* ie_npc[] = { "\203\213\203C\201[\203W", (void*) NULL };
static int door_1_open[] = {
    CALL_CPP_SYNC(PTR(&evt_snd_bgmoff), 18432)
    CALL_CPP_SYNC(PTR(&evt_snd_envoff), 18432)
    CALL_CPP_SYNC(PTR(&evt_snd_env_lpf), 0, 800)
    RETURN()
    END_SCRIPT()
};
static int door_1_close[] = {
    CALL_CPP_SYNC(PTR(&evt_snd_bgmon), 160, 0)
    CALL_CPP_SYNC(PTR(&evt_snd_envon), 160, 0)
    CALL_CPP_SYNC(PTR(&evt_snd_env_lpf), 0, 0)
    RETURN()
    END_SCRIPT()
};
static char door_1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int evt_gameover[] = {
    WAIT_MS(700)

    // TODO: maybe would be good for some ? reaction

    // Luigi msg saying we are screwed
    CALL_CPP_SYNC(PTR(&evt_msg_print), 0, PTR("pro_10"), 0,
        PTR("\203\213\203C\201[\203W"))
    WAIT_MS(500)

    CALL_CPP_SYNC(PTR(&evt_mario_get_pos), 0, LW(0), LW(1), LW(2))
    CALL_CPP_SYNC(PTR(&evt_eff64), 0, PTR("broken_barrier_n64"), 2, LW(0), LW(1),
        LW(2), 1, 0x3c, 0, 0, 0, 0, 0, 0)
    CALL_CPP_SYNC(PTR(&evt_mario_set_pose), PTR("M_I_O"))
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_VOICE_MARIO_SURPRISED2"),
        LW(0), LW(1), LW(2))
    WAIT_MS(1100)

    // Play thunder/light effect
    CALL_CPP_SYNC(PTR(&evt_cam_shake), 4, FLOAT(0.01953125), FLOAT(0.0), 100)
    CALL_CPP_SYNC(PTR(&evt_eff64), 0, PTR("thunder_n64"), 4, LW(0), LW(1),
        LW(2), 1, 0x3c, 0, 0, 0, 0, 0, 0)
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_STG8_LIGHT1"), LW(0), LW(1),
        LW(2), 0)
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_ITEM_ICE_THUNDER_FALL1"),
        LW(0), LW(1), LW(2), 0)
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_VOICE_MARIO_LAND_DAMAGE2"),
        LW(0), LW(1), LW(2), 0)
    CALL_CPP_SYNC(PTR(&evt_mario_set_pose), PTR("M_D_1"))
    WAIT_MS(2000)

    // Mario is down
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_VOICE_MARIO_DOWN1"),
        LW(0), LW(1), LW(2), 0)
    CALL_CPP_SYNC(PTR(&evt_mario_set_pose), PTR("M_I_S"))
    WAIT_MS(2066)
    CALL_CPP_SYNC(PTR(&evt_mario_set_pose), PTR("M_D_2"))
    WAIT_MS(1000)

    // Game over scene
    CALL_CPP_SYNC(PTR(&evt_seq_set_seq), 5, 0, 0)
    WAIT_MS(1000)

    RETURN()
    END_SCRIPT()
};
static int evt_prologue[] = {
    BEGIN_THREAD()
        WAIT_MS(1500)
        CALL_CPP_SYNC(PTR(&evt_snd_bgmon), 512, PTR("BGM_EVT_MARIO_HOUSE1"))
    END_THREAD()
    CALL_CPP_SYNC(PTR(&evt_snd_envon), 272, PTR("ENV_OPN_AAA1"))
    CALL_CPP_SYNC(PTR(&evt_snd_bgm_scope), 0, 1)
    CALL_CPP_SYNC(PTR(&evt_cam_letter_box_onoff), 1, 1)
    CALL_CPP_SYNC(PTR(&evt_cam_letter_box_camid), 6)
    CALL_CPP_SYNC(PTR(&evt_npc_status_onoff), 1, PTR("\203\213\203C\201[\203W"), 2)
    CALL_CPP_SYNC(PTR(&evt_npc_status_onoff), 1, PTR("\203p\203\214\203b\203^"), 2)
    CALL_CPP_SYNC(PTR(&evt_party_stop), 0)
    CALL_CPP_SYNC(PTR(&evt_mario_key_onoff), 0)
    CALL_CPP_SYNC(PTR(&evt_mario_set_pos), -150, 30, -330)
    CALL_CPP_SYNC(PTR(&evt_party_set_pos), 0, -150, 30, -330)
    CALL_CPP_SYNC(PTR(&evt_cam3d_evt_set), 145, 122, 884, 145, 108, -180, 0, 11)
    CALL_CPP_SYNC(PTR(&evt_seq_wait), 2)
    CALL_CPP_SYNC(PTR(&evt_mario_set_pos), -150, 30, -330)
    CALL_CPP_SYNC(PTR(&evt_party_set_pos), 0, -150, 30, -330)
    BEGIN_THREAD()
        CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_init), 11, 0, 1500, 4000)
        LOOP(0)
            CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_get_value))
            DIVF(LW(0), FLOAT(10.00000))
            CALL_CPP_SYNC(PTR(&evt_mapobj_trans), 1, PTR("sai_ki2"), LW(0), 0, 0)
            MULF(LW(0), FLOAT(-1.00000))
            CALL_CPP_SYNC(PTR(&evt_mapobj_trans), 1, PTR("sai_ki1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQ(LW(1), 0)
                BREAK_LOOP()
            END_IF()
        END_LOOP()
    END_THREAD()
    CALL_CPP_SYNC(PTR(&evt_cam3d_evt_set), 145, 122, 717, 145, 108, -180, 5000, 11)
    WAIT_MS(4000)
    CALL_CPP_SYNC(PTR(&evt_npc_set_position), PTR("\203p\203\214\203b\203^"), 500, 500, 0)
    SET(GF(1), 0)
    BEGIN_THREAD()
        WAIT_MS(3000)
        LOOP(14)
            CALL_CPP_SYNC(PTR(&evt_npc_get_position), PTR("\203p\203\214\203b\203^"), LW(0), LW(1), LW(2))
            CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_EVT_OPN_PARETTA_MOVE1"), LW(0), LW(1), -100, 0)
            WAIT_MS(200)
        END_LOOP()
        LOOP(0)
            CALL_CPP_SYNC(PTR(&evt_npc_get_position), PTR("\203p\203\214\203b\203^"), LW(0), LW(1), LW(2))
            CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_EVT_OPN_PARETTA_MOVE1"), LW(0), LW(1), -100, 0)
            WAIT_MS(400)
            IF_INT_EQ(GF(1), 1)
                BREAK_LOOP()
            END_IF()
        END_LOOP()
        LOOP(17)
            CALL_CPP_SYNC(PTR(&evt_npc_get_position), PTR("\203p\203\214\203b\203^"), LW(0), LW(1), LW(2))
            CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_EVT_OPN_PARETTA_MOVE1"), LW(0), LW(1), -100, 0)
            WAIT_MS(200)
        END_LOOP()
    END_THREAD()
    CALL_CPP_SYNC(PTR(&evt_npc_glide_position), PTR("\203p\203\214\203b\203^"), 210, 25, -30, 0, FLOAT(80.00000), FLOAT(-30.00000), 11, 0)
    CALL_CPP_SYNC(PTR(&evt_npc_reverse_ry), PTR("\203p\203\214\203b\203^"))
    WAIT_MS(500)
    CALL_CPP_SYNC(PTR(&evt_mapobj_get_position), PTR("S_posuto"), LW(0), LW(1), LW(2))
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_EVT_POST_SHAKE1"), LW(0), LW(1), LW(2), 0)
    LOOP(3)
        CALL_CPP_SYNC(PTR(&evt_mapobj_trans), 1, PTR("S_posuto"), 2, 0, 0)
        WAIT_FRAMES(2)
        CALL_CPP_SYNC(PTR(&evt_mapobj_trans), 1, PTR("S_posuto"), 0, 0, 0)
        WAIT_FRAMES(2)
    END_LOOP()
    CALL_CPP_SYNC(PTR(&evt_npc_reverse_ry), PTR("\203p\203\214\203b\203^"))
    WAIT_MS(500)
    CALL_CPP_SYNC(PTR(&evt_msg_print), 0, PTR("pro_00"), 0, PTR("\203p\203\214\203b\203^"))
    SET(GF(1), 1)
    CALL_CPP_SYNC(PTR(&evt_npc_glide_position), PTR("\203p\203\214\203b\203^"), 0, 300, -100, 0, FLOAT(80.00000), FLOAT(-30.00000), 11, 0)
    CALL_CPP_SYNC(PTR(&evt_npc_set_position), PTR("\203\213\203C\201[\203W"), 20, 30, -150)
    CALL_CPP_SYNC(PTR(&evt_npc_set_ry), PTR("\203\213\203C\201[\203W"), 90)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 0, PTR("S_naka"), 1)
    CALL_CPP_SYNC(PTR(&evt_mapobj_get_position), PTR("S_ie_door"), LW(0), LW(1), LW(2))
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_DOOR_OPEN1"), LW(0), LW(1), LW(2), 0)
    CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_init), 11, 0, 180, 500)
    LOOP(0)
        CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_get_value))
        CALL_SCRIPT_SYNC(PTR(&evt_door))
        IF_INT_EQ(LW(1), 0)
            BREAK_LOOP()
        END_IF()
    END_LOOP()
    CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), 63, -110, 0, FLOAT(80.00000), 1)
    CALL_CPP_SYNC(PTR(&evt_mapobj_get_position), PTR("S_ie_door"), LW(0), LW(1), LW(2))
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_DOOR_SHUT1"), LW(0), LW(1), LW(2), 0)
    BEGIN_THREAD()
        CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_init), 11, 180, 0, 500)
        LOOP(0)
            CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_get_value))
            CALL_SCRIPT_SYNC(PTR(&evt_door))
            IF_INT_EQ(LW(1), 0)
                BREAK_LOOP()
            END_IF()
        END_LOOP()
    END_THREAD()
    CALL_CPP_SYNC(PTR(&evt_npc_flag_onoff), 1, PTR("\203\213\203C\201[\203W"), 131088)
    CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), 195, 0, 0, FLOAT(80.00000), 1)
    CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), 225, -75, 0, FLOAT(80.00000), 1)
    WAIT_MS(500)
    CALL_CPP_SYNC(PTR(&evt_mapobj_get_position), PTR("S_posuto"), LW(0), LW(1), LW(2))
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_EVT_POST_SHAKE1"), LW(0), LW(1), LW(2), 0)
    LOOP(3)
        CALL_CPP_SYNC(PTR(&evt_mapobj_trans), 1, PTR("S_posuto"), 2, 0, 0)
        WAIT_FRAMES(2)
        CALL_CPP_SYNC(PTR(&evt_mapobj_trans), 1, PTR("S_posuto"), 0, 0, 0)
        WAIT_FRAMES(2)
    END_LOOP()
    WAIT_MS(340)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_5"))
    WAIT_MS(500)
    CALL_CPP_SYNC(PTR(&evt_npc_flag_onoff), 0, PTR("\203\213\203C\201[\203W"), 1024)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_11"))
    CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), 195, 0, 0, FLOAT(80.00000), 1)
    CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), 63, -110, 0, FLOAT(80.00000), 1)
    CALL_CPP_SYNC(PTR(&evt_npc_flag_onoff), 0, PTR("\203\213\203C\201[\203W"), 131088)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_5"))
    CALL_CPP_SYNC(PTR(&evt_mapobj_get_position), PTR("S_ie_door"), LW(0), LW(1), LW(2))
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_DOOR_OPEN1"), LW(0), LW(1), LW(2), 0)
    CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_init), 11, 0, 180, 500)
    LOOP(0)
        CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_get_value))
        CALL_SCRIPT_SYNC(PTR(&evt_door))
        IF_INT_EQ(LW(1), 0)
            BREAK_LOOP()
        END_IF()
    END_LOOP()
    BEGIN_THREAD()
        CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_6"))
        CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), 25, -155, 0, FLOAT(80.00000), 1)
        CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_5"))
    END_THREAD()
    WAIT_MS(500)
    CALL_CPP_SYNC(PTR(&evt_cam3d_evt_set), -345, 154, 96, -32, 75, -217, 0, 11)
    WAIT_FRAMES(1)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 1, PTR("S_aaa_00"), 1)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 0, PTR("S_naka"), 1)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 0, PTR("S_ie_door"), 1)
    CALL_CPP_SYNC(PTR(&evt_bg_set_color), 0, 0, 0, 255)
    WAIT_FRAMES(1)
    CALL_CPP_SYNC(PTR(&evt_snd_bgmoff), 18432)
    CALL_CPP_SYNC(PTR(&evt_snd_envoff), 18432)
    CALL_CPP_SYNC(PTR(&evt_snd_env_lpf), 0, 800)
    CALL_CPP_SYNC(PTR(&evt_mapobj_get_position), PTR("S_ie_door"), LW(0), LW(1), LW(2))
    CALL_CPP_SYNC(PTR(&evt_snd_sfxon_3d), PTR("SFX_DOOR_SHUT1"), LW(0), LW(1), LW(2), 0)
    BEGIN_THREAD()
        CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_init), 11, 180, 0, 500)
        LOOP(0)
            CALL_CPP_SYNC(PTR(&evt_sub_intpl_msec_get_value))
            CALL_SCRIPT_SYNC(PTR(&evt_door))
            IF_INT_EQ(LW(1), 0)
                BREAK_LOOP()
            END_IF()
        END_LOOP()
    END_THREAD()
    WAIT_MS(500)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_5"))
    CALL_CPP_SYNC(PTR(&evt_npc_set_autotalkpose), PTR("\203\213\203C\201[\203W"), PTR("L_5"), PTR("L_7"))
    CALL_CPP_SYNC(PTR(&evt_msg_print), 0, PTR("pro_01"), 0, PTR("\203\213\203C\201[\203W"))
    CALL_CPP_SYNC(PTR(&evt_cam3d_evt_set), -376, 154, 65, -63, 75, -247, 2000, 11)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_6"))
    CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), 23, -156, 0, FLOAT(80.00000), 1)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_5"))
    BEGIN_THREAD()
        CALL_CPP_SYNC(PTR(&evt_mario_set_pos), -155, 30, -320)
        CALL_CPP_SYNC(PTR(&evt_mario_mov_pos2), -125, -290, FLOAT(80.00000))
        CALL_CPP_SYNC(PTR(&evt_mario_mov_pos2), -85, -310, FLOAT(80.00000))
        CALL_CPP_SYNC(PTR(&evt_mario_adjust_dir))
    END_THREAD()
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_6"))
    CALL_CPP_SYNC(PTR(&evt_npc_move_position), PTR("\203\213\203C\201[\203W"), -52, -275, 0, FLOAT(80.00000), 1)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_5"))
    WAIT_MS(500)
    CALL_CPP_SYNC(PTR(&evt_msg_print), 0, PTR("pro_02"), 0, PTR("\203\213\203C\201[\203W"))
    WAIT_MS(300)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_8"))
    CALL_CPP_SYNC(PTR(&evt_npc_set_autotalkpose), PTR("\203\213\203C\201[\203W"), PTR("L_8"), PTR("L_9"))
    CALL_CPP_SYNC(PTR(&evt_msg_print), 0, PTR("pro_03"), 0, PTR("\203\213\203C\201[\203W"))

    // Get the current save
    MO_SET_BASE_INT(0x80415fd0)
    MO_READ_INT(LW(0)) // *gp: GlobalWork
    MO_SET_BASE_INT(LW(0))
    MO_READ_INT_INDEXED(LW(0), 0x11d0 / 4) // gp->curr_save

    // Get the file name of the current save
    MO_SET_BASE_INT(0x8041eab8)
    MO_READ_INT(LW(2)) // *wp: CardWork
    MO_SET_BASE_INT(LW(2))
    MO_READ_INT_INDEXED(LW(2), 0xa8 / 4) // wp->data
    MUL(LW(0), 0x4000)
    ADD(LW(0), 0x31c4)
    ADD(LW(0), LW(2)) // &wp->data[wp->info->fileNo]->unk_11c4

    // Check to see if the name is correct
    CALL_CPP_SYNC(PTR(&check_name), LW(0), LW(1))
    IF_INT_EQ(LW(1), 0)
        // Failed
        CALL_SCRIPT_SYNC(PTR(&evt_gameover))
    ELSE()
        WAIT_MS(300)
        CALL_CPP_SYNC(PTR(&evt_cam_letter_box_camid), 10)
        CALL_CPP_SYNC(PTR(&evt_fade_set_mapchange_type), 1, 17, 800, 16, 800)
        CALL_CPP_SYNC(PTR(&evt_bero_mapchange), PTR("gor_10"), 0)
    END_IF()

    RETURN()
    END_SCRIPT()
};
static int evt_prologue2[] = {
    CALL_CPP_SYNC(PTR(&evt_snd_envoff), 513)
    CALL_CPP_SYNC(PTR(&evt_snd_envon), 288, 0)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 1, PTR("S_aaa_00"), 1)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 0, PTR("S_naka"), 1)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 0, PTR("S_ie_door"), 1)
    CALL_CPP_SYNC(PTR(&evt_bg_set_color), 0, 0, 0, 255)
    CALL_CPP_SYNC(PTR(&evt_mario_key_onoff), 0)
    CALL_CPP_SYNC(PTR(&evt_mario_set_pos), -85, 30, -310)
    CALL_CPP_SYNC(PTR(&evt_mario_set_dir), 90, 0, 0)
    CALL_CPP_SYNC(PTR(&evt_party_stop), 0)
    CALL_CPP_SYNC(PTR(&evt_npc_flag_onoff), 0, PTR("\203\213\203C\201[\203W"), 1024)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("L_8"))
    CALL_CPP_SYNC(PTR(&evt_npc_set_autotalkpose), PTR("\203\213\203C\201[\203W"), PTR("L_8"), PTR("L_9"))
    CALL_CPP_SYNC(PTR(&evt_npc_set_position), PTR("\203\213\203C\201[\203W"), -52, 30, -275)
    CALL_CPP_SYNC(PTR(&evt_npc_set_ry), PTR("\203\213\203C\201[\203W"), 270)
    CALL_CPP_SYNC(PTR(&evt_npc_flag_onoff), 1, PTR("\203\213\203C\201[\203W"), 32768)
    CALL_CPP_SYNC(PTR(&evt_cam3d_evt_set), -376, 154, 65, -63, 75, -247, 0, 11)
    CALL_CPP_SYNC(PTR(&evt_seq_wait), 2)
    CALL_CPP_SYNC(PTR(&evt_mario_set_dir), 90, 0, 0)
    CALL_CPP_SYNC(PTR(&evt_fade_end_wait))
    CALL_CPP_SYNC(PTR(&evt_cam_letter_box_camid), 8)
    CALL_CPP_SYNC(PTR(&evt_msg_print), 0, PTR("pro_05"), 0, PTR("\203\213\203C\201[\203W"))
    WAIT_MS(300)
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("I_1"))
    CALL_CPP_SYNC(PTR(&evt_npc_get_position), PTR("\203\213\203C\201[\203W"), LW(0), LW(1), LW(2))
    ADD(LW(0), -25)
    ADD(LW(1), 15)
    ADD(LW(2), -3)
    CALL_CPP_SYNC(PTR(&evt_item_entry), PTR("map"), 96, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL_CPP_SYNC(PTR(&evt_item_set_scale), PTR("map"), FLOAT(0.54980))
    WAIT_MS(1000)
    CALL_CPP_SYNC(PTR(&evt_item_delete), PTR("map"))
    CALL_CPP_SYNC(PTR(&evt_npc_set_anim), PTR("\203\213\203C\201[\203W"), PTR("S_1"))
    CALL_CPP_SYNC(PTR(&evt_mario_set_pose), PTR("M_L_3"))
    WAIT_MS(1500)
    SET(GF(0), 0)
    BEGIN_THREAD()
        CALL_CPP_SYNC(PTR(&mapdraw))
    END_THREAD()
    LOOP(0)
        IF_INT_EQ(GF(0), 1)
            BREAK_LOOP()
        END_IF()
        WAIT_FRAMES(1)
    END_LOOP()
    WAIT_MS(1000)
    CALL_CPP_SYNC(PTR(&evt_snd_bgmoff_f), 512, 2000)
    CALL_CPP_SYNC(PTR(&evt_snd_envoff), 512)
    CALL_CPP_SYNC(PTR(&evt_fade_set_mapchange_type), 1, 49, 0, 50, 0)
    SET(GSW(0), 2)
    CALL_CPP_SYNC(PTR(&evt_bero_mapchange), PTR("muj_20"), PTR("prologue"))
    RETURN()
    END_SCRIPT()
};
static TreeData ki_data[] = {
  {6, "A_ki_1", "S_ki_1", "S_ha_1", NULL, NULL},
  {7, NULL, NULL, NULL, NULL, NULL}
};
static KusaData kusa_data[] = {
  {0, "A_kusa_01", "S_kusa_01", NULL},
  {0, "A_kusa_02", "S_kusa_02", NULL},
  {0, "A_kusa_03", "S_kusa_03", NULL},
  {0, "A_kusa_04", "S_kusa_04", NULL},
  {0, "A_kusa_05", "S_kusa_05", NULL},
  {0, "A_kusa_06", "S_kusa_06", NULL},
  {0, "A_kusa_07", "S_kusa_07", NULL},
  {0, "A_kusa_08", "S_kusa_08", NULL},
  {0, "A_kusa_09", "S_kusa_09", NULL},
  {0, "A_kusa_10", "S_kusa_10", NULL},
  {4, NULL, NULL, NULL}
};
static BeroEntry bero_entry_data[] = {
    {"dokan_1", 2, 0, 9, 100000, 0, 0, 4294967295, NULL, 6, NULL, 0, "dokan_1", 1, 1, 0, 0},
    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0}
};
int aaa_00_init_evt[] = {
    SET(LW(0), PTR(&bero_entry_data))
    CALL_CPP_SYNC(PTR(&evt_bero_get_info))
    CALL_SCRIPT_SYNC(PTR(&evt_bero_info_run))
    CALL_CPP_SYNC(PTR(&evt_npc_setup), PTR(&npcEnt))
    SET(LW(0), PTR(&door_1))
    CALL_SCRIPT_SYNC(PTR(&evt_door_entry))
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 0, PTR("sai_ki1"), 2)
    CALL_CPP_SYNC(PTR(&evt_mapobj_flag_onoff), 1, 0, PTR("sai_ki2"), 2)
    CALL_CPP_SYNC(PTR(&evt_bero_get_entername), LW(0))
    IF_STRING_EQ(LW(0), PTR("prologue"))
        CALL_SCRIPT_ASYNC(PTR(&evt_prologue))
        WAIT_FRAMES(1)
        RETURN()
    END_IF()
    IF_STRING_EQ(LW(0), PTR("prologue2"))
        CALL_SCRIPT_ASYNC(PTR(&evt_prologue2))
        WAIT_FRAMES(1)
        RETURN()
    END_IF()
    IF_INT_EQ(GSW(0), 402)
        CALL_CPP_SYNC(PTR(&evt_mario_kill_party), 0)
        CALL_CPP_SYNC(PTR(&evt_bero_get_entername), LW(0))
    END_IF()
    SET(LW(0), PTR(&ki_data))
    CALL_SCRIPT_SYNC(PTR(&evt_sub_tree_access_entry))
    SET(LW(0), PTR(&kusa_data))
    CALL_SCRIPT_SYNC(PTR(&evt_sub_kusa_access_entry))
    RETURN()
    END_SCRIPT()
};
static MarioHouseWork *wp;


void mapdelete(void) {
    if (wp != NULL && wp->texture != NULL) {
        fileFree(wp->texture);
    }
}

// arg0: name
// arg1: ret
static EvtReturnCodes check_name(EventEntry* event, bool isFirstCall) {
  char* name = (char*)evtGetValue(event, event->args[0]);
  if (memcmp(name, "Password", 8)) {
    evtSetValue(event, event->args[1], 0);
  } else {
    evtSetValue(event, event->args[1], 1);
  }

  return EVT_RETURN_DONE;
}

static int mapdraw(EventEntry* event, bool isFirstCall) {
    if (isFirstCall) {
        wp = _mapAlloc(mapalloc_base_ptr, 8);
        memset(wp, 0, sizeof(MarioHouseWork));
        wp->texture = fileAllocf(4, "%s/mariost.tpl", getMarioStDvdRoot());
        wp->alpha = 0;
    }
    wp->alpha += 2;
    if (wp->alpha > 255) {
        wp->alpha = 255;
        evtSetValue(event, GF(0), 1); //done rolling in
    }
    dispEntry(CAMERA_3D, 7, draw, 1000.0f, wp);
    return EVT_RETURN_BLOCK;
}
static void draw(CameraId cameraId, void* param) {
    f32 old_viewport[GX_VIEWPORT_SZ];
    f32 old_projection[GX_PROJECTION_SZ];
    CameraEntry old_camera;
    Vec translate, scale;
    GXColor color;

    // Preserve old projection/views
    GXGetViewportv(old_viewport);
    GXGetProjectionv(old_projection);

    // Draw 2d texture onto screen
    GXSetProjection(camGetPtr(CAMERA_2D)->projection, camGetPtr(CAMERA_2D)->type);
    old_camera = *camGetCurPtr();
    *camGetCurPtr() = *camGetPtr(CAMERA_2D);
    winTexInit(*wp->texture->data);
    color = (GXColor){0xFF, 0xFF, 0xFF, (u8)wp->alpha};
    scale = vec3_aaa_000005dc;
    translate = vec3_aaa_000005d0;
    winTexSet(3, translate, scale, color); // render the map image

    // Restore old settings
    *camGetCurPtr() = old_camera;
    GXSetViewport(old_viewport[0], old_viewport[1], old_viewport[2],
         old_viewport[3], old_viewport[4], old_viewport[5]);
    GXSetProjectionv(old_projection);
}
