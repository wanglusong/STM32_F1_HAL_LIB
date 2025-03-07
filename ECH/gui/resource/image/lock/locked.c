#include "lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

const LV_ATTRIBUTE_MEM_ALIGN uint8_t locked_map[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 
  0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x0f, 0x04, 0x03, 0x00, 0x00, 0x00, 0xcd, 0x0d, 0x58, 
  0x44, 0x00, 0x00, 0x00, 0x03, 0x73, 0x42, 0x49, 0x54, 0x08, 0x08, 0x08, 0xdb, 0xe1, 0x4f, 0xe0, 
  0x00, 0x00, 0x00, 0x30, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff, 0xff, 0xff, 0x83, 0x00, 0xff, 0x83, 
  0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 
  0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 
  0x83, 0x00, 0xff, 0x83, 0x00, 0xff, 0x83, 0x00, 0xc1, 0xc0, 0x62, 0x53, 0x00, 0x00, 0x00, 0x10, 
  0x74, 0x52, 0x4e, 0x53, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 
  0xcc, 0xdd, 0xee, 0xff, 0x76, 0x95, 0x01, 0x15, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 
  0x00, 0x00, 0x25, 0x80, 0x00, 0x00, 0x25, 0x80, 0x01, 0x6c, 0x55, 0x08, 0x07, 0x00, 0x00, 0x00, 
  0x1f, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x4d, 0x61, 
  0x63, 0x72, 0x6f, 0x6d, 0x65, 0x64, 0x69, 0x61, 0x20, 0x46, 0x69, 0x72, 0x65, 0x77, 0x6f, 0x72, 
  0x6b, 0x73, 0x20, 0x38, 0xb5, 0x68, 0xd2, 0x78, 0x00, 0x00, 0x00, 0x58, 0x49, 0x44, 0x41, 0x54, 
  0x08, 0x99, 0x63, 0x60, 0x60, 0xa8, 0xfb, 0xe3, 0xc0, 0x00, 0x04, 0x5c, 0xff, 0xce, 0x7f, 0x07, 
  0xd1, 0xf3, 0x27, 0x32, 0x9d, 0x0f, 0x00, 0xd2, 0xef, 0x18, 0x18, 0xec, 0x17, 0x00, 0xe9, 0x3b, 
  0x0c, 0x0c, 0x72, 0x40, 0x5a, 0x6d, 0x66, 0x79, 0x79, 0x65, 0xab, 0x00, 0xc3, 0xfb, 0xff, 0x20, 
  0xd0, 0xc0, 0xf0, 0xff, 0xff, 0xbf, 0xf3, 0xff, 0xff, 0x4f, 0x00, 0xd2, 0xdf, 0xb8, 0x20, 0xf4, 
  0x17, 0x0e, 0x54, 0xfa, 0xbb, 0x34, 0x84, 0xfe, 0xff, 0x1e, 0x44, 0xc3, 0xf4, 0xe5, 0xbe, 0x03, 
  0x82, 0x37, 0x0a, 0x00, 0x75, 0x3b, 0x42, 0x0e, 0x59, 0x25, 0x63, 0x1f, 0x00, 0x00, 0x00, 0x00, 
  0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82, 
};

lv_img_dsc_t locked = {
  .header.always_zero = 0,
  .header.w = 13,
  .header.h = 15,
  .data_size = 312,
  .header.cf = LV_IMG_CF_RAW_ALPHA,
  .data = locked_map,
};
