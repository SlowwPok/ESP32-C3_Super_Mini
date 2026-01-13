#pragma once
#include <stdint.h>

// ===== ORIENTATION =====
// 0 = vertical (pins up)
// 1 = horizontal right
// 2 = upside down
// 3 = horizontal left (рекомендовано)
#define DISPLAY_ROTATION 3

// ===== DISPLAY SIZE =====
#define DISPLAY_WIDTH   170
#define DISPLAY_HEIGHT  320

// ===== DEBUG =====
#define GRID_STEP 10
#define TEST_SQUARE_SIZE 20

// ===== UI COLORS (RGB565) =====
#define UI_BLACK    0x0000
#define UI_WHITE    0xFFFF
#define UI_RED      0xF800
#define UI_GREEN    0x07E0
#define UI_BLUE     0x001F
#define UI_YELLOW   0xFFE0
#define UI_MAGENTA  0xF81F
#define UI_DARKGREY 0x7BEF
