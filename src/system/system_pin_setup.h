#pragma once

/*
 ============================================================
  SYSTEM PIN SETUP
  Єдине місце, де описані ВСІ піни ESP32-C3
  #include "system/system_pin_setup.h"
 ============================================================
*/

/* =========================
   КНОПКИ
   ========================= */
#define PIN_BTN_POWER_UI      4    // TTP223: on/off дисплею + on/off RGB + перемикання режимів
//#define PIN_BTN_UI            ?    // інша кнопка (поки немає) на перемикання екранів

/* =========================
   RGB LED STRIPS (WS2812)
   ========================= */
#define PIN_RGB_STRIP_1        2
#define PIN_RGB_STRIP_2        3

/* =========================
   DISPLAY (Current -> ST7789, SPI)
   ========================= */
#define PIN_TFT_CS             21  // Chip Select
#define PIN_TFT_DC             7   // Data/Command
#define PIN_TFT_RST            20  // Reset
#define PIN_TFT_BL             5   // backlight (якщо керується)
// SPI
#define PIN_SPI_SCK            10   // display - SDA
#define PIN_SPI_MOSI           6   // display - SCL

/* =========================
   I2C BUS (RTC, Modules, Conveter)
   ========================= */
#define PIN_I2C_SDA            8
#define PIN_I2C_SCL            9
