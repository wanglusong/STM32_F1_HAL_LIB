#ifdef __cplusplus
extern "C" {
#endif

#include "lv_ech.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdarg.h>
#ifdef UART_FUNC
#include "ech_uartall.h"
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif

/*************************************************
*
*                  GLOBAL
*
*************************************************/
lv_ech_status_bar_t      *lv_ech_status_bar = NULL;
lv_ech_status_bar_fptr_t  *lv_ech_status_bar_fptr = NULL;
lv_group_t                      *ech_indev_group;
lv_indev_t               *ech_keypad_dev = NULL;
lv_ech_activity_t       * current_activity;
nv_ech_setting_msg_t    * ech_setting_conf = NULL;
/*************************************************
*
*                  LOCAL
*
*************************************************/	
static char lv_ech_time[LV_ech_STABAR_TIME_LEN_DEFAULT]   =   {0};
static lv_ech_activity_list_t *lv_ech_activity_list;
static lv_signal_cb_t ancient_signal_func = NULL;
static lv_design_cb_t ancient_design_func = NULL;
static lv_event_cb_t  ancient_event_func  = NULL;
static status_bar_task_t status_bar_task_ext[LV_ech_STABAR_TASK_EXT_LENGTH];
static lv_ech_activity_t * _idle_activity;
static char lv_ech_refresh_ui_state = 0;
#define LV_ech_STACK_SIZE   100
static struct _lv_ech_stack_t
{
    int size;
    void *activity[LV_ech_STACK_SIZE];
} lv_ech_statck;

/*电池图标*/
const lv_img_dsc_t *battery_img_dispaly[9] = { &stat_sys_battery_charge_anim0
												,&stat_sys_battery_charge_anim15
												,&stat_sys_battery_charge_anim28
												,&stat_sys_battery_charge_anim43
												,&stat_sys_battery_charge_anim57
												,&stat_sys_battery_charge_anim71
												,&stat_sys_battery_charge_anim85
												,&stat_sys_battery_charge_anim100};


/***********************************************
*
*				   theme
*
************************************************/
lv_style_t theme_white_style_base = {0};
lv_style_t theme_white_style_list_scroll = {0};
lv_style_t theme_white_style_list_page = {0};
lv_style_t theme_white_style_list_btn_rel = {0};
lv_style_t theme_white_style_list_btn_pr = {0};
lv_style_t theme_white_style_list_btn_ina = {0};
lv_style_t theme_white_style_win_header = {0};
lv_style_t theme_white_style_idle_big_clock = {0};
lv_style_t theme_white_style_idle_date_label = {0};
lv_style_t theme_white_style_idle_msg_label = {0};
lv_style_t theme_white_style_switch_bg = {0};
lv_style_t theme_white_style_switch_indic = {0};
lv_style_t theme_white_style_switch_knob_off = {0};
lv_style_t theme_white_style_switch_knob_on = {0};
lv_style_t theme_white_style_rb = {0};
lv_style_t theme_white_style_cb = {0};
lv_style_t theme_white_style_about_label = {0};
lv_style_t theme_white_style_status_bar = {0};
lv_style_t theme_white_style_status_bar_time = {0};
lv_style_t theme_white_style_control = {0};

#ifdef CONFIG_ech_GUI_CHOICE_THEME_SUPPORT
lv_style_t theme_black_style_base = {0};
lv_style_t theme_black_style_list_scroll = {0};
lv_style_t theme_black_style_list_page = {0};
lv_style_t theme_black_style_list_btn_rel = {0};
lv_style_t theme_black_style_list_btn_pr = {0};
lv_style_t theme_black_style_list_btn_ina = {0};
lv_style_t theme_black_style_win_header = {0};
lv_style_t theme_black_style_idle_big_clock = {0};
lv_style_t theme_black_style_idle_date_label = {0};
lv_style_t theme_black_style_idle_msg_label = {0};
lv_style_t theme_black_style_switch_bg = {0};
lv_style_t theme_black_style_switch_indic = {0};
lv_style_t theme_black_style_switch_knob_off = {0};
lv_style_t theme_black_style_switch_knob_on = {0};
lv_style_t theme_black_style_rb = {0};
lv_style_t theme_black_style_cb = {0};
lv_style_t theme_black_style_about_label = {0};
lv_style_t theme_black_style_status_bar = {0};
lv_style_t theme_black_style_status_bar_time = {0};
lv_style_t theme_black_style_control = {0};
#endif

static bool lv_ech_init_stabar_time_label(void);
static void lv_ech_stabar_battery_task(void);
static bool lv_ech_init_stabar_battery_img(void);

/*******************
*     NAME:    lv_ech_control_init
*   AUTHOR:    lugj
* DESCRIPT:    初始化控制区域
*     DATE:    2019-10-25
********************/
static void lv_ech_control_init(lv_ech_activity_t *activity,
                                       const char *left_text,
                                       const char *middle_text,
                                       const char *right_text)
{
    lv_ech_control_t *control;
    lv_style_t * ctrl_background_style;

    ctrl_background_style = (lv_style_t *)ech_setting_conf->theme.current_theme->style_control;/*主题*/

    control = (lv_ech_control_t *)lv_mem_alloc(sizeof(lv_ech_control_t));

    control->background = lv_obj_create(activity->display, NULL);

    if(activity->has_stabar)
    {
        lv_obj_set_size(control->background, LV_ech_CONTROL_HOR_RES, LV_ech_CONTROL_VER_RES);

        lv_obj_set_pos(control->background, LV_ech_CONTROL_POSITION_X, LV_ech_CONTROL_POSITION_Y);
    }
    else
    {
        lv_obj_set_size(control->background, LV_ech_CONTROL_HOR_RES, LV_ech_CONTROL_VER_RES);

        lv_obj_set_pos(control->background, LV_ech_CONTROL_NOSTABAR_POSITION_X, LV_ech_CONTROL_NOSTABAR_POSITION_Y);
    }
    lv_obj_add_style(control->background, LV_OBJ_PART_MAIN, ctrl_background_style);

    activity->control = control;

    control->left_button = lv_label_create(control->background,NULL);
    lv_label_set_text(control->left_button,left_text);
    lv_label_set_align(control->left_button, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(control->left_button, lv_obj_get_parent(control->left_button), LV_ALIGN_IN_LEFT_MID, 0, 0);

    control->middle_button = lv_label_create(control->background,NULL);
    lv_label_set_text(control->middle_button, middle_text);
    lv_label_set_align(control->middle_button, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(control->middle_button, lv_obj_get_parent(control->middle_button), LV_ALIGN_CENTER, 0, 0);

    control->right_button = lv_label_create(control->background,NULL);
    lv_label_set_text(control->right_button, right_text);
    lv_label_set_align(control->right_button, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(control->right_button, lv_obj_get_parent(control->right_button), LV_ALIGN_IN_RIGHT_MID, 0, 0);

}

/*******************
*     NAME:    lv_ech_activity_list_init
*   AUTHOR:    wangls
* DESCRIPT:    初始化activity查询表
*     DATE:    2020-08-16
********************/
static void	lv_ech_activity_list_init(void)
{
    lv_ech_activity_list = (lv_ech_activity_list_t *)lv_mem_alloc(sizeof(lv_ech_activity_list_t));
    lv_ech_activity_list->size = 0;
    lv_ech_activity_list->head = (lv_ech_activity_list_node_t *)lv_mem_alloc(sizeof(lv_ech_activity_list_node_t));
    lv_ech_activity_list->head->activity = NULL;
    lv_ech_activity_list->head->next = NULL;
}


/*******************
*     NAME:    lv_ech_activity_list_insert
*   AUTHOR:    wangls
* DESCRIPT:    将new_activity插入activity查询表
*     DATE:    2020-08-16
********************/
static bool	lv_ech_activity_list_insert(lv_ech_activity_t * new_activity)
{
    lv_ech_activity_list_node_t * p = lv_ech_activity_list->head;
    lv_ech_activity_list_node_t * nonius = (lv_ech_activity_list_node_t *)lv_mem_alloc(sizeof(lv_ech_activity_list_node_t));
    if(NULL == nonius)
    {
        return false;
    }
    nonius->activity = new_activity;
    nonius->next = NULL;

    if(lv_ech_activity_list->size == 0)
    {
        p->next = nonius;
    }
    else
    {
        p = p->next;
        while(p->next != NULL)
        {
            if(p->activity == new_activity)
            {
                return true;
            }
            p = p->next;
        }
        p->next = nonius;
    }
    lv_ech_activity_list->size = lv_ech_activity_list->size + 1;
    return true;
}



/*******************
*     NAME:    lv_ech_activity_list_delete
*   AUTHOR:    wangls
* DESCRIPT:    将old_activity从activity查询表中删除
*     DATE:    2020-08-16
********************/
static void	lv_ech_activity_list_delete(lv_ech_activity_t * old_activity)
{
    lv_ech_activity_list_node_t * p = lv_ech_activity_list->head;
    lv_ech_activity_list_node_t * t;

    while(p->next && p->next->activity != old_activity)
    {
        p = p->next;
    }

    if(p->next != NULL)
    {
        t = p->next;
        p->next = t->next;
        lv_mem_free(t);
        lv_ech_activity_list->size = lv_ech_activity_list->size - 1;
    }
}

/*******************
*     NAME:    lv_ech_signal_cb
*   AUTHOR:    wangls
* DESCRIPT:    设备界面signal函数
*     DATE:    2020-08-16
********************/
static lv_res_t lv_ech_signal_cb(lv_obj_t * obj, lv_signal_t sign, void * param)
{
    lv_res_t ret = LV_RES_OK;
   // OSI_LOGI(0, "[ech][signal][lv_ech_signal_cb] obj <- 0x%p \n", obj);
   // OSI_LOGI(0, "[ech][signal][lv_ech_signal_cb] sign <- %d \n", sign);
   // OSI_LOGI(0, "[ech][signal][lv_ech_signal_cb] param <- 0x%p \n", param);

#if 0
    bool is_keypad_msg = lv_ech_is_keypad_msg(sign, param);
    bool lcd_is_wakeup = ech_get_lcd_status();

	if(is_keypad_msg && !lcd_is_wakeup)
	{
		return LV_RES_INV;
	}

    ech_setting_conf = lv_ech_setting_conf_read();
    uint32_t cur_key = 0;

    if(false == is_keypad_msg)
    {
        ret = (*ancient_signal_func)(obj,sign,param);

        if(ret != LV_RES_OK)
        {
	        return ret;
        }
    }

    if(!(sign == LV_SIGNAL_STYLE_CHG
      || sign == LV_SIGNAL_PRESSED
      || sign == LV_SIGNAL_PRESSING
      || sign == LV_SIGNAL_PRESS_LOST
      || sign == LV_SIGNAL_RELEASED
      || sign == LV_SIGNAL_LONG_PRESS
      || sign == LV_SIGNAL_LONG_PRESS_REP
      || sign == LV_SIGNAL_DRAG_BEGIN
      || sign == LV_SIGNAL_DRAG_END
      || sign == LV_SIGNAL_FOCUS
      || sign == LV_SIGNAL_DEFOCUS
      || sign == LV_SIGNAL_CONTROL))
	{
		return ret;
	}
#endif
	
    lv_ech_activity_t * activity = lv_ech_activity_list_lookup(obj);
    if(NULL == activity)
    {
	    return ret;
    }

    if(activity != current_activity)
    {
       // OSI_LOGI(0, "[ech][signal][lv_ech_signal_cb] current activity is empty or is not current_activity\n");
      return ret;
    }
		
#if 0
    uint8_t vol_cur = lv_ech_setting_get_current_volume(ech_MMI_VOICE_MSG);
    if(is_keypad_msg)
    {
		cur_key = *((uint32_t *)param);

		OSI_LOGI(0, "[ech][signal][lv_ech_signal_cb] cur_key <- %d \n", cur_key);
		if(cur_key == LV_GROUP_KEY_VOL_DOWN)
        {
            if(vol_cur > 0)
            {
                vol_cur = vol_cur - 1;
                lv_ech_set_volum(ech_MMI_VOICE_PLAY , vol_cur, ech_setting_conf->btn_voice_switch, true);
            }
        }
        else if(cur_key == LV_GROUP_KEY_VOL_UP)
        {
            if(vol_cur < 11)
            {
                vol_cur = vol_cur + 1;
                lv_ech_set_volum(ech_MMI_VOICE_PLAY , vol_cur, ech_setting_conf->btn_voice_switch, true);
            }
        }
        else if(cur_key != LV_GROUP_KEY_ech)
        {
		    ech_play_btn_voice_one_time(vol_cur,
#ifdef CONFIG_ech_TTS_SUPPORT
			    ech_setting_conf->voice_broadcast_switch ||
#endif
			    !(ech_setting_conf->btn_voice_switch));
        }
    }

#endif
		
    if(NULL != activity->signal_func)
    {
        //OSI_LOGI(0, "[ech][signal][lv_ech_signal_cb] call current signal_cb of activity\n");
        ret = activity->signal_func(obj, sign, param);
    }
    return ret;
}

/*******************
*     NAME:    lv_ech_design_cb
*   AUTHOR:    wangls
* DESCRIPT:    设备界面design函数
*     DATE:    2020-08-16
********************/
static bool lv_ech_design_cb(lv_obj_t * obj, const lv_area_t * mask_p, lv_design_mode_t mode)
{
    bool ret = ancient_design_func(obj,mask_p, mode);
    lv_ech_activity_t * activity = lv_ech_activity_list_lookup(obj);
    if(activity == NULL)
    {
        return ret;
    }
    if(NULL != activity->design_func)
    {
        activity->design_func(obj,mask_p, mode);
    }

    return ret;
}

/*******************
*     NAME:    lv_ech_event_cb
*   AUTHOR:    wangls
* DESCRIPT:    设备界面event函数
*     DATE:    2020-08-16
********************/
static void lv_ech_event_cb(lv_obj_t * obj, lv_event_t event)
{
	if(ancient_event_func == NULL)
	{
		return;
	}
    ancient_event_func(obj, event);
    lv_ech_activity_t * activity = lv_ech_activity_list_lookup(obj);
    if(activity == NULL)
    {
        return;
    }
    if(NULL != activity->event_func)
    {
        activity->event_func(obj, event);
    }
}

/*******************
*     NAME:    lv_ech_stack_init
*   AUTHOR:    wangls
* DESCRIPT:    初始化界面管理栈
*     DATE:    2020-8-16
********************/
static void lv_ech_stack_init(void)
{
    lv_ech_statck.size = 0;
    memset(lv_ech_statck.activity, 0, sizeof(void *) * LV_ech_STACK_SIZE);
}

/*******************
*     NAME:    lv_ech_stack_push
*   AUTHOR:    wangls
* DESCRIPT:    压入界面管理栈
*     DATE:    2020-8-16
********************/
static bool lv_ech_stack_push(lv_ech_activity_t *activity)
{
    if(activity == NULL)
    {
        //OSI_LOGI(0, "Please set corrent parameter -- activity\n");
        return false;
    }
    if(lv_ech_statck.size < 0 || lv_ech_statck.size >= LV_ech_STACK_SIZE)
    {
        //OSI_LOGI(0, "capacity of lv_ech_statck is full and can not add any activity to lv_ech_statck\n");
        return false;
    }
    for(int j = 0; j < lv_ech_statck.size; j++)
    {
        if(lv_ech_statck.activity[j] == (void *)activity)
        {
            //OSI_LOGI(0, "The activity is existed in the lv_ech_statck!\n");
            return true;
        }
    }
    lv_ech_statck.activity[lv_ech_statck.size++] = (void *)activity;
    return true;
}

/*******************
*     NAME:    lv_ech_stack_pop
*   AUTHOR:    wangls
* DESCRIPT:    弹出界面管理栈并删除
*     DATE:    2020-8-16
********************/
static lv_ech_activity_t * lv_ech_stack_pop(void)
{
    if(lv_ech_statck.size <= 0)
    {
        //OSI_LOGI(0, "lv_ech_statck is null! Please add idle activity\n");
        return NULL;
    }
    if(lv_ech_statck.size == 1)
    {
        //OSI_LOGI(0, "lv_ech_statck have one item only, only return idle activity and dont decrease size\n");
        return lv_ech_statck.activity[lv_ech_statck.size - 1];
    }
    lv_ech_statck.size = lv_ech_statck.size - 1;
    return (lv_ech_activity_t *)lv_ech_statck.activity[lv_ech_statck.size];
}

/*******************
*     NAME:    lv_ech_stack_top
*   AUTHOR:    wangls
* DESCRIPT:    查看界面管理栈顶元素
*     DATE:    2020-8-16
********************/
static lv_ech_activity_t * lv_ech_stack_top(void)
{
    if(lv_ech_statck.size <= 0)
    {
        //OSI_LOGI(0, "lv_ech_statck is null! Please add idle activity\n");
        return NULL;
    }
    return (lv_ech_activity_t *)lv_ech_statck.activity[lv_ech_statck.size - 1];
}

/*******************
*     NAME:    lv_ech_status_bar_init
*   AUTHOR:    wangls
* DESCRIPT:    初始化状态栏
*     DATE:    2020-8-16
********************/
static bool lv_ech_status_bar_init(void)
{
    bool ret_val = true;
    lv_style_t * ech_stabar_style;
	
    ech_stabar_style = (lv_style_t *)ech_setting_conf->theme.current_theme->style_status_bar;

    lv_ech_status_bar = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(lv_ech_status_bar, LV_ech_STATUS_BAR_HOR_RES, LV_ech_STATUS_BAR_VER_RES);
    lv_obj_set_pos(lv_ech_status_bar, LV_ech_STATUS_BAR_POSITION_X, LV_ech_STATUS_BAR_POSITION_Y);
    lv_obj_add_style(lv_ech_status_bar, LV_OBJ_PART_MAIN, ech_stabar_style);

    lv_ech_status_bar_fptr = (lv_ech_status_bar_fptr_t *)lv_mem_alloc(sizeof(lv_ech_status_bar_fptr_t));
    memset(lv_ech_status_bar_fptr, 0, sizeof(lv_ech_status_bar_fptr_t));
    lv_ech_status_bar->user_data = lv_ech_status_bar_fptr;

    lv_ech_init_stabar_time_label();
   	lv_ech_init_stabar_battery_img();

    memset(status_bar_task_ext, 0, sizeof(status_bar_task_t) * LV_ech_STABAR_TASK_EXT_LENGTH);

    lv_task_create(lv_ech_stabar_task,1000,LV_TASK_PRIO_LOWEST,NULL);
    lv_ech_status_bar_task_ext_add(lv_ech_stabar_battery_task);
	#if 0
    lv_ech_status_bar_task_ext_add(lv_ech_stabar_signal_task);
	#endif
		UART1_apTrace("FUNC: %s LINE: %d\r\n", __func__, __LINE__);
    return ret_val;

}

/*******************
*     NAME:    lv_ech_setting_init
*   AUTHOR:    wangls
* DESCRIPT:    初始化配置
*     DATE:    2019-10-24
********************/
bool lv_ech_setting_init(void)
{
    lv_ech_setting_conf_init();
    ech_setting_conf = lv_ech_setting_conf_read();
	
    return true;
}

/*******************
*     NAME:    lv_ech_theme_init
*   AUTHOR:    wangls
* DESCRIPT:    初始化主题
*     DATE:    2020-8-16
********************/
static bool lv_ech_theme_init(void)
{
	lv_style_init(&theme_white_style_base);
	lv_style_set_bg_color(&theme_white_style_base, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00,0x00,0x00));
	lv_style_set_bg_grad_color(&theme_white_style_base, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00,0x00,0x00));
	lv_style_set_radius(&theme_white_style_base, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&theme_white_style_base, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&theme_white_style_base, LV_STATE_DEFAULT, LV_OPA_COVER);
	lv_style_set_image_recolor(&theme_white_style_base, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xFF, 0xF5, 0x98));
	lv_style_set_image_recolor_opa(&theme_white_style_base, LV_STATE_DEFAULT, LV_OPA_30);
	lv_style_set_image_opa(&theme_white_style_base, LV_STATE_DEFAULT, LV_OPA_90);

	lv_style_init(&theme_white_style_list_page);
	lv_style_set_bg_color(&theme_white_style_list_page, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&theme_white_style_list_page, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));
	lv_style_set_pad_top(&theme_white_style_list_page, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&theme_white_style_list_page, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&theme_white_style_list_page, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&theme_white_style_list_page, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_inner(&theme_white_style_list_page, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&theme_white_style_list_page, LV_STATE_DEFAULT, 0);

	lv_style_init(&theme_white_style_list_scroll);
	lv_style_set_bg_color(&theme_white_style_list_scroll, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&theme_white_style_list_scroll, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));
	lv_style_set_pad_top(&theme_white_style_list_scroll, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&theme_white_style_list_scroll, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&theme_white_style_list_scroll, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&theme_white_style_list_scroll, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_inner(&theme_white_style_list_scroll, LV_STATE_DEFAULT, 1);
	lv_style_set_border_width(&theme_white_style_list_scroll, LV_STATE_DEFAULT, 0);

	lv_style_t lv_scr_base = {0};
	
	lv_style_init(&lv_scr_base);
	lv_style_set_pad_top(&lv_scr_base, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&lv_scr_base, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&lv_scr_base, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&lv_scr_base, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_inner(&lv_scr_base, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&lv_scr_base, LV_STATE_DEFAULT, 0);

	lv_style_copy(&theme_white_style_list_btn_rel, &theme_white_style_list_scroll);
	lv_style_set_text_color(&theme_white_style_list_btn_rel, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x11, 0x11, 0x11));
	lv_style_set_text_font(&theme_white_style_list_btn_rel, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.list_btn_current_font);
	lv_style_set_pad_left(&theme_white_style_list_btn_rel, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_right(&theme_white_style_list_btn_rel, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_inner(&theme_white_style_list_btn_rel, LV_STATE_DEFAULT, 5);

	lv_style_copy(&theme_white_style_list_btn_pr, &theme_white_style_list_btn_rel);
	lv_style_set_bg_color(&theme_white_style_list_btn_pr, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_style_set_bg_grad_color(&theme_white_style_list_btn_pr, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_style_set_bg_opa(&theme_white_style_list_btn_pr, LV_STATE_DEFAULT, LV_OPA_70);
	lv_style_set_text_font(&theme_white_style_list_btn_pr, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.list_btn_current_font);

	lv_style_copy(&theme_white_style_list_btn_ina, &theme_white_style_list_btn_rel);
	lv_style_set_bg_color(&theme_white_style_list_btn_ina, LV_STATE_DEFAULT, LV_COLOR_GRAY);
	lv_style_set_bg_grad_color(&theme_white_style_list_btn_ina, LV_STATE_DEFAULT, LV_COLOR_GRAY);
	lv_style_set_text_font(&theme_white_style_list_btn_ina, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.list_btn_current_font);

	lv_style_init(&theme_white_style_win_header);
	lv_style_set_bg_color(&theme_white_style_win_header, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xee,0xb7,0x00));
	lv_style_set_bg_grad_color(&theme_white_style_win_header, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xee,0xb7,0x00));
	lv_style_set_bg_opa(&theme_white_style_win_header, LV_STATE_DEFAULT, LV_OPA_COVER);
	lv_style_set_text_color(&theme_white_style_win_header, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xee,0xee,0xee));
	lv_style_set_text_font(&theme_white_style_win_header, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.win_title_font);

	lv_style_copy(&theme_white_style_idle_big_clock, &lv_scr_base);
	lv_style_set_text_color(&theme_white_style_idle_big_clock, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_text_font(&theme_white_style_idle_big_clock, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.idle_big_clock_font);

	lv_style_copy(&theme_white_style_idle_date_label, &lv_scr_base);
	lv_style_set_text_color(&theme_white_style_idle_date_label, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_text_font(&theme_white_style_idle_date_label, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.idle_date_label_font);

	lv_style_init(&theme_white_style_idle_msg_label);
	lv_style_set_text_color(&theme_white_style_idle_msg_label, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_text_font(&theme_white_style_idle_msg_label, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.idle_page2_msg_font);

	lv_style_init(&theme_white_style_switch_bg);
	lv_style_set_bg_color(&theme_white_style_switch_bg, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x3f, 0x38, 0x3f));
	lv_style_set_bg_grad_color(&theme_white_style_switch_bg, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x3f, 0x38, 0x3f));
	lv_style_set_pad_top(&theme_white_style_switch_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_bottom(&theme_white_style_switch_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&theme_white_style_switch_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_right(&theme_white_style_switch_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_border_width(&theme_white_style_switch_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_radius(&theme_white_style_switch_bg, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);

	lv_style_init(&theme_white_style_switch_indic);
	lv_style_set_bg_color(&theme_white_style_switch_indic, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xef, 0xc8, 0x9f));
	lv_style_set_bg_grad_color(&theme_white_style_switch_indic, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xef, 0xc8, 0x9f));
	lv_style_set_pad_top(&theme_white_style_switch_indic, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&theme_white_style_switch_indic, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&theme_white_style_switch_indic, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&theme_white_style_switch_indic, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&theme_white_style_switch_indic, LV_STATE_DEFAULT, 0);
	lv_style_set_radius(&theme_white_style_switch_indic, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
	lv_style_set_pad_inner(&theme_white_style_switch_indic, LV_STATE_DEFAULT, 0);

	lv_style_init(&theme_white_style_switch_knob_off);
	lv_style_set_bg_color(&theme_white_style_switch_knob_off, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x77, 0x77, 0x77));
	lv_style_set_bg_grad_color(&theme_white_style_switch_knob_off, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x77, 0x77, 0x77));
	lv_style_set_border_width(&theme_white_style_switch_knob_off, LV_STATE_DEFAULT, 0);
	lv_style_set_radius(&theme_white_style_switch_knob_off, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
	lv_style_set_shadow_width(&theme_white_style_switch_knob_off, LV_STATE_DEFAULT, 0);

	lv_style_init(&theme_white_style_switch_knob_on);
	lv_style_set_bg_color(&theme_white_style_switch_knob_on, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x77, 0x77, 0x77));
	lv_style_set_bg_grad_color(&theme_white_style_switch_knob_on, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x77, 0x77, 0x77));
	lv_style_set_border_width(&theme_white_style_switch_knob_on, LV_STATE_DEFAULT, 0);
	lv_style_set_radius(&theme_white_style_switch_knob_on, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
	lv_style_set_shadow_width(&theme_white_style_switch_knob_on, LV_STATE_DEFAULT, 0);

	lv_style_init(&theme_white_style_rb);
	lv_style_set_border_width(&theme_white_style_rb, LV_STATE_DEFAULT, 0);
	lv_style_set_radius(&theme_white_style_rb, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
	lv_style_set_shadow_width(&theme_white_style_rb, LV_STATE_DEFAULT, 0);

	lv_style_init(&theme_white_style_cb);
	lv_style_set_border_width(&theme_white_style_cb, LV_STATE_DEFAULT, 0);
	lv_style_set_radius(&theme_white_style_cb, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
	lv_style_set_shadow_width(&theme_white_style_cb, LV_STATE_DEFAULT, 0);

	lv_style_copy(&theme_white_style_about_label, &theme_white_style_list_scroll);
	lv_style_set_text_color(&theme_white_style_about_label, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x11, 0x11, 0x11));
	lv_style_set_text_font(&theme_white_style_about_label, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.about_label_current_font);

	lv_style_copy(&theme_white_style_status_bar, &lv_scr_base);
	lv_style_set_bg_color(&theme_white_style_status_bar, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00,0x00,0x00));
	lv_style_set_bg_grad_color(&theme_white_style_status_bar, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00,0x00,0x00));
	lv_style_set_bg_opa(&theme_white_style_status_bar, LV_STATE_DEFAULT, LV_OPA_90);
	lv_style_set_radius(&theme_white_style_status_bar, LV_STATE_DEFAULT, 0);

	lv_style_init(&theme_white_style_status_bar_time);
	lv_style_set_border_width(&theme_white_style_status_bar_time, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&theme_white_style_status_bar_time, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_text_font(&theme_white_style_status_bar_time, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.status_bar_time_font);

	lv_style_copy(&theme_white_style_control, &lv_scr_base);
	lv_style_set_bg_color(&theme_white_style_control, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00,0x00,0xcd));
	lv_style_set_bg_grad_color(&theme_white_style_control, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00,0x00,0xcd));
	lv_style_set_radius(&theme_white_style_control, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&theme_white_style_control, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_text_font(&theme_white_style_control, LV_STATE_DEFAULT, (lv_font_t *)ech_setting_conf->font.activity_control_font);

#ifdef CONFIG_ech_GUI_CHOICE_THEME_SUPPORT
// 初始化黑色主题
    lv_style_copy(&theme_black_style_base,&lv_style_transp);
    theme_black_style_base.body.main_color = LV_COLOR_MAKE(0xFF,0xFF,0xFF);
    theme_black_style_base.body.grad_color = LV_COLOR_MAKE(0xFF,0xFF,0xFF);
    theme_black_style_base.body.radius = 0;
    theme_black_style_base.body.opa = 255;
    theme_black_style_base.image.color = LV_COLOR_BLUE;
    theme_black_style_base.image.intense = 0x33;

    lv_style_copy(&theme_black_style_list_scroll, &lv_style_scr);
    lv_style_copy(&theme_black_style_list_page, &theme_black_style_list_scroll);

    theme_black_style_list_page.body.main_color = LV_COLOR_MAKE(0x10, 0x10, 0x10);
    theme_black_style_list_page.body.grad_color = LV_COLOR_MAKE(0x10, 0x10, 0x10);
    theme_black_style_list_page.body.padding.top = 0;
    theme_black_style_list_page.body.padding.bottom = 0;
    theme_black_style_list_page.body.padding.left = 0;
    theme_black_style_list_page.body.padding.right = 0;
    theme_black_style_list_page.body.padding.inner = 0;
    theme_black_style_list_page.body.border.width = 0;

    theme_black_style_list_scroll.body.padding.top = 0;
    theme_black_style_list_scroll.body.padding.bottom = 0;
    theme_black_style_list_scroll.body.padding.left = 0;
    theme_black_style_list_scroll.body.padding.right = 0;
    theme_black_style_list_scroll.body.padding.inner = 1;
    theme_black_style_list_scroll.body.border.width = 0;
    theme_black_style_list_scroll.body.main_color = LV_COLOR_MAKE(0x20, 0x20, 0x20);
    theme_black_style_list_scroll.body.grad_color = LV_COLOR_MAKE(0x20, 0x20, 0x20);

    lv_style_copy(&theme_black_style_list_btn_rel, &theme_black_style_list_scroll);
    theme_black_style_list_btn_rel.text.color = LV_COLOR_MAKE(0xee, 0xee, 0xee);
    theme_black_style_list_btn_rel.text.font = (lv_font_t *)ech_setting_conf->font.list_btn_current_font;
    theme_black_style_list_btn_rel.body.padding.inner = 5;
    theme_black_style_list_btn_rel.body.padding.left = 2;
    theme_black_style_list_btn_rel.body.padding.right = 3;
    theme_black_style_list_btn_rel.image.color = LV_COLOR_GRAY;
    theme_black_style_list_btn_rel.image.intense = 230;
    theme_black_style_list_btn_rel.image.opa = 255;
    //theme_black_style_list_btn_rel.body.opa = 0;

    lv_style_copy(&theme_black_style_list_btn_pr, &theme_black_style_list_btn_rel);
    theme_black_style_list_btn_pr.body.main_color = LV_COLOR_MAKE(0xbb,0x00,0x00);
    theme_black_style_list_btn_pr.body.grad_color = LV_COLOR_MAKE(0xbb,0x00,0x00);
    theme_black_style_list_btn_pr.text.font = (lv_font_t *)ech_setting_conf->font.list_btn_current_font;
    theme_black_style_list_btn_pr.image.color = LV_COLOR_GRAY;
    theme_black_style_list_btn_pr.image.intense = 230;
    theme_black_style_list_btn_pr.image.opa = 255;
    theme_black_style_list_btn_pr.body.opa = 0xaa;

    lv_style_copy(&theme_black_style_list_btn_ina, &theme_black_style_list_btn_rel);
    theme_black_style_list_btn_ina.body.main_color = LV_COLOR_MAKE(0x7f,0x7f,0x7f);
    theme_black_style_list_btn_ina.body.grad_color = LV_COLOR_MAKE(0x7f,0x7f,0x7f);
    theme_black_style_list_btn_ina.text.font = (lv_font_t *)ech_setting_conf->font.list_btn_current_font;
    theme_black_style_list_btn_ina.image.color = LV_COLOR_GRAY;
    theme_black_style_list_btn_ina.image.intense = 255;
    theme_black_style_list_btn_ina.image.opa = 255;


    lv_style_copy(&theme_black_style_win_header, &lv_style_scr);
    theme_black_style_win_header.body.main_color = LV_COLOR_MAKE(0x60,0x60,0x60);
    theme_black_style_win_header.body.grad_color = LV_COLOR_MAKE(0x60,0x60,0x60);
    theme_black_style_win_header.body.opa = 255;
    theme_black_style_win_header.text.font = (lv_font_t *)ech_setting_conf->font.win_title_font;
    theme_black_style_win_header.text.color = LV_COLOR_MAKE(0x11,0x11,0x11);

    lv_style_copy(&theme_black_style_idle_big_clock, &lv_style_transp_tight);
    theme_black_style_idle_big_clock.text.color = LV_COLOR_WHITE;
    theme_black_style_idle_big_clock.text.font = (lv_font_t *)ech_setting_conf->font.idle_big_clock_font;

    lv_style_copy(&theme_black_style_idle_date_label, &lv_style_plain);
    theme_black_style_idle_date_label.text.color = LV_COLOR_WHITE;
    theme_black_style_idle_date_label.text.font = (lv_font_t *)ech_setting_conf->font.idle_date_label_font;

    lv_style_copy(&theme_black_style_idle_msg_label, &lv_style_transp_tight);
    theme_black_style_idle_msg_label.text.color = LV_COLOR_WHITE;
    theme_black_style_idle_msg_label.text.font = (lv_font_t *)ech_setting_conf->font.idle_page2_msg_font;

    lv_style_copy(&theme_black_style_switch_bg, &lv_style_pretty);
    theme_black_style_switch_bg.body.radius = LV_RADIUS_CIRCLE;
    theme_black_style_switch_bg.body.main_color = LV_COLOR_MAKE(0xf0, 0xc7, 0xc0);
    theme_black_style_switch_bg.body.grad_color = LV_COLOR_MAKE(0xf0, 0xc7, 0xc0);
    theme_black_style_switch_bg.body.padding.top = 2;
    theme_black_style_switch_bg.body.padding.bottom = 2;
    theme_black_style_switch_bg.body.padding.left = 2;
    theme_black_style_switch_bg.body.padding.right = 2;
    theme_black_style_switch_bg.body.border.width = 0;

    lv_style_copy(&theme_black_style_switch_indic, &lv_style_pretty_color);
    theme_black_style_switch_indic.body.radius = LV_RADIUS_CIRCLE;
    theme_black_style_switch_indic.body.main_color = LV_COLOR_MAKE(0x60, 0x37, 0x10);
    theme_black_style_switch_indic.body.grad_color = LV_COLOR_MAKE(0x60, 0x37, 0x10);
    theme_black_style_switch_indic.body.padding.top = 0;
    theme_black_style_switch_indic.body.padding.bottom = 0;
    theme_black_style_switch_indic.body.padding.left = 0;
    theme_black_style_switch_indic.body.padding.right = 0;
    theme_black_style_switch_indic.body.padding.inner= 0;
    theme_black_style_switch_indic.body.border.width = 0;

    lv_style_copy(&theme_black_style_switch_knob_off, &lv_style_pretty);
    theme_black_style_switch_knob_off.body.radius = LV_RADIUS_CIRCLE;
    theme_black_style_switch_knob_off.body.shadow.width = 0;
    theme_black_style_switch_knob_off.body.shadow.type = LV_SHADOW_BOTTOM;
    theme_black_style_switch_knob_off.body.border.width = 0;
    theme_black_style_switch_knob_off.body.main_color = LV_ech_SWITCH_ON_OFF_INDIC_COLOR;
    theme_black_style_switch_knob_off.body.grad_color = LV_ech_SWITCH_ON_OFF_INDIC_COLOR;

    lv_style_copy(&theme_black_style_switch_knob_on, &lv_style_pretty_color);
    theme_black_style_switch_knob_on.body.radius = LV_RADIUS_CIRCLE;
    theme_black_style_switch_knob_on.body.shadow.width = 0;
    theme_black_style_switch_knob_on.body.shadow.type = LV_SHADOW_BOTTOM;
    theme_black_style_switch_knob_on.body.border.width = 0;
    theme_black_style_switch_knob_on.body.main_color = LV_ech_SWITCH_ON_OFF_INDIC_COLOR;
    theme_black_style_switch_knob_on.body.grad_color = LV_ech_SWITCH_ON_OFF_INDIC_COLOR;

    lv_style_copy(&theme_black_style_rb, &lv_style_pretty_color);
    theme_black_style_rb.body.radius = LV_RADIUS_CIRCLE;
    theme_black_style_rb.body.shadow.width = 0;
    theme_black_style_rb.body.shadow.type = LV_SHADOW_BOTTOM;
    theme_black_style_rb.body.border.width = 0;

    lv_style_copy(&theme_black_style_cb, &lv_style_pretty_color);
    theme_black_style_cb.body.radius = LV_RADIUS_CIRCLE;
    theme_black_style_cb.body.shadow.width = 0;
    theme_black_style_cb.body.shadow.type = LV_SHADOW_BOTTOM;
    theme_black_style_cb.body.border.width = 0;

    lv_style_copy(&theme_black_style_about_label, &theme_black_style_list_scroll);
    theme_black_style_about_label.text.color = LV_COLOR_MAKE(0xee, 0xee, 0xee);
    theme_black_style_about_label.text.font = (lv_font_t *)ech_setting_conf->font.about_label_current_font;

    lv_style_copy(&theme_black_style_status_bar,&lv_style_plain);
    theme_black_style_status_bar.body.main_color = LV_COLOR_MAKE(0x00,0x00,0x00);
    theme_black_style_status_bar.body.grad_color = LV_COLOR_MAKE(0x00,0x00,0x00);
    theme_black_style_status_bar.body.radius = 0;
    theme_black_style_status_bar.body.opa = 240;

    lv_style_copy(&theme_black_style_status_bar_time,&lv_style_plain);
    theme_black_style_status_bar_time.text.color = LV_COLOR_WHITE;
    theme_black_style_status_bar_time.text.font = (lv_font_t *)ech_setting_conf->font.status_bar_time_font;

    lv_style_copy(&theme_black_style_control,&lv_style_plain);
    theme_black_style_control.body.main_color = LV_COLOR_MAKE(0x88,0x33,0x00);
    theme_black_style_control.body.grad_color = LV_COLOR_MAKE(0x88,0x33,0x00);
    theme_black_style_control.text.color = LV_COLOR_WHITE;
    theme_black_style_control.text.font = (lv_font_t *)ech_setting_conf->font.activity_control_font;
#endif
    return true;
}

/*******************
*     NAME:    lv_ech_init_stabar_time_label
*   AUTHOR:    wangls
* DESCRIPT:    初始化状态栏时间label
*     DATE:    2020-8-16
********************/
static bool lv_ech_init_stabar_time_label(void)
{
    bool ret_val = true;
    lv_obj_t *time_label;
    lv_ech_time_t time = {0};
    lv_style_t * label_style;
    label_style = (lv_style_t *)ech_setting_conf->theme.current_theme->style_status_bar_time;
    lv_ech_status_bar_fptr->time_formate = LV_ech_STABAR_TIME_FORMATE_DEFAULT;
    lv_ech_status_bar_fptr->time_label  = lv_label_create(lv_ech_status_bar, NULL);
    time_label = lv_ech_status_bar_fptr->time_label;
    lv_obj_add_style(time_label, LV_LABEL_PART_MAIN, label_style);
    lv_obj_align(time_label, lv_ech_status_bar, LV_ALIGN_IN_LEFT_MID, 0, 0);

    lv_ech_get_time(&time);

    switch(lv_ech_status_bar_fptr->time_formate)
    {
	    case lv_ech_time_format_hhmm:
	    {
	        sprintf(lv_ech_time,"%02d:%02d",time.tm_hour,time.tm_min);
	        break;
	    }

	    case lv_ech_time_format_mmhh:
	    {
	        sprintf(lv_ech_time,"%02d:%02d",time.tm_min,time.tm_hour);
	        break;
	    }

	    case lv_ech_time_format_hhmmss:
	    {
	        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_hour,time.tm_min,time.tm_sec);
	        break;
	    }

	    case lv_ech_time_format_sshhmm:
	    {
	        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_sec,time.tm_hour,time.tm_min);
	        break;
	    }

	    case lv_ech_time_format_ssmmhh:
	    {
	        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_sec,time.tm_min,time.tm_hour);
	        break;
	    }

	    case lv_ech_time_format_mmhhss:
	    {
	        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_min,time.tm_hour,time.tm_sec);
	        break;
	    }

	    default:
	    {
	        sprintf(lv_ech_time,"%02d:%02d",time.tm_hour,time.tm_min);
	    }
    }

    lv_label_set_text(time_label, lv_ech_time);
    return ret_val;
}

/*******************
*     NAME:    lv_ech_create_activity
*   AUTHOR:    wangls
* DESCRIPT:    创建一个有效的activity
*     DATE:    2020-08-02
********************/
lv_ech_activity_t *lv_ech_create_activity(lv_ech_activity_ext_t *activity_ext,
        bool has_stabar,
        bool has_control,
        lv_ech_control_text_t *control_text)
{
    static bool is_lv_ech_atctivity_init = false;
    lv_style_t * ech_display_style = NULL;

    if(!is_lv_ech_atctivity_init)
    {
        is_lv_ech_atctivity_init = true;
        lv_ech_theme_init();
        lv_ech_status_bar_init();
        lv_ech_activity_list_init();
        lv_ech_stack_init();
		UART1_apTrace("FUNC: %s LINE: %d\r\n", __func__, __LINE__);
    }
	/*主题*/
    ech_display_style = (lv_style_t *)ech_setting_conf->theme.current_theme->style_base;
    lv_ech_activity_t *activity = (lv_ech_activity_t *)lv_mem_alloc(sizeof(lv_ech_activity_t));

    memset(activity,0,sizeof(lv_ech_activity_t));
    if(_idle_activity == NULL)
    {
        _idle_activity = activity;
    }
    lv_ech_stack_push(activity);
    lv_ech_activity_list_insert(activity);

    current_activity = activity;

    activity->has_control = has_control;
    activity->has_stabar= has_stabar;
    activity->status_bar = lv_ech_status_bar;
    activity->activity_ext.actId = activity_ext->actId;
    activity->activity_ext.create = activity_ext->create;
    activity->activity_ext.prepare_destory = activity_ext->prepare_destory;

    activity->base = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(activity->base,LV_ech_SCREEN_SCALE_HOR_RES,LV_ech_SCREEN_SCALE_VER_RES);
    lv_obj_set_pos(activity->base,LV_ech_SCREEN_X,LV_ech_SCREEN_Y);

    lv_obj_add_style(activity->base, LV_OBJ_PART_MAIN, ech_display_style);
    activity->display = lv_img_create(activity->base,NULL);
    lv_img_set_auto_size(activity->display, false);
    if(has_stabar)
    {
        lv_obj_set_size(activity->display,LV_ech_DISPLAY_NOCTR_HOR_RES,LV_ech_DISPLAY_NOCTR_VER_RES);
        lv_obj_set_pos(activity->display,LV_ech_DISPLAY_NOCTR_POSITION_X,LV_ech_DISPLAY_NOCTR_POSITION_Y);
        if(current_activity == _idle_activity)
        {
            lv_img_set_src(activity->display,&ic_launcher_bg);
        }
        lv_obj_set_parent(lv_ech_status_bar, activity->base);
    }
    else
    {
        lv_obj_set_size(activity->display,LV_ech_DISPLAY_NOCTR_STABAR_HOR_RES,LV_ech_DISPLAY_NOCTR_STABAR_VER_RES);
        lv_obj_set_pos(activity->display,LV_ech_DISPLAY_NOCTR_STABAR_POSITION_X,LV_ech_DISPLAY_NOCTR_STABAR_POSITION_Y);
        if(current_activity == _idle_activity)
        {
            lv_img_set_src(activity->display,&ic_launcher_bg);
        }
    }
    if(has_control)
    {
        if(control_text != NULL)
        {
            lv_ech_control_init(activity,
                                       control_text->left_text,
                                       control_text->middle_text,
                                       control_text->right_text);
        }
        else
        {
            lv_ech_control_init(activity,
                                       "",
                                       "",
                                       "");
        }
    }

    if(NULL == ancient_signal_func)
    {
        ancient_signal_func = activity->display->signal_cb;
    }

    if(NULL == ancient_design_func)
    {
        ancient_design_func = activity->display->design_cb;
    }

    if(NULL == ancient_event_func)
    {
        ancient_event_func = activity->display->event_cb;
    }

    lv_obj_set_signal_cb(activity->display, lv_ech_signal_cb);
    lv_obj_set_design_cb(activity->display, lv_ech_design_cb);
    lv_obj_set_event_cb(activity->display, lv_ech_event_cb);

    activity->signal_func = NULL;
    activity->design_func = NULL;
    activity->event_func = NULL;

#if 1
    if(ech_indev_group == NULL)
    {
        ech_indev_group = lv_group_create();
        ech_keypad_dev  = lv_ech_get_keypad_dev();
        lv_group_set_wrap(ech_indev_group,true);
        lv_indev_set_group(ech_keypad_dev,ech_indev_group);
    }

    lv_group_focus_freeze(ech_indev_group,false);
    lv_group_add_obj(ech_indev_group,activity->display);
    lv_group_focus_obj(activity->display);
    lv_group_focus_freeze(ech_indev_group,true);
#endif
    if(activity->activity_ext.create != NULL)
    {
        activity->ext_data = (void *)activity->activity_ext.create(activity->display);
    }

    return activity;
}

/*******************
*     NAME:    lv_ech_activity_list_lookup
*   AUTHOR:    wangls
* DESCRIPT:    从activity查询表中查询display的activity
*     DATE:    2020-08-16
********************/
lv_ech_activity_t *	lv_ech_activity_list_lookup(lv_ech_display_t * display)
{
    lv_ech_activity_list_node_t * p = lv_ech_activity_list->head;
    if(display == NULL)
    {
        return NULL;
    }
    if(p->next != NULL)
    {
        p = p->next;
        while(p)
        {
            if(p->activity->display == display && p->activity != NULL && p->activity->display != NULL)
            {
                return p->activity;
            }
            p = p->next;
        }
    }
    return NULL;
}

/*******************
*	    NAME: lv_ech_stabar_task
*	  AUTHOR: wangls
* DESCRIPT: 状态栏任务
*	    DATE: 2020-8-16
********************/
void lv_ech_stabar_task(lv_task_t * task)
{
    static lv_ech_time_t time = {0};
    int k;
    //lv_ech_get_time(&time);

    switch(lv_ech_status_bar_fptr->time_formate)
    {
    case lv_ech_time_format_hhmm:
    {
        sprintf(lv_ech_time,"%02d:%02d",time.tm_hour,time.tm_min);
        break;
    }

    case lv_ech_time_format_mmhh:
    {
        sprintf(lv_ech_time,"%02d:%02d",time.tm_min,time.tm_hour);
        break;
    }

    case lv_ech_time_format_hhmmss:
    {
        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_hour,time.tm_min,time.tm_sec);
        break;
    }

    case lv_ech_time_format_sshhmm:
    {
        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_sec,time.tm_hour,time.tm_min);
        break;
    }

    case lv_ech_time_format_ssmmhh:
    {
        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_sec,time.tm_min,time.tm_hour);
        break;
    }

    case lv_ech_time_format_mmhhss:
    {
        sprintf(lv_ech_time,"%02d:%02d:%02d",time.tm_min,time.tm_hour,time.tm_sec);
        break;
    }

    default:
    {
        sprintf(lv_ech_time,"%02d:%02d",time.tm_hour,time.tm_min);
    }
    }
    lv_label_set_text(lv_ech_status_bar_fptr->time_label,lv_ech_time);

    for(k = 0; k < LV_ech_STABAR_TASK_EXT_LENGTH; k++)
    {
        if(status_bar_task_ext[k] != NULL)
        {
            (status_bar_task_ext[k])();
        }
    }
}

/*******************
*     NAME:    lv_ech_status_bar_task_ext_add
*   AUTHOR:    wangls
* DESCRIPT:    添加状态栏额外任务
*     DATE:    2020-8-16
********************/
bool lv_ech_status_bar_task_ext_add(status_bar_task_t task)
{
    static int stabar_task_ext_count = 0;
    if(stabar_task_ext_count >= LV_ech_STABAR_TASK_EXT_LENGTH)
    {
        return false;
    }

    status_bar_task_ext[stabar_task_ext_count] = task;
    stabar_task_ext_count = stabar_task_ext_count + 1;
    return true;
}

/*******************
*     NAME:    lv_ech_stabar_battery_task
*   AUTHOR:    wangls
* DESCRIPT:    电池效果
*     DATE:    2020-8-16
********************/
static void lv_ech_stabar_battery_task(void)
{
    static lv_img_dsc_t * pre_battery_img = NULL;
    lv_img_dsc_t * cur_battery_img = lv_ech_get_battery_img();
    if(cur_battery_img != pre_battery_img && cur_battery_img != NULL)
    {
        pre_battery_img = cur_battery_img;
        lv_img_set_src(lv_ech_status_bar_fptr->battery_img, cur_battery_img);
    }
}

/*******************
*     NAME:    lv_ech_get_display_width
*   AUTHOR:    wangls
* DESCRIPT:    获取显示区域宽
*     DATE:    2020-8-16
********************/
lv_coord_t lv_ech_get_display_width(const lv_ech_display_t * display)
{
    return lv_obj_get_width(display);
}

/*******************
*     NAME:    lv_ech_get_display_height
*   AUTHOR:    wangls
* DESCRIPT:    获取显示区域高
*     DATE:    2020-8-16
********************/
lv_coord_t lv_ech_get_display_height(lv_ech_display_t * display)
{
    lv_coord_t height = 0;
    lv_ech_activity_t * activity;
    activity = lv_ech_activity_list_lookup(display);
    if(activity->has_control)
    {
        height = -LV_ech_CONTROL_VER_RES;
    }
    height = height + lv_obj_get_height(display);
    return height;
}

/*******************
*     NAME:    lv_ech_activity_set_signal_cb
*   AUTHOR:    wangls
* DESCRIPT:    设置activity的signal函数
*     NOTE:    signal函数运行机制:
					lv_xxx_create(parent,copy) ==> 调用parent->signal_func函数
*     DATE:    2020-8-16
********************/
void lv_ech_activity_set_signal_cb(lv_ech_activity_t *activity,
        lv_signal_cb_t func)
{
    if(NULL != func)
    {
        activity->signal_func = func;
    }
}

/*******************
*     NAME:    lv_ech_activity_set_design_cb
*   AUTHOR:    wangls
* DESCRIPT:    设置activity的signal函数
*     DATE:    2020-8-16
********************/
void lv_ech_activity_set_design_cb(lv_ech_activity_t *activity,
        lv_design_cb_t func)
{
    if(NULL != func)
    {
        activity->design_func = func;
    }
}

/*******************
*     NAME:    lv_ech_get_battery_state
*   AUTHOR:    wangls
* DESCRIPT:    获取电池状态，
*     DATE:    2020-8-16
********************/
UINT8 lv_ech_get_battery_state(void)
{
    battery_values_t * battery_value = lv_mem_alloc(sizeof(battery_values_t));
    ech_battery_get_status(battery_value);
    lv_ech_status_bar_fptr->has_battery = battery_value->battery_status == 1? true:false;
    lv_mem_free(battery_value);
    return battery_value->battery_status;
}

/*******************
*     NAME:    lv_ech_get_battery_img
*   AUTHOR:    wangls
* DESCRIPT:    <BB><F1>?<B5><B1>???<B5><E7><B3><D8>?<B1><EA>
*     DATE:    2020-08-16
********************/
lv_img_dsc_t * lv_ech_get_battery_img(void)
{
	battery_values_t battery_t;
	ech_battery_get_status(&battery_t);
    const lv_img_dsc_t * battery_img = NULL;
	static uint8_t battery_img_cur = 0;
	static uint8_t low_battery_check_count = 0;

    if(!battery_t.battery_status)
    {
        battery_img = &stat_sys_no_battery;
        return (lv_img_dsc_t *)battery_img;
    }

    if(ech_CHG_DISCONNECTED == battery_t.charging)
    {
        if(battery_t.battery_value >= 100)
        {
            battery_img = &stat_sys_battery_100;
        }
        else if(battery_t.battery_value >= 85)
        {
            battery_img = &stat_sys_battery_85;
        }
        else if(battery_t.battery_value >= 71)
        {
            battery_img = &stat_sys_battery_71;
        }
        else if(battery_t.battery_value >= 57)
        {
            battery_img = &stat_sys_battery_57;
        }
        else if(battery_t.battery_value >= 43)
        {
            battery_img = &stat_sys_battery_43;
        }
        else if(battery_t.battery_value >= 28)
        {
            battery_img = &stat_sys_battery_28;
        }
        else if(battery_t.battery_value >= 15)
        {
            battery_img = &stat_sys_battery_15;
        }
        else if(battery_t.battery_value >= 0)
        {
            battery_img = &stat_sys_battery_0;
            if(low_battery_check_count < 1)
            {
	
            }
            low_battery_check_count = (low_battery_check_count + 1) % 60;
            return (lv_img_dsc_t *)battery_img;
        }
        low_battery_check_count = 0;
    }
    else
    {
        if(battery_t.battery_value >= 100)
        {
			battery_img_cur = 7;
            battery_img = battery_img_dispaly[battery_img_cur];
        }
        else if(battery_t.battery_value >= 85)
        {
			battery_img = battery_img_dispaly[battery_img_cur];
			battery_img_cur++;
			if(battery_img_cur>7)
			battery_img_cur=6;
        }
        else if(battery_t.battery_value >= 71)
        {
			battery_img = battery_img_dispaly[battery_img_cur];

			battery_img_cur++;
			if(battery_img_cur>7)
			battery_img_cur=5;
        }
        else if(battery_t.battery_value >= 57)
        {
            battery_img = battery_img_dispaly[battery_img_cur];
			battery_img_cur++;
			if(battery_img_cur>7)
			battery_img_cur=4;
        }
        else if(battery_t.battery_value >= 43)
        {
            battery_img = battery_img_dispaly[battery_img_cur];
			battery_img_cur++;
			if(battery_img_cur>7)
			battery_img_cur=3;
        }
        else if(battery_t.battery_value >= 28)
        {
            battery_img = battery_img_dispaly[battery_img_cur];
			battery_img_cur++;
			if(battery_img_cur>7)
			battery_img_cur=2;
        }
        else if(battery_t.battery_value >= 15)
        {
            battery_img = battery_img_dispaly[battery_img_cur];
			battery_img_cur++;
			if(battery_img_cur>7)
			battery_img_cur=1;
        }
        else if(battery_t.battery_value >= 0)
        {
            battery_img = battery_img_dispaly[battery_img_cur];
			battery_img_cur++;
			if(battery_img_cur>7)
			battery_img_cur=0;
        }
    }
    return (lv_img_dsc_t *)battery_img;
}

/*******************
*	  NAME:    lv_ech_init_stabar_battery_img
*	AUTHOR:    wangls
* DESCRIPT:    初始化状态栏电池图标
*	  DATE:    2020-8-16
********************/
static bool lv_ech_init_stabar_battery_img(void)
{
	bool ret_val = true;
	lv_obj_t *obj = NULL;

	lv_ech_status_bar_fptr->has_battery = lv_ech_get_battery_state();
	lv_ech_status_bar_fptr->battery_img = lv_img_create(lv_ech_status_bar, NULL);
	obj = lv_ech_status_bar_fptr->battery_img;

	lv_img_set_src(obj, lv_ech_get_battery_img());
	lv_obj_align(obj, lv_ech_status_bar, LV_ALIGN_IN_RIGHT_MID, 0, 0);
	return ret_val;
}
	

#ifdef __cplusplus
}
#endif
