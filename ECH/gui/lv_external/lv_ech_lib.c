#include "../lv_include/lv_ech_lib.h"
#include "../lv_objx/lv_ech_obj/lv_font_resource.h"
#include "../lv_objx/lv_ech_obj/lv_ech_obj.h"
#include "lv_gui_main.h"
#include <stdlib.h>
#include "../lv_include/lv_ech_type.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

static nv_poc_setting_msg_t poc_setting_conf_local = {0};
static nv_poc_theme_msg_node_t theme_white = {0};
#ifdef CONFIG_POC_GUI_CHOICE_THEME_SUPPORT
static nv_poc_theme_msg_node_t theme_black = {0};
#endif

#define POC_SETTING_CONFIG_FILENAME CONFIG_FS_AP_NVM_DIR "/poc_setting_config.nv"
#define POC_SETTING_CONFIG_FILESIZE (sizeof(nv_poc_setting_msg_t))
#define POC_SETTING_CONFIG_BUFFER (&poc_setting_conf_local)
static bool nv_poc_setting_config_is_writed = false;


/*
      name : lv_poc_get_keypad_dev
    return : get keypad indev
      date : 2020-04-22
*/
OUT lv_indev_t *
lv_poc_get_keypad_dev(void)
{
	//return lvGuiGetKeyPad();
}

/*
      name : lv_poc_setting_conf_init
    return : bool
      date : 2020-03-30
*/
OUT bool
lv_poc_setting_conf_init(void)
{

}

/*
      name : lv_poc_setting_conf_read
    return : point a buff
      date : 2020-03-30
*/
OUT nv_poc_setting_msg_t *
lv_poc_setting_conf_read(void)
{
	if(nv_poc_setting_config_is_writed)
	{
//		nv_poc_setting_config_is_writed = false;
//		vfs_sfile_read(POC_SETTING_CONFIG_FILENAME, POC_SETTING_CONFIG_BUFFER, POC_SETTING_CONFIG_FILESIZE);
	}

    //return POC_SETTING_CONFIG_BUFFER;
}

/*
      name : lv_poc_setting_conf_write
    return : length of buff
      date : 2020-03-30
*/
OUT int32_t
lv_poc_setting_conf_write(void)
{
//	int file_size = -1;
//	file_size = vfs_sfile_write(POC_SETTING_CONFIG_FILENAME, POC_SETTING_CONFIG_BUFFER, POC_SETTING_CONFIG_FILESIZE);
//	nv_poc_setting_config_is_writed = true;
//  return file_size;
}

/*
      name : lv_poc_get_time
    return : get local time
      date : 2020-03-30
*/
void
lv_poc_get_time(OUT lv_poc_time_t * time)
{
	if(time == NULL)
	{
		return;
	}
    struct tm system_time;

	system_time.tm_hour = 6;
	system_time.tm_mday = 16;
	system_time.tm_min = 39;
	system_time.tm_mon = 7;
	system_time.tm_sec = 25;
	system_time.tm_year = 20;
	system_time.tm_wday = 6;

    system_time.tm_hour = system_time.tm_hour + 8;
	system_time.tm_mon = system_time.tm_mon + 1;/*优化月份 + 1 0-11*/
	if(system_time.tm_hour > 23)
	{
		system_time.tm_hour = system_time.tm_hour % 24;
		system_time.tm_mday = system_time.tm_mday + 1;
		switch(system_time.tm_mon)//月份0-11
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
				if(system_time.tm_mday > 31)
				{
					system_time.tm_mday = system_time.tm_mday % 32 + 1;
					system_time.tm_mon = system_time.tm_mon + 1;
				}
				break;

			case 4:
			case 6:
			case 9:
			case 11:
				if(system_time.tm_mday > 30)
				{
					system_time.tm_mday = system_time.tm_mday % 31 + 1;
					system_time.tm_mon = system_time.tm_mon + 1;
				}
				break;

			case 2:
				if(system_time.tm_year % 400 == 0 || (system_time.tm_year % 100 != 0 && system_time.tm_year % 4 == 0))
				{
					if(system_time.tm_mday > 29)
					{
						system_time.tm_mday = system_time.tm_mday % 30 + 1;
						system_time.tm_mon = system_time.tm_mon + 1;
					}
				}
				else
				{
					if(system_time.tm_mday > 28)
					{
						system_time.tm_mday = system_time.tm_mday % 29 + 1;
						system_time.tm_mon = system_time.tm_mon + 1;
					}
				}

				break;
			case 12:
				if(system_time.tm_mday > 31)
				{
					system_time.tm_mday = system_time.tm_mday % 32 + 1;
					system_time.tm_mon = system_time.tm_mon % 13 + 1;
					system_time.tm_year = system_time.tm_year + 1;
				}
				break;
			default:
				break;
		}
	}

	time->tm_year = system_time.tm_year;
	time->tm_mon = system_time.tm_mon;
	time->tm_mday = system_time.tm_mday;
	time->tm_hour = system_time.tm_hour;
	time->tm_min = system_time.tm_min;
	time->tm_sec = system_time.tm_sec;
	time->tm_wday = system_time.tm_wday;
}

/*
      name : poc_set_lcd_status
     param : config lcd state
      date : 2020-03-30
*/
void
poc_set_lcd_status(IN int8_t wakeup)
{
	if(wakeup != 0)
	{
		//lvGuiScreenOn();
	}
	else
	{
		//lvGuiScreenOff();
	}
}

/*
      name : poc_get_lcd_status
    return : get lcd state
      date : 2020-03-30
*/
OUT bool
poc_get_lcd_status(void)
{
	//return lvGuiGetScreenStatus();
	return true;
}

/*
      name : nv_setting_config_const
     param : config nv
      date : 2020-08-16
*/
void
nv_setting_config_const(OUT nv_poc_setting_msg_t * poc_setting)
{	
	poc_setting->font.list_btn_big_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.list_btn_small_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.about_label_big_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.about_label_small_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.win_title_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.activity_control_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.status_bar_time_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.idle_big_clock_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;//time
	poc_setting->font.idle_date_label_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;//label
	poc_setting->font.idle_page2_msg_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.idle_popwindows_msg_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.idle_lockgroupwindows_msg_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;
	poc_setting->font.idle_shutdownwindows_msg_font = (uint32_t)LV_THEME_DEFAULT_FONT_NORMAL;

	poc_setting->theme.white = &theme_white;
	poc_setting->theme.white->style_base = (uint32_t)&theme_white_style_base;
	poc_setting->theme.white->style_list_scroll = (uint32_t)&theme_white_style_list_scroll;
	poc_setting->theme.white->style_list_page = (uint32_t)&theme_white_style_list_page;
	poc_setting->theme.white->style_list_btn_rel = (uint32_t)&theme_white_style_list_btn_rel;
	poc_setting->theme.white->style_list_btn_pr = (uint32_t)&theme_white_style_list_btn_pr;
	poc_setting->theme.white->style_list_btn_ina = (uint32_t)&theme_white_style_list_btn_ina;
	poc_setting->theme.white->style_idle_big_clock = (uint32_t)&theme_white_style_idle_big_clock;
	poc_setting->theme.white->style_idle_date_label = (uint32_t)&theme_white_style_idle_date_label;
	poc_setting->theme.white->style_idle_msg_label = (uint32_t)&theme_white_style_idle_msg_label;
	poc_setting->theme.white->style_about_label = (uint32_t)&theme_white_style_about_label;
	poc_setting->theme.white->style_cb = (uint32_t)&theme_white_style_rb;
	poc_setting->theme.white->style_rb = (uint32_t)&theme_white_style_cb;
	poc_setting->theme.white->style_switch_bg = (uint32_t)&theme_white_style_switch_bg;
	poc_setting->theme.white->style_switch_indic = (uint32_t)&theme_white_style_switch_indic;
	poc_setting->theme.white->style_switch_knob_off = (uint32_t)&theme_white_style_switch_knob_off;
	poc_setting->theme.white->style_switch_knob_on = (uint32_t)&theme_white_style_switch_knob_on;
	poc_setting->theme.white->style_status_bar = (uint32_t)&theme_white_style_status_bar;
	poc_setting->theme.white->style_status_bar_time = (uint32_t)&theme_white_style_status_bar_time;
	poc_setting->theme.white->style_win_header = (uint32_t)&theme_white_style_win_header;
	poc_setting->theme.white->style_control = (uint32_t)&theme_white_style_control;


#ifdef CONFIG_POC_GUI_CHOICE_THEME_SUPPORT
	poc_setting->theme.black = &theme_black;
	poc_setting->theme.black->style_base = (uint32_t)&theme_black_style_base;
	poc_setting->theme.black->style_list_scroll = (uint32_t)&theme_black_style_list_scroll;
	poc_setting->theme.black->style_list_page = (uint32_t)&theme_black_style_list_page;
	poc_setting->theme.black->style_list_btn_rel = (uint32_t)&theme_black_style_list_btn_rel;
	poc_setting->theme.black->style_list_btn_pr = (uint32_t)&theme_black_style_list_btn_pr;
	poc_setting->theme.black->style_list_btn_ina = (uint32_t)&theme_black_style_list_btn_ina;
	poc_setting->theme.black->style_idle_big_clock = (uint32_t)&theme_black_style_idle_big_clock;
	poc_setting->theme.black->style_idle_date_label = (uint32_t)&theme_black_style_idle_date_label;
	poc_setting->theme.black->style_idle_msg_label = (uint32_t)&theme_black_style_idle_msg_label;
	poc_setting->theme.black->style_about_label = (uint32_t)&theme_black_style_about_label;
	poc_setting->theme.black->style_cb = (uint32_t)&theme_black_style_rb;
	poc_setting->theme.black->style_rb = (uint32_t)&theme_black_style_cb;
	poc_setting->theme.black->style_switch_bg = (uint32_t)&theme_black_style_switch_bg;
	poc_setting->theme.black->style_switch_indic = (uint32_t)&theme_black_style_switch_indic;
	poc_setting->theme.black->style_switch_knob_off = (uint32_t)&theme_black_style_switch_knob_off;
	poc_setting->theme.black->style_switch_knob_on = (uint32_t)&theme_black_style_switch_knob_on;
	poc_setting->theme.black->style_status_bar = (uint32_t)&theme_black_style_status_bar;
	poc_setting->theme.black->style_status_bar_time = (uint32_t)&theme_black_style_status_bar_time;
	poc_setting->theme.black->style_win_header = (uint32_t)&theme_black_style_win_header;
	poc_setting->theme.black->style_control = (uint32_t)&theme_black_style_control;
#endif
}

/*
      name : poc_battery_get_status
     param : point a battery buff
      date : 2020-08-16
*/
void
poc_battery_get_status(OUT battery_values_t *values)
{
	int8_t status[16];
	memset(status, 0, sizeof(int8_t) * 16);
	//drvChargerGetStatus(status);
	status[0] = 1;
	status[2] = 55;
	status[1] = 0;
	status[4] = 200;
	status[8] = 3600;
	status[12] = 35;
	
	values->battery_status = status[0];

	values->battery_value = status[2];

	if(status[1] == 0 || status[1] == 3)
	{
		values->charging = POC_CHG_DISCONNECTED;
	}
	else if(status[1] == 1 || status[1] == 2)
	{
		values->charging = POC_CHG_CONNECTED;
	}
	else
	{
		values->charging = POC_CHG_DISCONNECTED;
	}

	uint32_t * temp = (uint32_t *)(&(status[4]));
	values->charge_cur_mA = *temp;
	temp = (uint32_t *)(&(status[8]));
	values->battery_val_mV = *temp;
	temp = (uint32_t *)(&(status[12]));
	values->battery_temp = *temp;
}


