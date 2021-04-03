#include "../lv_include/lv_ech_lib.h"
#include "../lv_objx/lv_ech_obj/lv_font_resource.h"
#include "../lv_objx/lv_ech_obj/lv_ech_obj.h"
#include "lv_gui_main.h"
#include <stdlib.h>
#include "../lv_include/lv_ech_type.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

static nv_ech_setting_msg_t ech_setting_conf_local = {0};
static nv_ech_theme_msg_node_t theme_white = {0};
#ifdef CONFIG_ech_GUI_CHOICE_THEME_SUPPORT
static nv_ech_theme_msg_node_t theme_black = {0};
#endif

#define ECH_SETTING_CONFIG_FILENAME CONFIG_FS_AP_NVM_DIR "/ech_setting_config.nv"
#define ECH_SETTING_CONFIG_FILESIZE (sizeof(nv_ech_setting_msg_t))
#define ECH_SETTING_CONFIG_BUFFER (&ech_setting_conf_local)
static bool nv_ech_setting_config_is_writed = false;


/*
      name : lv_ech_get_keypad_dev
    return : get keypad indev
      date : 2020-04-22
*/
OUT lv_indev_t *
lv_ech_get_keypad_dev(void)
{
	//return lvGuiGetKeyPad();
}

/*
      name : lv_ech_setting_conf_init
    return : bool
      date : 2020-03-30
*/
OUT bool
lv_ech_setting_conf_init(void)
{
    memset(&ech_setting_conf_local, 0, ECH_SETTING_CONFIG_FILESIZE);
    ech_mmi_ech_setting_config(ECH_SETTING_CONFIG_BUFFER);

	return true;

lv_ech_setting_nvm_failed:
	ech_mmi_ech_setting_config(ECH_SETTING_CONFIG_BUFFER);
	return false;
}

/*
      name : lv_ech_setting_conf_read
    return : point a buff
      date : 2020-03-30
*/
OUT nv_ech_setting_msg_t *
lv_ech_setting_conf_read(void)
{
	if(nv_ech_setting_config_is_writed)
	{
		nv_ech_setting_config_is_writed = false;
		//vfs_sfile_read(ECH_SETTING_CONFIG_FILENAME, ECH_SETTING_CONFIG_BUFFER, ECH_SETTING_CONFIG_FILESIZE);
	}

    return ECH_SETTING_CONFIG_BUFFER;
}

/*
      name : lv_ech_setting_conf_write
    return : length of buff
      date : 2020-03-30
*/
OUT int32_t
lv_ech_setting_conf_write(void)
{
	int file_size = -1;
//	file_size = vfs_sfile_write(ech_SETTING_CONFIG_FILENAME, ECH_SETTING_CONFIG_BUFFER, ECH_SETTING_CONFIG_FILESIZE);
//	nv_ech_setting_config_is_writed = true;
  return file_size;
}

/*
      name : lv_ech_get_time
    return : get local time
      date : 2020-03-30
*/
void
lv_ech_get_time(OUT lv_ech_time_t * time)
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
      name : ech_set_lcd_status
     param : config lcd state
      date : 2020-03-30
*/
void
ech_set_lcd_status(IN int8_t wakeup)
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
      name : ech_get_lcd_status
    return : get lcd state
      date : 2020-03-30
*/
OUT bool
ech_get_lcd_status(void)
{
	//return lvGuiGetScreenStatus();
	return true;
}

/*
      name : prv_ech_mmi_ech_setting_config_const
     param : config nv
      date : 2020-08-16
*/
static
void
prv_ech_mmi_ech_setting_config_const(OUT nv_ech_setting_msg_t * ech_setting)
{	
	ech_setting->font.list_btn_big_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.list_btn_small_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.about_label_big_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.about_label_small_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.win_title_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.activity_control_font = (uint32_t)LV_ech_FONT_MSYH(2500, 14);
	ech_setting->font.status_bar_time_font = (uint32_t)LV_ech_FONT_MSYH(2500, 14);
	ech_setting->font.idle_big_clock_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);//time
	ech_setting->font.idle_date_label_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);//label
	ech_setting->font.idle_page2_msg_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.idle_popwindows_msg_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.idle_lockgroupwindows_msg_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);
	ech_setting->font.idle_shutdownwindows_msg_font = (uint32_t)LV_ech_FONT_MSYH(2500, 15);

	ech_setting->theme.white = &theme_white;
	ech_setting->theme.white->style_base = (uint32_t)&theme_white_style_base;
	ech_setting->theme.white->style_list_scroll = (uint32_t)&theme_white_style_list_scroll;
	ech_setting->theme.white->style_list_page = (uint32_t)&theme_white_style_list_page;
	ech_setting->theme.white->style_list_btn_rel = (uint32_t)&theme_white_style_list_btn_rel;
	ech_setting->theme.white->style_list_btn_pr = (uint32_t)&theme_white_style_list_btn_pr;
	ech_setting->theme.white->style_list_btn_ina = (uint32_t)&theme_white_style_list_btn_ina;
	ech_setting->theme.white->style_idle_big_clock = (uint32_t)&theme_white_style_idle_big_clock;
	ech_setting->theme.white->style_idle_date_label = (uint32_t)&theme_white_style_idle_date_label;
	ech_setting->theme.white->style_idle_msg_label = (uint32_t)&theme_white_style_idle_msg_label;
	ech_setting->theme.white->style_about_label = (uint32_t)&theme_white_style_about_label;
	ech_setting->theme.white->style_cb = (uint32_t)&theme_white_style_rb;
	ech_setting->theme.white->style_rb = (uint32_t)&theme_white_style_cb;
	ech_setting->theme.white->style_switch_bg = (uint32_t)&theme_white_style_switch_bg;
	ech_setting->theme.white->style_switch_indic = (uint32_t)&theme_white_style_switch_indic;
	ech_setting->theme.white->style_switch_knob_off = (uint32_t)&theme_white_style_switch_knob_off;
	ech_setting->theme.white->style_switch_knob_on = (uint32_t)&theme_white_style_switch_knob_on;
	ech_setting->theme.white->style_status_bar = (uint32_t)&theme_white_style_status_bar;
	ech_setting->theme.white->style_status_bar_time = (uint32_t)&theme_white_style_status_bar_time;
	ech_setting->theme.white->style_win_header = (uint32_t)&theme_white_style_win_header;
	ech_setting->theme.white->style_control = (uint32_t)&theme_white_style_control;


#ifdef CONFIG_ech_GUI_CHOICE_THEME_SUPPORT
	ech_setting->theme.black = &theme_black;
	ech_setting->theme.black->style_base = (uint32_t)&theme_black_style_base;
	ech_setting->theme.black->style_list_scroll = (uint32_t)&theme_black_style_list_scroll;
	ech_setting->theme.black->style_list_page = (uint32_t)&theme_black_style_list_page;
	ech_setting->theme.black->style_list_btn_rel = (uint32_t)&theme_black_style_list_btn_rel;
	ech_setting->theme.black->style_list_btn_pr = (uint32_t)&theme_black_style_list_btn_pr;
	ech_setting->theme.black->style_list_btn_ina = (uint32_t)&theme_black_style_list_btn_ina;
	ech_setting->theme.black->style_idle_big_clock = (uint32_t)&theme_black_style_idle_big_clock;
	ech_setting->theme.black->style_idle_date_label = (uint32_t)&theme_black_style_idle_date_label;
	ech_setting->theme.black->style_idle_msg_label = (uint32_t)&theme_black_style_idle_msg_label;
	ech_setting->theme.black->style_about_label = (uint32_t)&theme_black_style_about_label;
	ech_setting->theme.black->style_cb = (uint32_t)&theme_black_style_rb;
	ech_setting->theme.black->style_rb = (uint32_t)&theme_black_style_cb;
	ech_setting->theme.black->style_switch_bg = (uint32_t)&theme_black_style_switch_bg;
	ech_setting->theme.black->style_switch_indic = (uint32_t)&theme_black_style_switch_indic;
	ech_setting->theme.black->style_switch_knob_off = (uint32_t)&theme_black_style_switch_knob_off;
	ech_setting->theme.black->style_switch_knob_on = (uint32_t)&theme_black_style_switch_knob_on;
	ech_setting->theme.black->style_status_bar = (uint32_t)&theme_black_style_status_bar;
	ech_setting->theme.black->style_status_bar_time = (uint32_t)&theme_black_style_status_bar_time;
	ech_setting->theme.black->style_win_header = (uint32_t)&theme_black_style_win_header;
	ech_setting->theme.black->style_control = (uint32_t)&theme_black_style_control;
#endif
}

/*
      name : ech_mmi_ech_setting_config
     param : [ech_setting] IN param
      date : 2020-03-30
*/
void
ech_mmi_ech_setting_config(OUT nv_ech_setting_msg_t * ech_setting)
{
	prv_ech_mmi_ech_setting_config_const(ech_setting);
	ech_setting->theme.type = 0;
	ech_setting->theme.current_theme = ech_setting->theme.white;
	ech_setting->read_and_write_check = 0x3f;
	ech_setting->btn_voice_switch = 0;
#ifdef CONFIG_ech_TTS_SUPPORT
	ech_setting->voice_broadcast_switch = 0;
#endif
#ifdef CONFIG_ech_GUI_KEYPAD_LIGHT_SUPPORT
	ech_setting->keypad_led_switch = 0;
#endif
	ech_setting->GPS_switch = 0;
	ech_setting->electric_torch_switch = 0;
	ech_setting->screen_brightness = 4;
	ech_setting->screen_bright_time = 2;
	ech_setting->main_SIM = 0;
#ifdef CONFIG_ech_GUI_CHOICE_NET_TYPE_SUPPORT
	ech_setting->net_type = 0;
#endif
	ech_setting->font.big_font_switch = 1;
	ech_setting->font.list_page_colum_count = 3;
	ech_setting->font.list_btn_current_font = ech_setting->font.list_btn_small_font;
	ech_setting->font.about_label_current_font = ech_setting->font.about_label_small_font;
	ech_setting->volume = 5;
	ech_setting->language = 0;
#ifdef CONFIG_AT_MY_ACCOUNT_SUPPORT
	strcpy(ech_setting->account_name, "00000");
	strcpy(ech_setting->account_passwd, "00000");
	strcpy(ech_setting->ip_address, "124.160.11.21");
	ech_setting->ip_port = 10000;
#endif
}

/*
      name : ech_battery_get_status
     param : point a battery buff
      date : 2020-08-16
*/
void
ech_battery_get_status(OUT battery_values_t *values)
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
		values->charging = ech_CHG_DISCONNECTED;
	}
	else if(status[1] == 1 || status[1] == 2)
	{
		values->charging = ech_CHG_CONNECTED;
	}
	else
	{
		values->charging = ech_CHG_DISCONNECTED;
	}

	uint32_t * temp = (uint32_t *)(&(status[4]));
	values->charge_cur_mA = *temp;
	temp = (uint32_t *)(&(status[8]));
	values->battery_val_mV = *temp;
	temp = (uint32_t *)(&(status[12]));
	values->battery_temp = *temp;
}


