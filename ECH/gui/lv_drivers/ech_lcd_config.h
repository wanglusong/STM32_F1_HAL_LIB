#ifndef _ECH_LCD_CONFIG_H
#define _ECH_LCD_CONFIG_H

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
#include "ech_tft.h"
#endif

#ifndef ST7735_SPI /*使用1.44_st7735屏幕*/
#include "ech_st7735_spi.h"
#endif

#ifndef OLED_IIC /*使用iic_oled屏幕*/
#include "ech_oled_iic.h"
#endif

#ifndef ST7789_SPI /*使用1.13_st7789屏幕*/
#include "ech_st7789_spi.h"
#endif


#endif
