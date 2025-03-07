#include "lvgl.h"


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

const LV_ATTRIBUTE_MEM_ALIGN uint8_t ic_menu_friend_map[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 
  0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0e, 0x04, 0x03, 0x00, 0x00, 0x00, 0x02, 0xa4, 0x5b, 
  0xdc, 0x00, 0x00, 0x00, 0x03, 0x73, 0x42, 0x49, 0x54, 0x08, 0x08, 0x08, 0xdb, 0xe1, 0x4f, 0xe0, 
  0x00, 0x00, 0x00, 0x24, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff, 0xff, 0x00, 0xb7, 0xee, 0x00, 0xb7, 
  0xee, 0x00, 0xb7, 0xee, 0x00, 0xb7, 0xee, 0x00, 0xb7, 0xee, 0x00, 0xb7, 0xee, 0x00, 0xb7, 0xee, 
  0x00, 0xb7, 0xee, 0x00, 0xb7, 0xee, 0x00, 0xb7, 0xee, 0x00, 0xb7, 0xee, 0x87, 0xf9, 0x7f, 0xae, 
  0x00, 0x00, 0x00, 0x0c, 0x74, 0x52, 0x4e, 0x53, 0x00, 0x11, 0x22, 0x44, 0x77, 0x88, 0xaa, 0xbb, 
  0xcc, 0xdd, 0xee, 0xff, 0xce, 0xf6, 0x73, 0xe8, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 
  0x00, 0x00, 0x0b, 0x12, 0x00, 0x00, 0x0b, 0x12, 0x01, 0xd2, 0xdd, 0x7e, 0xfc, 0x00, 0x00, 0x00, 
  0x1f, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x4d, 0x61, 
  0x63, 0x72, 0x6f, 0x6d, 0x65, 0x64, 0x69, 0x61, 0x20, 0x46, 0x69, 0x72, 0x65, 0x77, 0x6f, 0x72, 
  0x6b, 0x73, 0x20, 0x38, 0xb5, 0x68, 0xd2, 0x78, 0x00, 0x00, 0x00, 0x5b, 0x49, 0x44, 0x41, 0x54, 
  0x08, 0x99, 0x55, 0x8a, 0xa1, 0x0d, 0x80, 0x30, 0x14, 0x05, 0x1f, 0xa9, 0x21, 0xa9, 0xc1, 0x30, 
  0x05, 0xa6, 0x9e, 0x11, 0x50, 0xcc, 0xd1, 0x09, 0x70, 0xec, 0xd1, 0x01, 0xb0, 0x0d, 0x90, 0x26, 
  0xcd, 0x2d, 0x47, 0xfb, 0x1d, 0x67, 0xde, 0xe5, 0xf2, 0xa4, 0x21, 0x96, 0x49, 0x9d, 0x11, 0x4e, 
  0x93, 0x05, 0x6e, 0x93, 0x15, 0x9e, 0x7f, 0xe9, 0x1f, 0x4f, 0x96, 0x1c, 0x04, 0x2b, 0x8a, 0x45, 
  0xb2, 0x92, 0xaa, 0x15, 0x97, 0xa0, 0x06, 0x9f, 0xb5, 0xd1, 0x78, 0x5b, 0xc1, 0x68, 0x92, 0xfa, 
  0xd6, 0x26, 0xf3, 0x01, 0xd7, 0x2e, 0x7d, 0x30, 0x56, 0x26, 0xac, 0x26, 0x23, 0x14, 0xa3, 0x00, 
  0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82, 
};

lv_img_dsc_t ic_menu_friend = {
  .header.always_zero = 0,
  .header.w = 15,
  .header.h = 14,
  .data_size = 299,
  .header.cf = LV_IMG_CF_RAW_ALPHA,
  .data = ic_menu_friend_map,
};
