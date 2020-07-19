#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

#include "sys.h"
#include "malloc.h"

#if 0
#define ST7735_SPI	
#else
#define TFT_SPI	
#endif

#ifndef TFT_SPI
#include "lcd.h"
#endif

#ifndef ST7735_SPI /*使用1.44_st7735屏幕*/
#include "st7735_spi.h"
#endif


#endif
