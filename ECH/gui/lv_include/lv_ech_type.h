#ifndef __LV_TYPR_PORT_H_
#define __LV_TYPR_PORT_H_

#include "lvgl.h"
#include "appstart.h"

typedef unsigned char 		 UINT8;
typedef short int     		 INT16;
typedef unsigned short int   UINT16;
typedef int          		 INT32;
typedef unsigned int  		 UINT32;

typedef unsigned char 		 uint8_t;
typedef short int    		 int16_t;
typedef unsigned short int   uint16_t;

#define IN  const
#define OUT

//#define ech_UI_MACRO     1
//#if ech_UI_MACRO != 0
//#define GROUP_EQUATION(A,B,C,D,E) lv_ech_check_group_equation((A),(B),(C),(D),(E))
//#define MEMBER_EQUATION(A,B,C,D,E) lv_ech_check_member_equation((A),(B),(C),(D),(E))
//#else
//#define GROUP_EQUATION(A,B,C,D,E) (0 == strcmp((A),(B)))
//#define MEMBER_EQUATION(A,B,C,D,E) (0 == strcmp((A),(B)))
//#endif

#define LIST_ELEMENT_NAME_MAX_LENGTH 64

#define LV_ech_NAME_LEN LIST_ELEMENT_NAME_MAX_LENGTH

#define ech_MAX_BRIGHT 9

/*******************
*     NAME:   lv_ech_time_t
*   AUTHOR:   lugj
* DESCRIPT:   获取时间的结构体
*     DATE:   2019-11-01
********************/
typedef struct
{
    INT32 tm_sec;                                                                 // seconds [0,59]
    INT32 tm_min;                                                                 // minutes [0,59]
    INT32 tm_hour;                                                                // hour [0,23]
    INT32 tm_mday;                                                                // day of month [1,31]
    INT32 tm_mon;                                                                 // month of year [1,12]
    INT32 tm_year;                                                                // since 1970
    INT32 tm_wday;                                                                // sunday = 0
} lv_ech_time_t;



typedef struct
{
	uint8_t big_font_switch;                      
	uint8_t list_page_colum_count;                 
	uint32_t list_btn_current_font;                
	uint32_t list_btn_big_font;                    
	uint32_t list_btn_small_font;                  
	uint32_t about_label_current_font;           
	uint32_t about_label_big_font;                
	uint32_t about_label_small_font;               
	uint32_t win_title_font;
	uint32_t activity_control_font;
	uint32_t status_bar_time_font;
	uint32_t idle_big_clock_font;
	uint32_t idle_date_label_font;
	uint32_t idle_page2_msg_font;
	uint32_t idle_popwindows_msg_font;
	uint32_t idle_lockgroupwindows_msg_font;
	uint32_t idle_shutdownwindows_msg_font;
} nv_ech_font_size_msg_t;


typedef struct
{
	uint32_t style_base;
	uint32_t style_list_scroll;
	uint32_t style_list_page;
	uint32_t style_list_btn_rel;
	uint32_t style_list_btn_pr;
	uint32_t style_list_btn_ina;
	uint32_t style_win_header;
	uint32_t style_idle_big_clock;
	uint32_t style_idle_date_label;
	uint32_t style_idle_msg_label;
	uint32_t style_switch_bg;
	uint32_t style_switch_indic;
	uint32_t style_switch_knob_off;
	uint32_t style_switch_knob_on;
	uint32_t style_rb;
	uint32_t style_cb;
	uint32_t style_about_label;
	uint32_t style_status_bar;
	uint32_t style_status_bar_time;
	uint32_t style_control;
} nv_ech_theme_msg_node_t;

typedef struct
{
	uint8_t  type;                      //[0] white theme   [1]black theme    [default 0]
	nv_ech_theme_msg_node_t * current_theme;
#ifdef CONFIG_ech_GUI_CHOICE_THEME_SUPPORT
	nv_ech_theme_msg_node_t * black;
#endif
	nv_ech_theme_msg_node_t * white;
} nv_ech_theme_msg_t;

typedef struct
{
	uint8_t read_and_write_check;
	uint8_t btn_voice_switch;         //[0]close   [1]open   [default 0]
#ifdef CONFIG_ech_TTS_SUPPORT
	uint8_t voice_broadcast_switch;   //[0]close   [1]open   [default 0]
#endif
#ifdef CONFIG_ech_GUI_KEYPAD_LIGHT_SUPPORT
	uint8_t keypad_led_switch;        //[0]close   [1]open   [default 0]
#endif
	uint8_t GPS_switch;               //[0]close   [1]open   [default 0]
	uint8_t electric_torch_switch;    //[0]close   [1]open   [default 0]
	uint8_t screen_brightness;        //[0 - 9]    [default 4]
	uint8_t screen_bright_time;       //[0]5�?[1]15�?[2]30�?[3]1分钟 [4]2分钟 [5]5分钟 [6]10分钟 [7]30分钟     [default 2]
	//uint8_t current_theme;          //[0] white theme   [1]black theme    [default 0]
	uint8_t main_SIM;                 //[0]SIM 1   [1]SIM 2     [default 0]
#ifdef CONFIG_ech_GUI_CHOICE_NET_TYPE_SUPPORT
	uint8_t net_type;                 //[0]4G/3G/2G  [1]only 3G/2G    [default 0]
#endif
	uint8_t volume;                   //[0-10]    [default 5]
	uint8_t language;                 //[0]简体中�?      [default 0]
	nv_ech_font_size_msg_t font;
	nv_ech_theme_msg_t theme;
#ifdef CONFIG_AT_MY_ACCOUNT_SUPPORT
	char account_name[32];
	char account_passwd[32];
	char ip_address[20];
	int  ip_port;
#endif
} nv_ech_setting_msg_t;

typedef enum
{
    ech_SIM_1 = 0,
    ech_SIM_2
} ech_SIM_ID;

typedef enum
{
    ech_CHG_CONNECTED,                                                          // charger connected
    ech_CHG_DISCONNECTED                                                        // charger disconnected
} ech_CHG_STATUS;

typedef struct{
    UINT32 battery_status;   // 0 - no battery; 1 - has battery
    UINT32 battery_val_mV;   // voltage
    UINT32 charge_cur_mA;    // current
    INT32 battery_temp;     // temperature
    int8_t battery_value;     // surplus electric quantity
    ech_CHG_STATUS charging;         // is charging
} battery_values_t;

typedef enum
{
    MMI_MODEM_SIGNAL_BAR_0,
    MMI_MODEM_SIGNAL_BAR_1,
    MMI_MODEM_SIGNAL_BAR_2,
    MMI_MODEM_SIGNAL_BAR_3,
    MMI_MODEM_SIGNAL_BAR_4,
    MMI_MODEM_SIGNAL_BAR_5
} ech_MMI_MODEM_SIGNAL_BAR;

typedef enum
{
    MMI_MODEM_PLMN_RAT_GSM = 0,                                                 // GSM network
    MMI_MODEM_PLMN_RAT_UMTS,                                                    // UTRAN network
    MMI_MODEM_PLMN_RAT_LTE,                                                     // LTE network
    MMI_MODEM_PLMN_RAT_UNKNOW
} ech_MMI_MODEM_PLMN_RAT;

typedef enum
{
	ech_MMI_VOICE_MSG,
	ech_MMI_VOICE_NOTE,
	ech_MMI_VOICE_KEY,
	ech_MMI_VOICE_PLAY,
	ech_MMI_VOICE_CALL,
} ech_MMI_VOICE_TYPE_E;

typedef enum
{
	LV_GROUP_KEY_UP             = LV_KEY_UP,  /*0x11*/
	LV_GROUP_KEY_DOWN           = LV_KEY_DOWN,  /*0x12*/
	LV_GROUP_KEY_RIGHT          = LV_KEY_RIGHT,  /*0x13*/
	LV_GROUP_KEY_LEFT           = LV_KEY_LEFT,  /*0x14*/
	LV_GROUP_KEY_ESC            = LV_KEY_ESC,  /*0x1B*/
	LV_GROUP_KEY_DEL            = LV_KEY_DEL, /*0x7F*/
	LV_GROUP_KEY_BACKSPACE      = LV_KEY_BACKSPACE,   /*0x08*/
	LV_GROUP_KEY_ENTER          = LV_KEY_ENTER,  /*0x0A, '\n'*/
	LV_GROUP_KEY_NEXT           = LV_KEY_NEXT,   /*0x09, '\t'*/
	LV_GROUP_KEY_PREV           = LV_KEY_PREV,  /*0x0B, '*/
	LV_GROUP_KEY_HOME           = LV_KEY_HOME,   /*0x02, STX*/
	LV_GROUP_KEY_END            = LV_KEY_END,   /*0x03, ETX*/
	LV_GROUP_KEY_GP             = 43,
	LV_GROUP_KEY_MB             = 44,
	LV_GROUP_KEY_VOL_DOWN       = 45,
	LV_GROUP_KEY_VOL_UP         = 46,
	LV_GROUP_KEY_ech            = 47,
	LV_GROUP_KEY_SET            = 48
} LV_GROUP_KEY_E;

typedef enum {
    LIST_TYPE_MEMBER,
    LIST_TYPE_GROUP,
    LIST_TYPE_GROUP_BUILD,
    LIST_TYPE_CALL,
    LIST_TYPE_NUM
} lv_ech_list_type_t;

typedef enum {
    ech_OPERATE_FAILD,
    ech_OPERATE_SECCESS,

    ech_MEMBER_ONLINE,
    ech_MEMBER_OFFLINE,
    ech_MEMBER_EXISTS,
    ech_MEMBER_NONENTITY,

    ech_GROUP_EXISTS,
    ech_GROUP_NONENTITY,
    ech_GROUP_EMPTY,
    ech_GROUP_NON_NULL,

    ech_UNKNOWN_FAULT
} lv_ech_status_t;

typedef enum
{
	LV_ech_NOTATION_NONE       = 0,
	LV_ech_NOTATION_HIDEN      = 1,
	LV_ech_NOTATION_DESTORY    = 2,
	LV_ech_NOTATION_REFRESH    = 3,
	LV_ech_NOTATION_LISTENING  = 4,
	LV_ech_NOTATION_SPEAKING   = 5,
	LV_ech_NOTATION_NORMAL_MSG = 6,
} lv_ech_notation_msg_type_t;

typedef enum {
	lv_ech_idle_page2_none_msg = 0,
	lv_ech_idle_page2_normal_info,
	lv_ech_idle_page2_warnning_info,
	lv_ech_idle_page2_login_info,
	lv_ech_idle_page2_audio,
	lv_ech_idle_page2_join_group,
	lv_ech_idle_page2_list_update,
	lv_ech_idle_page2_speak,
	lv_ech_idle_page2_tone,
	lv_ech_idle_page2_tts,
	lv_ech_idle_page2_listen
} lv_ech_idle_page2_display_t;

typedef enum{//指示灯状�?
	LVechLEDIDTCOM_SIGNAL_STATUS_START = 0,

	LVechLEDIDTCOM_SIGNAL_NORMAL_STATUS ,//正常状�?	LVechLEDIDTCOM_SIGNAL_CHARGING_STATUS ,//充电状�?	LVechLEDIDTCOM_SIGNAL_LOW_BATTERY_STATUS	,//低电�?	LVechLEDIDTCOM_SIGNAL_MERMEBER_LIST_SUCCESS_STATUS	,//获取成员列表成功
	LVechLEDIDTCOM_SIGNAL_MERMEBER_LIST_FAIL_STATUS	,//获取成员列表失败
	LVechLEDIDTCOM_SIGNAL_GROUP_LIST_SUCCESS_STATUS	,//获取群组列表成功
	LVechLEDIDTCOM_SIGNAL_GROUP_LIST_FAIL_STATUS	,//获取群组列表失败
	LVechLEDIDTCOM_SIGNAL_START_TALK_STATUS	,//对讲状�?	LVechLEDIDTCOM_SIGNAL_CONNECT_NETWORK_STATUS	,//注册上网络状�?	LVechLEDIDTCOM_SIGNAL_FAIL_STATUS	,//错误消息
}LVechIDTCOM_Led_SignalType_t;

typedef enum{//呼吸灯周�?
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_0 = 0,

	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_50 = 50,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_100 = 100 ,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_300 = 300	,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_500 = 500	,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_800 = 800	,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_1200 = 1200	,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_1500 = 1500	,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_2000 = 2000	,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_3000 = 3000	,
	LVechLEDIDTCOM_BREATH_LAMP_PERIOD_5000 = 5000	,
}LVechIDTCOM_Led_Period_t;

typedef enum{//刷新机制周期

	LVechLISTIDTCOM_LIST_PERIOD_0 = 0,
	LVechLISTIDTCOM_LIST_PERIOD_10 = 10,
	LVechLISTIDTCOM_LIST_PERIOD_50 = 50 ,
	LVechLISTIDTCOM_LIST_PERIOD_100 = 100 ,
	LVechLISTIDTCOM_LIST_PERIOD_300 = 300	,
	LVechLISTIDTCOM_LIST_PERIOD_500 = 500	,
	LVechLISTIDTCOM_LIST_PERIOD_800 = 800	,
	LVechLISTIDTCOM_LIST_PERIOD_1200 = 1200	,
	LVechLISTIDTCOM_LIST_PERIOD_1500 = 1500	,
	LVechLISTIDTCOM_LIST_PERIOD_2000 = 2000	,
}LVechIDTCOM_List_Period_t;


typedef enum{
	LVechUPDATE_TYPE_START = 0 ,
	LVechUPDATE_TYPE_MEMBERLIST ,
	LVechUPDATE_TYPE_GROUPLIST ,
	LVechUPDATE_TYPE_BUILD_GROUPLIST ,
	LVechUPDATE_TYPE_END ,
}ech_update_type;

typedef enum{
	LVechAUDIO_Type_Start_Index,
	LVechAUDIO_Type_Start_Machine,      // 欢迎使用数字公网对讲�?	LVechAUDIO_Type_Fail_Update_Group,      //群组信息更新失败
	LVechAUDIO_Type_Fail_Update_Member,      //成员列表更新失败
	LVechAUDIO_Type_Insert_SIM_Card,      //请插入SIM�?	LVechAUDIO_Type_Join_Group,      //加入群组
	LVechAUDIO_Type_Low_Battery,      //电量低请充电
	LVechAUDIO_Type_No_Login,      //当前未登�?	LVechAUDIO_Type_Offline_Member,      //成员不在�?	LVechAUDIO_Type_Success_Member_Call,      //单呼成功
	LVechAUDIO_Type_Success_Build_Group,      //建组成功
	LVechAUDIO_Type_Success_Login,      //登录成功
	LVechAUDIO_Type_No_Connected,      //当前网络未连�?	LVechAUDIO_Type_Tone_Cannot_Speak,   //
	LVechAUDIO_Type_Tone_Lost_Mic,   //
	LVechAUDIO_Type_Tone_Note,   //
	LVechAUDIO_Type_Tone_Start_Listen,   //
	LVechAUDIO_Type_Tone_Start_Speak,   //
	LVechAUDIO_Type_Tone_Stop_Listen,   //
	LVechAUDIO_Type_Tone_Stop_Speak,   //
	LVechAUDIO_Type_End_Index,
} LVechAUDIO_Type_e;

typedef struct _list_element_t{
    char name[LIST_ELEMENT_NAME_MAX_LENGTH];
    lv_obj_t * list_item;
    void * information;
    struct _list_element_t * next;
} list_element_t;

typedef struct {
    unsigned int group_number;
    list_element_t * group_list;
} lv_ech_group_list_t;

typedef void * lv_ech_group_info_t;

typedef void * lv_ech_member_info_t;

typedef struct {
	  bool hide_offline;
    unsigned int online_number;
    unsigned int offline_number;
    list_element_t * online_list;
    list_element_t * offline_list;
} lv_ech_member_list_t;

typedef struct _lv_ech_audio_dsc_t
{
	uint32_t data_size;
  uint8_t * data;
} lv_ech_audio_dsc_t;

#endif 

