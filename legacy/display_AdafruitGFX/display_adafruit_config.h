#pragma once
#include <Arduino.h>

// ===== ПАРАМЕТРИ ДИСПЛЕЯ =====
#define DISP_WIDTH   320  // Ширина дисплея в пікселях
#define DISP_HEIGHT  170  // Висота дисплея в пікселях

// ===== ОРІЄНТАЦІЯ =====
#define DISP_ROTATION 3   // Обертання дисплея (3 = landscape, пінси праворуч)

// ===== ПІНИ (ЗАМІНИТЬ НА СВОЇ РЕАЛЬНІ) =====
#define TFT_CS   21      // Chip Select
#define TFT_DC   7       // Data/Command
#define TFT_RST  20      // Reset

// ===== SPI ПІНИ =====
#define TFT_SCK   9      // SPI Clock
#define TFT_MOSI  8      // SPI MOSI

// ===== КОЛЬОРИ (ФОРМАТ RGB565) =====
#define COLOR_BLACK   0x0000 //RGB(0, 0, 0)
#define COLOR_WHITE   0xFFFF //RGB(255, 255, 255)
#define COLOR_RED     0xF800 //RGB(255, 0, 0)
#define COLOR_GREEN   0x07E0 //RGB(0, 255, 0)
#define COLOR_BLUE    0x001F //RGB(0, 0, 255)
#define COLOR_CYAN    0x07FF //RGB(0, 255, 255)
#define COLOR_MAGENTA 0xF81F //RGB(255, 0, 255)
#define COLOR_YELLOW  0xFFE0 //RGB(255, 255, 0)