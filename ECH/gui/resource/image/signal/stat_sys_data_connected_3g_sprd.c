#include "lvgl.h"


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

const LV_ATTRIBUTE_MEM_ALIGN uint8_t stat_sys_data_connected_3g_sprd_map[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 
  0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x12, 0x04, 0x03, 0x00, 0x00, 0x00, 0x90, 0x99, 0x52, 
  0x78, 0x00, 0x00, 0x00, 0x03, 0x73, 0x42, 0x49, 0x54, 0x08, 0x08, 0x08, 0xdb, 0xe1, 0x4f, 0xe0, 
  0x00, 0x00, 0x00, 0x18, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x29, 0x2b, 0xc0, 0xc8, 0x00, 0x00, 0x00, 0x08, 0x74, 0x52, 0x4e, 0x53, 0x00, 0x22, 0x33, 0x44, 
  0x66, 0x77, 0x99, 0xff, 0x02, 0x2a, 0xf9, 0x4a, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 
  0x00, 0x00, 0x0a, 0xf0, 0x00, 0x00, 0x0a, 0xf0, 0x01, 0x42, 0xac, 0x34, 0x98, 0x00, 0x00, 0x00, 
  0x1f, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x4d, 0x61, 
  0x63, 0x72, 0x6f, 0x6d, 0x65, 0x64, 0x69, 0x61, 0x20, 0x46, 0x69, 0x72, 0x65, 0x77, 0x6f, 0x72, 
  0x6b, 0x73, 0x20, 0x38, 0xb5, 0x68, 0xd2, 0x78, 0x00, 0x00, 0x00, 0x2b, 0x49, 0x44, 0x41, 0x54, 
  0x08, 0x99, 0x63, 0x60, 0x20, 0x1e, 0xb0, 0x94, 0x97, 0x0b, 0x30, 0x30, 0x98, 0x3b, 0xb0, 0x17, 
  0x30, 0x30, 0x94, 0x82, 0x45, 0x4a, 0x98, 0xcb, 0xc1, 0x6c, 0x46, 0x20, 0x69, 0x1e, 0xc0, 0x56, 
  0x00, 0x56, 0xa3, 0x80, 0x4b, 0x3f, 0x00, 0x26, 0xda, 0x06, 0xb9, 0xc2, 0xe2, 0x9e, 0x06, 0x00, 
  0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82, 
};

lv_img_dsc_t stat_sys_data_connected_3g_sprd = {
  .header.always_zero = 0,
  .header.w = 10,
  .header.h = 18,
  .data_size = 235,
  .header.cf = LV_IMG_CF_RAW_ALPHA,
  .data = stat_sys_data_connected_3g_sprd_map,
};
