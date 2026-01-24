#pragma once
#include "system/system_pin_setup.h"

// ===== ПІН-КОНФІГУРАЦІЯ (SPI ДЛЯ ST7789) =====
#define PIN_SCLK    PIN_SPI_SCK    // SPI Clock (SCLK)
#define PIN_MOSI    PIN_SPI_MOSI    // SPI MOSI (SI)
#define PIN_DC      PIN_TFT_DC     // Data/Command
#define PIN_CS      PIN_TFT_CS     // Chip Select
#define PIN_RST     PIN_TFT_RST    // Reset
#define PIN_BL      PIN_TFT_BL     // Backlight 

// ===== ПАРАМЕТРИ ДИСПЛЕЯ ST7789 =====
#define DISP_MEMORY_WIDTH   170  // Ширина пам'яті дисплея
#define DISP_MEMORY_HEIGHT  320  // Висота пам'яті дисплея
#define DISP_PANEL_WIDTH    170  // Ширина панелі дисплея
#define DISP_PANEL_HEIGHT   320  // Висота панелі дисплея
#define DISP_OFFSET_X       35   // Зсув по X
#define DISP_OFFSET_Y       0    // Зсув по Y
#define DISP_ROTATION       3    // Орієнтація: landscape, штифти з правого боку
#define DISP_INVERT         true // Інверсія кольорів
#define DISP_RGB_ORDER      false // Порядок кольорів: BGR