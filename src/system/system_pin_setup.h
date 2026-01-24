#pragma once

/*
 ============================================================
  SYSTEM PIN SETUP
  Єдине місце, де описані ВСІ піни ESP32-C3
  #include "system/system_pin_setup.h"
 ============================================================
*/

#define PIN_GPIO_8   8
#define PIN_GPIO_9   9

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
#define PIN_TFT_BL             6   // backlight (якщо керується)

/* =========================
   SPI BUS (Display ST7789)
   ========================= */
#define PIN_SPI_SCK  PIN_GPIO_9
#define PIN_SPI_MOSI PIN_GPIO_8

/* =========================
   I2C BUS (RTC, Sensors)
   ========================= */
#define PIN_I2C_SDA   10
#define PIN_I2C_SCL   5

/* =========================
   ONE-WIRE
   ========================= */
// #define PIN_DS18B20             2

/* =========================
   ANALOG
   ========================= */
// #define PIN_MQ135_ANALOG        0   // перевір, який ADC пін на C3

/* =========================
   RESERVED / FUTURE
   ========================= */
// #define PIN_...