#pragma once

/*
 ============================================================
  SYSTEM PIN SETUP
  Єдине місце, де описані ВСІ піни ESP32-C3
  #include "system/system_pin_setup.h"
 ============================================================
*/
#define PIN_GPIO_2   2
#define PIN_GPIO_3   3
#define PIN_GPIO_4   4
#define PIN_GPIO_5   5
#define PIN_GPIO_6   6
#define PIN_GPIO_7   7
#define PIN_GPIO_8   8
#define PIN_GPIO_9   9
#define PIN_GPIO_10   10
#define PIN_GPIO_20   20
#define PIN_GPIO_21   21

/* =========================
   КНОПКИ
   ========================= */
#define PIN_BTN_POWER_UI      PIN_GPIO_4    // TTP223: on/off дисплею + on/off RGB + перемикання режимів
//#define PIN_BTN_UI            ?    // інша кнопка (поки немає) на перемикання екранів

/* =========================
   RGB LED STRIPS (WS2812)
   ========================= */
#define PIN_RGB_STRIP_1        PIN_GPIO_2
#define PIN_RGB_STRIP_2        PIN_GPIO_3

/* =========================
   DISPLAY (Current -> ST7789, SPI)
   ========================= */
#define PIN_TFT_CS             PIN_GPIO_21  // Chip Select
#define PIN_TFT_DC             PIN_GPIO_5   // Data/Command був на 7 
#define PIN_TFT_RST            PIN_GPIO_20  // Reset
#define PIN_TFT_BL             PIN_GPIO_10  // backlight (якщо керується) був на 6

/* =========================
   SPI BUS (Display ST7789)
   ========================= */
#define PIN_SPI_SCK  PIN_GPIO_9
#define PIN_SPI_MOSI PIN_GPIO_8

/* =========================
   I2C BUS (RTC, Sensors)
   ========================= */
#define PIN_I2C_SDA   PIN_GPIO_6
#define PIN_I2C_SCL   PIN_GPIO_7