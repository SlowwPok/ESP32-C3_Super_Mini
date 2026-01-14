#pragma once

// ===== ПІН-КОНФІГУРАЦІЯ (SPI ДЛЯ ST7789) =====
#define PIN_SCLK    9    // SPI Clock (SCLK)
#define PIN_MOSI    8    // SPI MOSI (SI)
#define PIN_DC      7    // Data/Command
#define PIN_CS      21   // Chip Select
#define PIN_RST     10   // Reset

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

// ===== КОЛЬОРИ (ФОРМАТ RGB565) =====
#define COLOR_BLACK    0x0000 //RGB(0, 0, 0)
#define COLOR_WHITE    0xFFFF //RGB(255, 255, 255)
#define COLOR_RED      0xF800 //RGB(255, 0, 0)
#define COLOR_GREEN    0x07E0 //RGB(0, 255, 0)
#define COLOR_BLUE     0x001F //RGB(0, 0, 255)
#define COLOR_YELLOW   0xFFE0 //RGB(255, 255, 0)
#define COLOR_MAGENTA  0xF81F //RGB(255, 0, 255)
#define COLOR_GRAY     0x8410 //RGB(128, 64, 128)  // Приблизний сірий
#define COLOR_CYAN     0x07FF //RGB(0, 255, 255)