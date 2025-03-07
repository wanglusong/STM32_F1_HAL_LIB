#include "lvgl.h"


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

const LV_ATTRIBUTE_MEM_ALIGN uint8_t font_one_60px_map[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 
  0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x3c, 0x02, 0x03, 0x00, 0x00, 0x00, 0x05, 0xd1, 0x42, 
  0x76, 0x00, 0x00, 0x00, 0x03, 0x73, 0x42, 0x49, 0x54, 0x08, 0x08, 0x08, 0xdb, 0xe1, 0x4f, 0xe0, 
  0x00, 0x00, 0x00, 0x0c, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 
  0x3f, 0x00, 0x00, 0x00, 0xc6, 0xd3, 0x5f, 0x6f, 0x00, 0x00, 0x00, 0x04, 0x74, 0x52, 0x4e, 0x53, 
  0x00, 0xff, 0xff, 0xff, 0xb3, 0x2d, 0x40, 0x88, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 
  0x00, 0x00, 0x0a, 0xf0, 0x00, 0x00, 0x0a, 0xf0, 0x01, 0x42, 0xac, 0x34, 0x98, 0x00, 0x00, 0x00, 
  0x1f, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x4d, 0x61, 
  0x63, 0x72, 0x6f, 0x6d, 0x65, 0x64, 0x69, 0x61, 0x20, 0x46, 0x69, 0x72, 0x65, 0x77, 0x6f, 0x72, 
  0x6b, 0x73, 0x20, 0x38, 0xb5, 0x68, 0xd2, 0x78, 0x00, 0x00, 0x00, 0x2e, 0x49, 0x44, 0x41, 0x54, 
  0x18, 0x95, 0x63, 0x60, 0xc0, 0x00, 0xcc, 0xff, 0x21, 0x34, 0x37, 0x94, 0x96, 0x87, 0xd2, 0xfb, 
  0xff, 0x43, 0x64, 0xff, 0xa3, 0xd0, 0x0c, 0x0c, 0xf6, 0xa3, 0x34, 0x5d, 0xe8, 0xfa, 0xff, 0x0d, 
  0x0c, 0x90, 0x70, 0xff, 0xff, 0x07, 0x37, 0x8d, 0x06, 0x00, 0x02, 0x6d, 0x58, 0xb9, 0x11, 0x23, 
  0xdb, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82, 
};

lv_img_dsc_t font_one_60px = {
  .header.always_zero = 0,
  .header.w = 26,
  .header.h = 60,
  .data_size = 222,
  .header.cf = LV_IMG_CF_RAW_ALPHA,
  .data = font_one_60px_map,
};
