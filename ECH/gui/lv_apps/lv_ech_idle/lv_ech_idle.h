#ifndef __LV_IDLE_PORT_H
#define __LV_IDLE_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "lv_ech.h"

extern lv_ech_activity_t *activity_idle;
void lv_ech_idle_set_user_name(const char * name_str);
void lv_ech_idle_set_group_name(const char * name_str);
char * lv_ech_idle_get_user_name(void);
char * lv_ech_idle_get_group_name(void);


extern lv_obj_t * idle_title_label;
extern lv_obj_t * idle_user_label;
extern lv_obj_t * idle_user_name_label;
extern lv_obj_t * idle_group_label;
extern lv_obj_t * idle_group_name_label;

lv_ech_activity_t * lv_ech_create_idle(void);

void lv_ech_idle_set_page2(lv_ech_idle_page2_display_t msg_type, char * content[], int csize);


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif //__INCLUDE_IDLE_H
