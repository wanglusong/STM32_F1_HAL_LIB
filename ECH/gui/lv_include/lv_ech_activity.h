#ifndef __LV_ECH_ACTIVITY_H_
#define __LV_ECH_ACTIVITY_H_

#include "lvgl.h"
#include "lv_ech.h"

enum
{
    ACT_ID_ECH_NONE,                    /* 0: invalid activity */
    ACT_ID_ECH_MEMBER_LIST,             /*1: member list*/
    ACT_ID_ECH_GROUP_LIST,              /*2: group list*/
    ACT_ID_ECH_GROUP_MEMBER_LIST,       /*3: group member list*/
    ACT_ID_ECH_MEMBER_CALL,             /*4: single call*/
    ACT_ID_ECH_IDLE,                    /*5: ech idle*/
    ACT_ID_ECH_MAIN_MENU,               /*6: main menu*/
    ACT_ID_ECH_MAKE_GROUP,              /*7: make group*/
    ACT_ID_ECH_MAIN_SETTING,            /*8: main setting*/
    ACT_ID_ECH_BRIGHT_TIME,             /*9: birght time*/
    ACT_ID_ECH_THEME_SWITCH,            /*10: theme switch*/
    ACT_ID_ECH_MAIN_SIM_CHOICE,         /*11: main SIM*/
    ACT_ID_ECH_NET_TYPE_CHOICE,         /*12: net type choice*/
    ACT_ID_ECH_ABOUT,                   /*13: about self*/
    ACT_ID_ECH_UPDATE_SOFTWARE,         /*14: update ui*/
    ACT_ID_ECH_EDEG_KEY_SET,            /*15: edeg key steting*/
    ACT_ID_ECH_VOLUM,                   /*16: turn volum*/
    ACT_ID_ECH_DISPLAY,                 /*17: display*/
    ACT_ID_ECH_WARNNING,                /*18: warn*/
    ACT_ID_ECH_LOCK_GROUP,              /*19: display*/
    ACT_ID_ECH_SHUTDOWN,                /*20: shutdown*/
    ACT_ID_ANYOBJ,                      /* : any object for example*/

    ACT_ID_MAX,
};
typedef uint8_t lv_ech_Activity_Id_t;

typedef lv_obj_t * (*lv_ech_activity_create_f_t)(lv_obj_t *);
typedef void (*lv_ech_activity_prepare_destory_f_t)(lv_obj_t *);

typedef struct
{
    lv_ech_Activity_Id_t actId;   /*activity id of the obj*/
    lv_ech_activity_create_f_t create;
    lv_ech_activity_prepare_destory_f_t prepare_destory;
} lv_ech_activity_ext_t;

#endif // __LV_ech_ACTIVITY_H_

