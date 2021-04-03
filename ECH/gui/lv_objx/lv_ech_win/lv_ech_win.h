
#ifndef __INCLUDE_LV_WIN_PORT_
#define __INCLUDE_LV_WIN_PORT_

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
#define LV_ech_WIN_TITLE_HEIGHT_RATIO  5

/*************************************************
*
*                  ENUM
*
*************************************************/


/*************************************************
*
*                  TYPEDEF
*
*************************************************/
/*Data of list*/
typedef struct
{
    lv_obj_t * title;
    lv_obj_t * header;
    lv_area_t display_area;
    void * display_obj;
} lv_ech_win_t;

typedef void *(* lv_ech_win_create_func_t)(lv_obj_t * parent, lv_area_t display_area);

/*************************************************
*
*                  STRUCT
*
*************************************************/
/*******************
*     NAME:
*   AUTHOR:   lugj
* DESCRIPT:
*     DATE:   2019-11-25
********************/


/*************************************************
*
*                  EXTERN
*
*************************************************/


/*************************************************
*
*                  STATIC
*
*************************************************/


/*************************************************
*
*                  PUBLIC DEFINE
*
*************************************************/
/*******************
*     NAME:   lv_ech_win_create
*   AUTHOR:   lugj
* DESCRIPT:   ´´½¨ech´°¿Ú
*     DATE:   2019-11-25
********************/
lv_ech_win_t * lv_ech_win_create(lv_obj_t * parent, const char * title, lv_ech_win_create_func_t func);


#ifdef __cplusplus
}
#endif


#endif //__INCLUDE_LV_INTER_PHONE_WIN__

