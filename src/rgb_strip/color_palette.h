#pragma once
#include "rgb_strip/rgb_types.h"

/* =========================================================
   БАЗОВА ПАЛІТРА КОЛЬОРІВ
   ========================================================= */

// --- Colors --- RED -> GREEN                              //in mode 2|1-strip - per pixel gradient
constexpr RGB COLOR_RED                     = {255, 0, 0};     //RGB(255, 0, 0)
constexpr RGB COLOR_ORANGE_DEEP             = {255, 80, 0};    //RGB(255, 80, 0)
constexpr RGB COLOR_ORANGE_VIVID            = {255, 160, 0};   //RGB(255, 160, 0)
constexpr RGB COLOR_YELLOW_LIGHT            = {255, 220, 0};   //RGB(255, 220, 0)
constexpr RGB COLOR_GREEN_LIME              = {220, 255, 0};   //RGB(220, 255, 0)
constexpr RGB COLOR_GREEN_BRIGHT            = {160, 255, 0};   //RGB(160, 255, 0)
constexpr RGB COLOR_GREEN_ELECTRIC          = {80, 255, 0};    //RGB(80, 255, 0)
constexpr RGB COLOR_GREEN                   = {0, 255, 0};     //RGB(0, 255, 0)

// --- Colors --- CYAN -> MAGENTA                           //in mode 2|2-strip - per pixel gradient
constexpr RGB COLOR_CYAN                    = {0, 255, 255};   //RGB(0, 255, 255)
constexpr RGB COLOR_CYAN_BRIGHT             = {0, 180, 255};   //RGB(0, 180, 255)
constexpr RGB COLOR_BLUE_DEEP               = {0, 120, 255};   //RGB(0, 120, 255)
constexpr RGB COLOR_BLUE_DARK               = {0, 60, 255};    //RGB(0, 60, 255)
constexpr RGB COLOR_BLUE                    = {0, 0, 255};     //RGB(0, 0, 255)
constexpr RGB COLOR_PURPLE_DARK             = {60, 0, 255};    //RGB(60, 0, 255)
constexpr RGB COLOR_PURPLE_DEEP             = {120, 0, 255};   //RGB(120, 0, 255)
constexpr RGB COLOR_MAGENTA                 = {180, 0, 255};   //RGB(180, 0, 255)

// ---- Warm ----
constexpr RGB COLOR_AMBER                   = {255, 126, 0};   //RGB(255, 126, 0)   in mode 0 - warm evening
constexpr RGB COLOR_BROWN_DARK              = {60, 40, 25};    //RGB(60, 40, 25)    in mode 1 - night

// ---- Utility ----
constexpr RGB COLOR_BLACK                   = {0, 0, 0};       //RGB(0, 0, 0)
constexpr RGB COLOR_WHITE                   = {255, 255, 255}; //RGB(255, 255, 255)

