#pragma once
#include "rgb_strip/rgb_types.h"

/* =========================================================
   БАЗОВА ПАЛІТРА КОЛЬОРІВ ДЛЯ RGB СТРІЧКИ
   ========================================================= */

// ===== КОЛЬОРИ: ЧЕРВОНИЙ -> ЗЕЛЕНИЙ (ГРАДІЄНТ ДЛЯ РЕЖИМУ 2|1) =====
constexpr RGB COLOR_RED                     = {255, 0, 0};     //RGB(255, 0, 0)
constexpr RGB COLOR_ORANGE_DEEP             = {255, 80, 0};    //RGB(255, 80, 0)
constexpr RGB COLOR_ORANGE_VIVID            = {255, 160, 0};   //RGB(255, 160, 0)
constexpr RGB COLOR_YELLOW_LIGHT            = {255, 220, 0};   //RGB(255, 220, 0)
constexpr RGB COLOR_GREEN_LIME              = {220, 255, 0};   //RGB(220, 255, 0)
constexpr RGB COLOR_GREEN_BRIGHT            = {160, 255, 0};   //RGB(160, 255, 0)
constexpr RGB COLOR_GREEN_ELECTRIC          = {80, 255, 0};    //RGB(80, 255, 0)
constexpr RGB COLOR_GREEN                   = {0, 255, 0};     //RGB(0, 255, 0)

// ===== КОЛЬОРИ: БІРЮЗОВИЙ -> МАГЕНТА (ГРАДІЄНТ ДЛЯ РЕЖИМУ 2|2) =====
constexpr RGB COLOR_CYAN                    = {0, 255, 255};   //RGB(0, 255, 255)
constexpr RGB COLOR_CYAN_BRIGHT             = {0, 180, 255};   //RGB(0, 180, 255)
constexpr RGB COLOR_BLUE_DEEP               = {0, 120, 255};   //RGB(0, 120, 255)
constexpr RGB COLOR_BLUE_DARK               = {0, 60, 255};    //RGB(0, 60, 255)
constexpr RGB COLOR_BLUE                    = {0, 0, 255};     //RGB(0, 0, 255)
constexpr RGB COLOR_PURPLE_DARK             = {60, 0, 255};    //RGB(60, 0, 255)
constexpr RGB COLOR_PURPLE_DEEP             = {120, 0, 255};   //RGB(120, 0, 255)
constexpr RGB COLOR_MAGENTA                 = {180, 0, 255};   //RGB(180, 0, 255)

// ===== КОЛЬОРИ: ТЕПЛИЙ БУРШТИН -> ТЕМНИЙ КОРИЧНЕВИЙ (WARM AMBIENT) =====
constexpr RGB COLOR_WARM_AMBER_BRIGHT       = {255, 140,  60}; // RGB(255, 140, 60)
constexpr RGB COLOR_WARM_AMBER              = {255, 130,  55}; // RGB(255, 130, 55)
constexpr RGB COLOR_WARM_ORANGE_SOFT        = {245, 120,  50}; // RGB(245, 120, 50)
constexpr RGB COLOR_WARM_ORANGE_DIM         = {235, 110,  45}; // RGB(235, 110, 45)
constexpr RGB COLOR_WARM_BROWN_LIGHT        = {225, 100,  40}; // RGB(225, 100, 40)
constexpr RGB COLOR_WARM_BROWN              = {215,  90,  35}; // RGB(215, 90, 35)
constexpr RGB COLOR_WARM_BROWN_DARK          = {205,  80,  30}; // RGB(205, 80, 30)
constexpr RGB COLOR_WARM_BROWN_DEEP          = {195,  70,  25}; // RGB(195, 70, 25)

// ===== КОЛЬОРИ: ФІОЛЕТОВИЙ НЕОН -> СИНІЙ НЕОН (CYBER NEON) =====
constexpr RGB COLOR_NEON_PURPLE_BRIGHT      = {120,   0, 255}; // RGB(120, 0, 255)
constexpr RGB COLOR_NEON_PURPLE              = {100,   0, 255}; // RGB(100, 0, 255)
constexpr RGB COLOR_NEON_VIOLET              = { 80,   0, 255}; // RGB(80, 0, 255)
constexpr RGB COLOR_NEON_BLUE_VIOLET         = { 60,   0, 255}; // RGB(60, 0, 255)
constexpr RGB COLOR_NEON_BLUE                = { 40,   0, 255}; // RGB(40, 0, 255)
constexpr RGB COLOR_NEON_BLUE_DEEP           = { 20,   0, 255}; // RGB(20, 0, 255)
constexpr RGB COLOR_NEON_BLUE_DIM            = { 10,   0, 200}; // RGB(10, 0, 200)
constexpr RGB COLOR_NEON_BLUE_DARK           = {  0,   0, 160}; // RGB(0, 0, 160)

// ===== КОЛЬОРИ: ЛІСОВИЙ ЗЕЛЕНИЙ -> МОХ / СИНЬО-ЗЕЛЕНИЙ (FOREST ORGANIC) =====
constexpr RGB COLOR_FOREST_GREEN_BRIGHT     = { 20, 120,  40}; // RGB(20, 120, 40)
constexpr RGB COLOR_FOREST_GREEN             = { 25, 110,  45}; // RGB(25, 110, 45)
constexpr RGB COLOR_FOREST_OLIVE             = { 30, 100,  50}; // RGB(30, 100, 50)
constexpr RGB COLOR_FOREST_MOSS              = { 35,  90,  55}; // RGB(35, 90, 55)
constexpr RGB COLOR_FOREST_TEAL              = { 40,  80,  60}; // RGB(40, 80, 60)
constexpr RGB COLOR_FOREST_TEAL_DIM          = { 45,  70,  65}; // RGB(45, 70, 65)
constexpr RGB COLOR_FOREST_BLUEGREEN         = { 50,  60,  70}; // RGB(50, 60, 70)
constexpr RGB COLOR_FOREST_BLUEGREEN_DARK    = { 55,  50,  75}; // RGB(55, 50, 75)

// ===== КОЛЬОРИ: ЛІД / СКЛО (ICE / GLASS GRADIENT) =====
constexpr RGB COLOR_ICE_WHITE               = {180, 240, 255}; // RGB(180, 240, 255)
constexpr RGB COLOR_ICE_LIGHT               = {160, 230, 255}; // RGB(160, 230, 255)
constexpr RGB COLOR_ICE_SOFT                = {140, 220, 255}; // RGB(140, 220, 255)
constexpr RGB COLOR_ICE_BLUE                = {120, 210, 255}; // RGB(120, 210, 255)
constexpr RGB COLOR_ICE_BLUE_LIGHT          = {100, 200, 255}; // RGB(100, 200, 255)
constexpr RGB COLOR_ICE_BLUE_DIM            = { 80, 190, 245}; // RGB(80, 190, 245)
constexpr RGB COLOR_ICE_BLUE_DARK           = { 60, 180, 235}; // RGB(60, 180, 235)
constexpr RGB COLOR_ICE_STEEL               = { 40, 170, 225}; // RGB(40, 170, 225)

// ===== ТЕПЛІ КОЛЬОРИ =====
constexpr RGB COLOR_AMBER                   = {255, 126, 0};   //RGB(255, 126, 0)   // Для теплого вечора (режим 0)
constexpr RGB COLOR_BROWN_DARK              = {60, 40, 25};    //RGB(60, 40, 25)    // Для ночі (режим 1)

// ===== УТИЛІТАРНІ КОЛЬОРИ =====
constexpr RGB COLOR_BLACK                   = {0, 0, 0};       //RGB(0, 0, 0)
constexpr RGB COLOR_WHITE                   = {255, 255, 255}; //RGB(255, 255, 255)

