#ifndef __LV_POC_LIB_H_
#define __LV_POC_LIB_H_

#include "lvgl.h"
#include "lv_ech.h"

#define LV_POC_ACTIVITY_ATTRIBUTE_CB_SET_SIZE (10)

struct tm
{
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
#ifdef __TM_GMTOFF
  long	__TM_GMTOFF;
#endif
#ifdef __TM_ZONE
  const char *__TM_ZONE;
#endif
};

/*
      name : lv_poc_get_keypad_dev
    return : get keypad indev
      date : 2020-04-22
*/
OUT lv_indev_t *
lv_poc_get_keypad_dev(void);

/*
      name : lv_poc_setting_conf_init
    return : bool
      date : 2020-03-30
*/
OUT bool
lv_poc_setting_conf_init(void);

/*
      name : lv_poc_setting_conf_read
    return : point a buff
      date : 2020-03-30
*/
OUT nv_poc_setting_msg_t *
lv_poc_setting_conf_read(void);

/*
      name : lv_poc_setting_conf_write
    return : length of buff
      date : 2020-03-30
*/
OUT int32_t
lv_poc_setting_conf_write(void);

/*
      name : lv_poc_get_time
    return : get local time
      date : 2020-03-30
*/
void
lv_poc_get_time(OUT lv_poc_time_t * time);

/*
      name : watch_set_lcd_status
     param : config lcd state
      date : 2020-03-30
*/
void
poc_set_lcd_status(IN int8_t wakeup);

/*
      name : watch_get_lcd_status
    return : get lcd state
      date : 2020-03-30
*/
OUT bool
poc_get_lcd_status(void);

/*
	  name : nv_setting_config_const
	 param : config nv
	  date : 2020-08-16
*/
void
nv_setting_config_const(OUT nv_poc_setting_msg_t * poc_setting);

/*
      name : poc_battery_get_status
     param : point a battery buff
      date : 2020-08-16
*/
void
poc_battery_get_status(OUT battery_values_t *values);	

#ifdef __cplusplus
}
#endif


#endif //__LV_POC_LIB_H_
