#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

#include "appstart.h"
#include "malloc.h"

/*********************************start**************************************/

#if !(OPEN)				/*开放---则使用该功能*/
#define ST7735_SPI	
#endif

#if !(CLOSE)
#define TFT_SPI	
#endif

#if !(CLOSE)
#define OLED_IIC	
#endif

#if !(CLOSE)
#define ST7789_SPI	
#endif

/**********************************end****************************************/

/**********************************start**************************************/
#ifndef TFT_SPI /*使用TFT屏幕*/
#include "tft_lcd.h"
#endif

#ifndef ST7735_SPI /*使用1.44_st7735屏幕*/
#include "st7735_spi.h"
#endif

#ifndef OLED_IIC /*使用iic_oled屏幕*/
#include "oled_iic.h"
#endif

#ifndef ST7789_SPI /*使用1.13_st7789屏幕*/
#include "st7789_spi.h"

/**********************************end****************************************/

/*extern img*/
/*rec img*/
extern const unsigned char st7789_Image_qq[3200];
extern const unsigned char gImage_st7789_rec_msg1[7200];
extern const unsigned char gImage_st7789_rec_msg2[7200];
extern const unsigned char gImage_st7789_rec_msg3[7200];
extern const unsigned char gImage_st7789_rec_msg4[7200];
/*sleep img*/
extern const unsigned char gImage_st7789_sleep_msg1[7200];
extern const unsigned char gImage_st7789_sleep_msg2[7200];

#endif


#endif
