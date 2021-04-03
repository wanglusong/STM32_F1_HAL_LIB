#ifndef __LV_OBJ_PORT_H_
#define __LV_OBJ_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
*
*                  INCLUDE
*
*************************************************/
#include "lvgl.h"
#include "lv_ech.h"
#include <stdarg.h>
/*************************************************
*
*                  DEFINE
*
*************************************************/
	
#define LV_ech_STABAR_TASK_EXT_LENGTH (20)

#define LV_ech_SCREEN_SCALE_HOR_RES (LV_HOR_RES)
#define LV_ech_SCREEN_SCALE_VER_RES (LV_VER_RES)


//屏幕的零点位置
#define LV_ech_SCREEN_X           (0)
#define LV_ech_SCREEN_Y           (0)


//状态栏的位置
#define LV_ech_STATUS_BAR_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_STATUS_BAR_VER_RES (LV_ech_SCREEN_SCALE_VER_RES/7)
#define LV_ech_STATUS_BAR_OFFSET_X   0
#define LV_ech_STATUS_BAR_OFFSET_Y   0
#define LV_ech_STATUS_BAR_X0   (LV_ech_SCREEN_X + LV_ech_STATUS_BAR_OFFSET_X)
#define LV_ech_STATUS_BAR_Y0   (LV_ech_SCREEN_Y + LV_ech_STATUS_BAR_OFFSET_Y)
#define LV_ech_STATUS_BAR_X1   (LV_ech_STATUS_BAR_X0 + LV_ech_STATUS_BAR_HOR_RES - 1)
#define LV_ech_STATUS_BAR_Y1   (LV_ech_STATUS_BAR_Y0 + LV_ech_STATUS_BAR_VER_RES - 1)
#define LV_ech_STATUS_BAR_POSITION_X  (LV_ech_STATUS_BAR_X0)
#define LV_ech_STATUS_BAR_POSITION_Y  (LV_ech_STATUS_BAR_Y0)

//控制栏尺寸以及偏移
#define LV_ech_CONTROL_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_CONTROL_VER_RES (LV_ech_SCREEN_SCALE_VER_RES/7)
#define LV_ech_CONTROL_OFFSET_X   (0)
#define LV_ech_CONTROL_OFFSET_Y   (0)


//显示栏偏移
#define LV_ech_DISPLAY_OFFSET_X   (0)
#define LV_ech_DISPLAY_OFFSET_Y   (0)


//有状态栏和控制栏的显示区域的位置
#define LV_ech_DISPLAY_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_DISPLAY_VER_RES (LV_ech_SCREEN_SCALE_VER_RES - LV_ech_STATUS_BAR_VER_RES - LV_ech_CONTROL_VER_RES)
#define LV_ech_DISPLAY_X0   (LV_ech_SCREEN_X + LV_ech_DISPLAY_OFFSET_X)
#define LV_ech_DISPLAY_Y0   (LV_ech_SCREEN_Y + LV_ech_DISPLAY_OFFSET_Y)
#define LV_ech_DISPLAY_X1   (LV_ech_DISPLAY_X0 + LV_ech_DISPLAY_HOR_RES - 1)
#define LV_ech_DISPLAY_Y1   (LV_ech_DISPLAY_Y0 + LV_ech_DISPLAY_VER_RES - 1)
#define LV_ech_DISPLAY_POSITION_X  (LV_ech_DISPLAY_X0)
#define LV_ech_DISPLAY_POSITION_Y  (LV_ech_DISPLAY_Y0)


//无控制栏有状态栏的显示区域位置
#define LV_ech_DISPLAY_NOCTR_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_DISPLAY_NOCTR_VER_RES (LV_ech_SCREEN_SCALE_VER_RES - LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_DISPLAY_NOCTR_X0   (LV_ech_SCREEN_X + LV_ech_DISPLAY_OFFSET_X)
#define LV_ech_DISPLAY_NOCTR_Y0   (LV_ech_SCREEN_Y + LV_ech_DISPLAY_OFFSET_Y + LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_DISPLAY_NOCTR_X1   (LV_ech_DISPLAY_NOCTR_X0 + LV_ech_DISPLAY_NOCTR_HOR_RES - 1)
#define LV_ech_DISPLAY_NOCTR_Y1   (LV_ech_DISPLAY_NOCTR_Y0 + LV_ech_DISPLAY_NOCTR_VER_RES - 1)
#define LV_ech_DISPLAY_NOCTR_POSITION_X  (LV_ech_DISPLAY_NOCTR_X0)
#define LV_ech_DISPLAY_NOCTR_POSITION_Y  (LV_ech_DISPLAY_NOCTR_Y0)

//有状态栏时显示base
#define LV_ech_DISPLAY_STABAR_BASE_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_DISPLAY_STABAR_BASE_VER_RES (LV_ech_SCREEN_SCALE_VER_RES - LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_DISPLAY_STABAR_BASE_X0   (LV_ech_SCREEN_X + LV_ech_DISPLAY_OFFSET_X)
#define LV_ech_DISPLAY_STABAR_BASE_Y0   (LV_ech_SCREEN_Y + LV_ech_DISPLAY_OFFSET_Y + LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_DISPLAY_STABAR_BASE_X1   (LV_ech_DISPLAY_STABAR_BASE_X0 + LV_ech_DISPLAY_STABAR_BASE_HOR_RES - 1)
#define LV_ech_DISPLAY_STABAR_BASE_Y1   (LV_ech_DISPLAY_STABAR_BASE_Y0 + LV_ech_DISPLAY_STABAR_BASE_VER_RES - 1)
#define LV_ech_DISPLAY_STABAR_BASE_POSITION_X  (LV_ech_DISPLAY_STABAR_BASE_X0)
#define LV_ech_DISPLAY_STABAR_BASE_POSITION_Y  (LV_ech_DISPLAY_STABAR_BASE_Y0)



//有状态栏的控制栏位置
#define LV_ech_CONTROL_X0   (LV_ech_SCREEN_X + LV_ech_CONTROL_OFFSET_X)
#define LV_ech_CONTROL_Y0   (LV_ech_SCREEN_Y + LV_ech_CONTROL_OFFSET_Y + LV_ech_DISPLAY_VER_RES)
#define LV_ech_CONTROL_X1   (LV_ech_CONTROL_X0 + LV_ech_CONTROL_HOR_RES - 1)
#define LV_ech_CONTROL_Y1   (LV_ech_CONTROL_Y0 + LV_ech_CONTROL_VER_RES - 1)
#define LV_ech_CONTROL_POSITION_X  (LV_ech_CONTROL_X0)
#define LV_ech_CONTROL_POSITION_Y  (LV_ech_CONTROL_Y0)


#if 1

//无状态栏有控制栏的显示区域位置
#define LV_ech_DISPLAY_NOSTABAR_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_DISPLAY_NOSTABAR_VER_RES (LV_ech_SCREEN_SCALE_VER_RES - LV_ech_CONTROL_VER_RES)
#define LV_ech_DISPLAY_NOSTABAR_X0   (LV_ech_SCREEN_X + LV_ech_DISPLAY_OFFSET_X)
#define LV_ech_DISPLAY_NOSTABAR_Y0   (LV_ech_SCREEN_Y + LV_ech_DISPLAY_OFFSET_Y)
#define LV_ech_DISPLAY_NOSTABAR_X1   (LV_ech_DISPLAY_NOSTABAR_X0 + LV_ech_DISPLAY_NOSTABAR_HOR_RES - 1)
#define LV_ech_DISPLAY_NOSTABAR_Y1   (LV_ech_DISPLAY_NOSTABAR_Y0 + LV_ech_DISPLAY_NOSTABAR_VER_RES - 1)
#define LV_ech_DISPLAY_NOSTABAR_POSITION_X  (LV_ech_DISPLAY_NOSTABAR_X0)
#define LV_ech_DISPLAY_NOSTABAR_POSITION_Y  (LV_ech_DISPLAY_NOSTABAR_Y0)



//无状态栏和控制栏时的显示区域位置
#define LV_ech_DISPLAY_NOCTR_STABAR_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_DISPLAY_NOCTR_STABAR_VER_RES (LV_ech_SCREEN_SCALE_VER_RES)
#define LV_ech_DISPLAY_NOCTR_STABAR_X0   (LV_ech_SCREEN_X + LV_ech_DISPLAY_OFFSET_X)
#define LV_ech_DISPLAY_NOCTR_STABAR_Y0   (LV_ech_SCREEN_Y + LV_ech_DISPLAY_OFFSET_Y)
#define LV_ech_DISPLAY_NOCTR_STABAR_X1   (LV_ech_DISPLAY_NOCTR_STABAR_X0 + LV_ech_DISPLAY_NOCTR_STABAR_HOR_RES - 1)
#define LV_ech_DISPLAY_NOCTR_STABAR_Y1   (LV_ech_DISPLAY_NOCTR_STABAR_Y0 + LV_ech_DISPLAY_NOCTR_STABAR_VER_RES - 1)
#define LV_ech_DISPLAY_NOCTR_STABAR_POSITION_X  (LV_ech_DISPLAY_NOCTR_STABAR_X0)
#define LV_ech_DISPLAY_NOCTR_STABAR_POSITION_Y  (LV_ech_DISPLAY_NOCTR_STABAR_Y0)

//无状态栏时显示base
#define LV_ech_DISPLAY_NOSTABAR_BASE_HOR_RES (LV_ech_SCREEN_SCALE_HOR_RES)
#define LV_ech_DISPLAY_NOSTABAR_BASE_VER_RES (LV_ech_SCREEN_SCALE_VER_RES)
#define LV_ech_DISPLAY_NOSTABAR_BASE_X0   (LV_ech_SCREEN_X + LV_ech_DISPLAY_OFFSET_X)
#define LV_ech_DISPLAY_NOSTABAR_BASE_Y0   (LV_ech_SCREEN_Y + LV_ech_DISPLAY_OFFSET_Y)
#define LV_ech_DISPLAY_NOSTABAR_BASE_X1   (LV_ech_DISPLAY_NOSTABAR_BASE_X0 + LV_ech_DISPLAY_NOSTABAR_BASE_HOR_RES - 1)
#define LV_ech_DISPLAY_NOSTABAR_BASE_Y1   (LV_ech_DISPLAY_NOSTABAR_BASE_Y0 + LV_ech_DISPLAY_NOSTABAR_BASE_VER_RES - 1)
#define LV_ech_DISPLAY_NOSTABAR_BASE_POSITION_X  (LV_ech_DISPLAY_NOSTABAR_BASE_X0)
#define LV_ech_DISPLAY_NOSTABAR_BASE_POSITION_Y  (LV_ech_DISPLAY_NOSTABAR_BASE_Y0)


//无状态栏的控制栏位置
#define LV_ech_CONTROL_NOSTABAR_X0   (LV_ech_SCREEN_X + LV_ech_CONTROL_OFFSET_X)
#define LV_ech_CONTROL_NOSTABAR_Y0   (LV_ech_SCREEN_Y + LV_ech_CONTROL_OFFSET_Y + LV_ech_DISPLAY_NOSTABAR_VER_RES)
#define LV_ech_CONTROL_NOSTABAR_X1   (LV_ech_CONTROL_NOSTABAR_X0 + LV_ech_CONTROL_HOR_RES)
#define LV_ech_CONTROL_NOSTABAR_Y1   (LV_ech_CONTROL_NOSTABAR_Y0 + LV_ech_CONTROL_VER_RES - 1)
#define LV_ech_CONTROL_NOSTABAR_POSITION_X  (LV_ech_CONTROL_NOSTABAR_X0)
#define LV_ech_CONTROL_NOSTABAR_POSITION_Y  (LV_ech_CONTROL_NOSTABAR_Y0)

#endif


//状态栏时间label位置信息
#define LV_ech_STABAR_TIME_HOR_RES       (LV_ech_SCREEN_SCALE_HOR_RES/5)
#define LV_ech_STABAR_TIME_VER_RES       (LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_STABAR_TIME_OFFSET_X      (4)
#define LV_ech_STABAR_TIME_OFFSET_Y      (4)
#define LV_ech_STABAR_TIME_X0             (LV_ech_SCREEN_X + LV_ech_STABAR_TIME_OFFSET_X)
#define LV_ech_STABAR_TIME_Y0             (LV_ech_SCREEN_Y + LV_ech_STABAR_TIME_OFFSET_Y)
#define LV_ech_STABAR_TIME_X1             (LV_ech_SCREEN_X + LV_ech_STABAR_TIME_OFFSET_X + LV_ech_STABAR_TIME_HOR_RES - 1)
#define LV_ech_STABAR_TIME_X2             (LV_ech_SCREEN_Y + LV_ech_STABAR_TIME_OFFSET_Y + LV_ech_STABAR_TIME_VER_RES - 1)
#define LV_ech_STABAR_TIME_POSITION_X    (LV_ech_STABAR_TIME_X0)
#define LV_ech_STABAR_TIME_POSITION_Y    (LV_ech_STABAR_TIME_Y0)


//状态栏电池位置信息
#define LV_ech_STABAR_BATTERY_HOR_RES    (LV_ech_SCREEN_SCALE_HOR_RES/12)
#define LV_ech_STABAR_BATTERY_VER_RES    (LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_STABAR_BATTERY_OFFSET_X   (0-2)
#define LV_ech_STABAR_BATTERY_OFFSET_Y   (1)
#define LV_ech_STABAR_BATTERY_X0          (LV_ech_SCREEN_X + LV_ech_STABAR_BATTERY_OFFSET_X + LV_ech_SCREEN_SCALE_HOR_RES - LV_ech_STABAR_BATTERY_HOR_RES - 1)
#define LV_ech_STABAR_BATTERY_Y0          (LV_ech_SCREEN_Y + LV_ech_STABAR_BATTERY_OFFSET_Y)
#define LV_ech_STABAR_BATTERY_X1          (LV_ech_SCREEN_X + LV_ech_STABAR_BATTERY_OFFSET_X + LV_ech_SCREEN_SCALE_HOR_RES - 1)
#define LV_ech_STABAR_BATTERY_Y1          (LV_ech_SCREEN_Y + LV_ech_STABAR_BATTERY_OFFSET_Y + LV_ech_STABAR_BATTERY_VER_RES - 1)
#define LV_ech_STABAR_BATTERY_POSITION_X (LV_ech_STABAR_BATTERY_X0)
#define LV_ech_STABAR_BATTERY_POSITION_Y (LV_ech_STABAR_BATTERY_Y0)


//状态栏SIM卡信息位置1
#define LV_ech_STABAR_SIM_1_HOR_RES    (LV_ech_SCREEN_SCALE_HOR_RES/12)
#define LV_ech_STABAR_SIM_1_VER_RES    (LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_STABAR_SIM_1_OFFSET_X   (-1)
#define LV_ech_STABAR_SIM_1_OFFSET_Y   (1)
#define LV_ech_STABAR_SIM_1_X0          (LV_ech_SCREEN_X + LV_ech_STABAR_SIM_1_OFFSET_X + LV_ech_SCREEN_SCALE_HOR_RES - LV_ech_STABAR_BATTERY_HOR_RES - LV_ech_STABAR_SIM_1_HOR_RES - 1)
#define LV_ech_STABAR_SIM_1_Y0          (LV_ech_SCREEN_Y + LV_ech_STABAR_SIM_1_OFFSET_Y)
#define LV_ech_STABAR_SIM_1_X1          (LV_ech_SCREEN_X + LV_ech_STABAR_SIM_1_OFFSET_X + LV_ech_SCREEN_SCALE_HOR_RES - LV_ech_STABAR_BATTERY_HOR_RES - 1)
#define LV_ech_STABAR_SIM_1_Y1          (LV_ech_SCREEN_Y + LV_ech_STABAR_SIM_1_OFFSET_Y + LV_ech_STABAR_SIM_1_VER_RES - 1)
#define LV_ech_STABAR_SIM_1_POSITION_X (LV_ech_STABAR_SIM_1_X0)
#define LV_ech_STABAR_SIM_1_POSITION_Y (LV_ech_STABAR_SIM_1_Y0)


//状态栏SIM卡信息位置2
#define LV_ech_STABAR_SIM_2_HOR_RES    (LV_ech_SCREEN_SCALE_HOR_RES/12)
#define LV_ech_STABAR_SIM_2_VER_RES    (LV_ech_STATUS_BAR_VER_RES)
#define LV_ech_STABAR_SIM_2_OFFSET_X   (-1)
#define LV_ech_STABAR_SIM_2_OFFSET_Y   (1)
#define LV_ech_STABAR_SIM_2_X0          (LV_ech_SCREEN_X + LV_ech_STABAR_SIM_2_OFFSET_X + LV_ech_SCREEN_SCALE_HOR_RES - LV_ech_STABAR_BATTERY_HOR_RES - LV_ech_STABAR_SIM_1_HOR_RES - LV_ech_STABAR_SIM_2_HOR_RES - 1)
#define LV_ech_STABAR_SIM_2_Y0          (LV_ech_SCREEN_Y + LV_ech_STABAR_SIM_2_OFFSET_Y)
#define LV_ech_STABAR_SIM_2_X1          (LV_ech_SCREEN_X + LV_ech_STABAR_SIM_2_OFFSET_X + LV_ech_SCREEN_SCALE_HOR_RES - LV_ech_STABAR_BATTERY_HOR_RES - LV_ech_STABAR_SIM_1_HOR_RES - 1)
#define LV_ech_STABAR_SIM_2_Y1          (LV_ech_SCREEN_Y + LV_ech_STABAR_SIM_2_OFFSET_Y + LV_ech_STABAR_SIM_2_VER_RES - 1)
#define LV_ech_STABAR_SIM_2_POSITION_X (LV_ech_STABAR_SIM_2_X0)
#define LV_ech_STABAR_SIM_2_POSITION_Y (LV_ech_STABAR_SIM_2_Y0)


#define LV_ech_STABAR_TIME_FORMATE_DEFAULT  (lv_ech_time_format_hhmm)
#define LV_ech_STABAR_TIME_LEN_DEFAULT       (12)
#define LV_ech_STABAR_TIME_DEAULT_HHMM              "00:00"
#define LV_ech_STABAR_TIME_DEAULT_MMHH              "00:00"
#define LV_ech_STABAR_TIME_DEAULT_HHMMSS            "00:00:00"
#define LV_ech_STABAR_TIME_DEAULT_SSHHMM            "00:00:00"
#define LV_ech_STABAR_TIME_DEAULT_SSMMHH            "00:00:00"
#define LV_ech_STABAR_TIME_DEAULT_MMHHSS            "00:00:00"


#define LV_ech_CONTROL_LBTN_HOR_RES        (LV_ech_CONTROL_HOR_RES/12)
#define LV_ech_CONTROL_LBTN_VER_RES        (LV_ech_CONTROL_VER_RES)
#define LV_ech_CONTROL_LBTN_OFFSET_X       (0)
#define LV_ech_CONTROL_LBTN_OFFSET_Y       (0)
#define LV_ech_CONTROL_LBTN_X0              (LV_ech_SCREEN_X + LV_ech_CONTROL_LBTN_OFFSET_X)
#define LV_ech_CONTROL_LBTN_Y0              (LV_ech_SCREEN_Y + LV_ech_CONTROL_LBTN_OFFSET_Y)
#define LV_ech_CONTROL_LBTN_X1              (LV_ech_CONTROL_LBTN_X0 + LV_ech_CONTROL_LBTN_HOR_RES - 1)
#define LV_ech_CONTROL_LBTN_Y1              (LV_ech_CONTROL_LBTN_Y0 + LV_ech_CONTROL_LBTN_VER_RES - 1)
#define LV_ech_CONTROL_LBTN_POSITION_X     (LV_ech_CONTROL_LBTN_X0)
#define LV_ech_CONTROL_LBTN_POSITION_Y     (LV_ech_CONTROL_LBTN_Y0)


#define LV_ech_CONTROL_MBTN_HOR_RES        (LV_ech_CONTROL_HOR_RES/12)
#define LV_ech_CONTROL_MBTN_VER_RES        (LV_ech_CONTROL_VER_RES)
#define LV_ech_CONTROL_MBTN_OFFSET_X       (0)
#define LV_ech_CONTROL_MBTN_OFFSET_Y       (0)
#define LV_ech_CONTROL_MBTN_X0              (LV_ech_SCREEN_X + LV_ech_CONTROL_MBTN_OFFSET_X + LV_ech_CONTROL_HOR_RES/4 - LV_ech_CONTROL_MBTN_HOR_RES/4 - LV_ech_CONTROL_MBTN_HOR_RES/6)
#define LV_ech_CONTROL_MBTN_Y0              (LV_ech_SCREEN_X + LV_ech_CONTROL_MBTN_OFFSET_Y)
#define LV_ech_CONTROL_MBTN_X1              (LV_ech_CONTROL_MBTN_X0 + LV_ech_CONTROL_MBTN_HOR_RES - 1)
#define LV_ech_CONTROL_MBTN_Y1              (LV_ech_CONTROL_MBTN_Y0 + LV_ech_CONTROL_MBTN_VER_RES - 1)
#define LV_ech_CONTROL_MBTN_POSITION_X     (LV_ech_CONTROL_MBTN_X0)
#define LV_ech_CONTROL_MBTN_POSITION_Y     (LV_ech_CONTROL_MBTN_Y0)


#define LV_ech_CONTROL_RBTN_HOR_RES        (LV_ech_CONTROL_HOR_RES/12)
#define LV_ech_CONTROL_RBTN_VER_RES        (LV_ech_CONTROL_VER_RES)
#define LV_ech_CONTROL_RBTN_OFFSET_X       (0)
#define LV_ech_CONTROL_RBTN_OFFSET_Y       (0)
#define LV_ech_CONTROL_RBTN_X0              (LV_ech_SCREEN_X + LV_ech_CONTROL_RBTN_OFFSET_X + LV_ech_CONTROL_HOR_RES - LV_ech_CONTROL_RBTN_HOR_RES)
#define LV_ech_CONTROL_RBTN_Y0              (LV_ech_SCREEN_X + LV_ech_CONTROL_RBTN_OFFSET_Y)
#define LV_ech_CONTROL_RBTN_X1              (LV_ech_CONTROL_RBTN_X0 + LV_ech_CONTROL_RBTN_HOR_RES - 1)
#define LV_ech_CONTROL_RBTN_Y1              (LV_ech_CONTROL_RBTN_Y0 + LV_ech_CONTROL_RBTN_VER_RES - 1)
#define LV_ech_CONTROL_RBTN_POSITION_X     (LV_ech_CONTROL_RBTN_X0)
#define LV_ech_CONTROL_RBTN_POSITION_Y     (LV_ech_CONTROL_RBTN_Y0)

/*************************************************
*
*                  TYPEDEF
*
*************************************************/
typedef char *             lv_ech_text;
typedef lv_obj_t           lv_ech_status_bar_t;
typedef lv_obj_t           lv_ech_display_t;
typedef lv_obj_t           lv_ech_control_button_t;

/*******************
*     NAME:    _lv_ech_control_t
*   AUTHOR:    wangls
* DESCRIPT:    control filed of the inter phone
*     DATE:    2020-8-16
********************/
typedef struct _lv_ech_control_t{
	lv_ech_control_button_t  *  left_button;
	lv_ech_control_button_t  *  middle_button;
	lv_ech_control_button_t  *  right_button;
	lv_obj_t                 *  background;
} lv_ech_control_t;

/*******************
*     NAME:   _lv_ech_activity_t
*   AUTHOR:   wangls
* DESCRIPT:   inter phone activity
*     DATE:   2020-8-16
********************/
typedef struct _lv_ech_activity_t{
	bool                               has_stabar;   //只标注是否显示状态栏，不代表状态栏的存在性
	bool                               has_control;     //标注该窗口是否有控制栏
	lv_obj_t                        *  base;            //activity基础，不要调用，只在创建和删除用到
	lv_ech_status_bar_t      *  status_bar;     //即使该窗口没有状态栏，该成员也会指向状态栏，因为状态栏唯一
	lv_ech_control_t         *  control;        //指向控制栏
	lv_ech_display_t         *  display;        //指向显示区域
    lv_signal_cb_t                   signal_func;    //activity的signal函数
    lv_design_cb_t                   design_func;    //activity的design函数
    lv_event_cb_t                     event_func;    //activity的event函数
    lv_ech_activity_ext_t            activity_ext;    //activity的创建和销毁
    void                            *  ext_data;       //activity的数据指针，具体数据类型由activity->base->ext_attr->create()的返回值决定，可以根据自己的需要，在创建activity后，将数据放置在此
} lv_ech_activity_t;

/*************************************************
*
*                  EXTERN
*
*************************************************/
extern lv_group_t *interphone_indev_group;
extern lv_ech_activity_t * current_activity;
extern lv_ech_status_bar_t      *lv_ech_status_bar;
extern nv_ech_setting_msg_t    * ech_setting_conf;

extern lv_style_t theme_white_style_base;
extern lv_style_t theme_white_style_list_scroll;
extern lv_style_t theme_white_style_list_page;
extern lv_style_t theme_white_style_list_btn_rel;
extern lv_style_t theme_white_style_list_btn_pr;
extern lv_style_t theme_white_style_list_btn_ina;
extern lv_style_t theme_white_style_win_header;
extern lv_style_t theme_white_style_idle_big_clock;
extern lv_style_t theme_white_style_idle_date_label;
extern lv_style_t theme_white_style_idle_msg_label;
extern lv_style_t theme_white_style_switch_bg;
extern lv_style_t theme_white_style_switch_indic;
extern lv_style_t theme_white_style_switch_knob_off;
extern lv_style_t theme_white_style_switch_knob_on;
extern lv_style_t theme_white_style_rb;
extern lv_style_t theme_white_style_cb;
extern lv_style_t theme_white_style_about_label;
extern lv_style_t theme_white_style_status_bar;
extern lv_style_t theme_white_style_status_bar_time;
extern lv_style_t theme_white_style_control;

extern lv_style_t theme_black_style_base;
extern lv_style_t theme_black_style_list_scroll;
extern lv_style_t theme_black_style_list_page;
extern lv_style_t theme_black_style_list_btn_rel;
extern lv_style_t theme_black_style_list_btn_pr;
extern lv_style_t theme_black_style_list_btn_ina;
extern lv_style_t theme_black_style_win_header;
extern lv_style_t theme_black_style_idle_big_clock;
extern lv_style_t theme_black_style_idle_date_label;
extern lv_style_t theme_black_style_idle_msg_label;
extern lv_style_t theme_black_style_switch_bg;
extern lv_style_t theme_black_style_switch_indic;
extern lv_style_t theme_black_style_switch_knob_off;
extern lv_style_t theme_black_style_switch_knob_on;
extern lv_style_t theme_black_style_rb;
extern lv_style_t theme_black_style_cb;
extern lv_style_t theme_black_style_about_label;
extern lv_style_t theme_black_style_status_bar;
extern lv_style_t theme_black_style_status_bar_time;
extern lv_style_t theme_black_style_control;

/*nv*/
extern nv_ech_setting_msg_t * ech_setting_conf;

/*******************
*     NAME:   _lv_ech_activity_list_node_t
*   AUTHOR:   wangls
* DESCRIPT:   存储创建的activity活动，以及查找display所属的activity
*     DATE:   2020-08-16
********************/
typedef struct _lv_ech_activity_list_node_t{
	lv_ech_activity_t * activity;
	struct _lv_ech_activity_list_node_t * next;
} lv_ech_activity_list_node_t;

typedef struct _lv_ech_activity_list_t{
	unsigned int size;
	struct _lv_ech_activity_list_node_t * head;
} lv_ech_activity_list_t;

typedef struct _lv_ech_control_text_t{
	lv_ech_text left_text;
	lv_ech_text middle_text;
	lv_ech_text right_text;
} lv_ech_control_text_t;

/*************************************************
*
*                  ENUM
*
*************************************************/
typedef enum {
	lv_ech_time_format_hhmm = 0,
	lv_ech_time_format_mmhh,
	lv_ech_time_format_hhmmss,
	lv_ech_time_format_sshhmm,
	lv_ech_time_format_ssmmhh,
	lv_ech_time_format_mmhhss,
	lv_ech_time_format_invalid_time_format
} lv_ech_time_format_t;

/*******************
*     NAME:   lv_ech_status_bar_sim_obj_t
*   AUTHOR:   wangls
* DESCRIPT:   status bar of the inter phone
*     DATE:   2020-8-16
********************/
typedef struct _lv_ech_status_bar_sim_obj_t
{
	lv_obj_t ** align_l_obj, ** align_r_obj;                 //对其对象，用于排列sim卡图??	lv_obj_t * sim_img;                   //在处错误时或者没有SIM卡时显示用的图标
	lv_obj_t * sim_up_down_img;           //上传下载时的图标
	lv_obj_t * sim_signal_strength_img;   //信号强度图标
	lv_obj_t * sim_net_type_img;          //网络信号类型图标
} lv_ech_status_bar_sim_obj_t;

/*******************
*     NAME:   lv_ech_status_bar_fptr_t
*   AUTHOR:   wangls
* DESCRIPT:   status bar of the inter phone
*     DATE:   2020-8-16
********************/
typedef struct _lv_ech_status_bar_fptr_t{
	bool                        has_sim1;
	bool                        has_sim2;
	bool                        has_battery;
	lv_ech_time_format_t time_formate;
	#if 1
	lv_ech_status_bar_sim_obj_t  *sim1;
	lv_ech_status_bar_sim_obj_t  *sim2;
	#else
	lv_obj_t                    *sim1;
	lv_obj_t                    *sim2;
	#endif
	lv_obj_t                    *battery_img;
	lv_obj_t                    *time_label;
  lv_obj_t                    *signal_type_label;
  lv_obj_t                    *signal_intensity_img;
} lv_ech_status_bar_fptr_t;

/*******************
*     NAME:    lv_ech_setting_init
*   AUTHOR:    wangls
* DESCRIPT:    初始化对讲机设置
*     DATE:    2019-10-24
********************/
bool lv_ech_setting_init(void);

/*******************
*     NAME:  status_bar_task_t
*   AUTHOR:  wangls
* DESCRIPT:  定义状态栏任务中额外执行的任务类型
*     DATE:
********************/
typedef void (*status_bar_task_t)(void);

/*******************
*	    NAME: lv_ech_stabar_task
*	  AUTHOR: wangls
* DESCRIPT: 状态栏任务
*	    DATE: 2020-8-16
********************/
void lv_ech_stabar_task(lv_task_t * task);

/*******************
*     NAME:    lv_ech_activity_list_lookup
*   AUTHOR:    wangls
* DESCRIPT:    从activity查询表中查询display的activity
*     DATE:    2020-08-16
********************/
lv_ech_activity_t *	lv_ech_activity_list_lookup(lv_ech_display_t * display);

/*******************
*     NAME:    lv_ech_create_activity
*   AUTHOR:    wangls
* DESCRIPT:    创建一个有效的activity
*     DATE:    2020-08-02
********************/
lv_ech_activity_t *lv_ech_create_activity(lv_ech_activity_ext_t *activity_ext,
        bool has_stabar,
        bool has_control,
        lv_ech_control_text_t *control_text);

/*******************
*     NAME:    lv_ech_status_bar_task_ext_add
*   AUTHOR:    wangls
* DESCRIPT:    添加状态栏额外任务
*     DATE:    2020-8-16
********************/
bool lv_ech_status_bar_task_ext_add(status_bar_task_t task);
				
/*******************
*     NAME:    lv_ech_get_display_width
*   AUTHOR:    wangls
* DESCRIPT:    获取显示区域??*     DATE:    2020-8-16
********************/
lv_coord_t lv_ech_get_display_width(const lv_ech_display_t * display);			

/*******************
*     NAME:    lv_ech_get_display_height
*   AUTHOR:    wangls
* DESCRIPT:    获取显示区域??*     DATE:    2020-8-16
********************/
lv_coord_t lv_ech_get_display_height(lv_ech_display_t * display);

/*******************
*     NAME:    lv_ech_activity_set_signal_cb
*   AUTHOR:    wangls
* DESCRIPT:    设置activity的signal函数
*     NOTE:    signal函数运行机制:
					lv_xxx_create(parent,copy) ==> 调用parent->signal_func函数
*     DATE:    2020-8-16
********************/
void lv_ech_activity_set_signal_cb(lv_ech_activity_t *activity,
        lv_signal_cb_t func);

/*******************
*     NAME:    lv_ech_activity_set_design_cb
*   AUTHOR:    wangls
* DESCRIPT:    设置activity的signal函数
*     DATE:    2020-8-16
********************/
void lv_ech_activity_set_design_cb(lv_ech_activity_t *activity,
        lv_design_cb_t func);

/*******************
*	  NAME:    lv_ech_get_battery_img
*	AUTHOR:    wangls
* DESCRIPT:    <BB><F1>?<B5><B1>???<B5><E7><B3><D8>?<B1><EA>
*	  DATE:    2020-08-16
********************/
lv_img_dsc_t * lv_ech_get_battery_img(void);

#ifdef __cplusplus
}
#endif


#endif //__INCLUDE_LV_INTER_PHONE_OBJ__

