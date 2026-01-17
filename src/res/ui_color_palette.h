#pragma once
#include <stdint.h>

/*
    UI COLOR PALETTE
    ----------------
    • ТІЛЬКИ для дисплея
    • ТІЛЬКИ RGB565
    • НІЯКИХ COLOR_RED / COLOR_GREEN
    • НІЯКОГО RGB
*/

// ===== BASE UI COLORS =====
constexpr uint16_t UI_COLOR_BG        = 0x0000; // чорний фон
constexpr uint16_t UI_COLOR_TEXT      = 0xFFFF; // основний текст
constexpr uint16_t UI_COLOR_DIM_TEXT  = 0x8410; // приглушений текст

// ===== DEBUG / LAYOUT =====
constexpr uint16_t UI_COLOR_BOUNDARY  = 0xF81F; // рожево-червоні межі

// ===== OPTIONAL STATUS COLORS =====
constexpr uint16_t UI_COLOR_OK        = 0x07E0; // зелений (OK)
constexpr uint16_t UI_COLOR_WARNING   = 0xFFE0; // жовтий (warning)
constexpr uint16_t UI_COLOR_ERROR     = 0xF800; // червоний (error)
