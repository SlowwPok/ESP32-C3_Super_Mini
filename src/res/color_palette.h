#pragma once
#include "rgb/strip/rgb_types.h"

// ONLY RGB888 COLORS FORMAT
// ONLY RGB888 COLORS FORMAT
// ONLY RGB888 COLORS FORMAT

/* =========================================================
   БАЗОВА ПАЛІТРА КОЛЬОРІВ ДЛЯ RGB СТРІЧКИ
   ========================================================= */

// ===== КОЛЬОРИ: ЧЕРВОНИЙ -> ЗЕЛЕНИЙ (ГРАДІЄНТ ДЛЯ РЕЖИМУ 2|1) =====
// Градієнт веселки від червоного до зеленого, часто використовується в базових ефектах
constexpr RGB COLOR_RED                     = {255, 0, 0};     // RGB(255, 0, 0) - Яскравий червоний
constexpr RGB COLOR_ORANGE_DEEP             = {255, 80, 0};    // RGB(255, 80, 0) - Темний помаранчевий
constexpr RGB COLOR_ORANGE_VIVID            = {255, 160, 0};   // RGB(255, 160, 0) - Яскравий помаранчевий
constexpr RGB COLOR_YELLOW_LIGHT            = {255, 220, 0};   // RGB(255, 220, 0) - Світлий жовтий
constexpr RGB COLOR_GREEN_LIME              = {220, 255, 0};   // RGB(220, 255, 0) - Лайм зелений
constexpr RGB COLOR_GREEN_BRIGHT            = {160, 255, 0};   // RGB(160, 255, 0) - Яскравий зелений
constexpr RGB COLOR_GREEN_ELECTRIC          = {80, 255, 0};    // RGB(80, 255, 0) - Електричний зелений
constexpr RGB COLOR_GREEN                   = {0, 255, 0};     // RGB(0, 255, 0) - Чистий зелений

// ===== КОЛЬОРИ: БІРЮЗОВИЙ -> МАГЕНТА (ГРАДІЄНТ ДЛЯ РЕЖИМУ 2|2) =====
// Градієнт веселки від синього до фіолетового, доповнює першу смугу
constexpr RGB COLOR_CYAN                    = {0, 255, 255};   // RGB(0, 255, 255) - Яскравий блакитний
constexpr RGB COLOR_CYAN_BRIGHT             = {0, 180, 255};   // RGB(0, 180, 255) - Світлий блакитний
constexpr RGB COLOR_BLUE_DEEP               = {0, 120, 255};   // RGB(0, 120, 255) - Темний блакитний
constexpr RGB COLOR_BLUE_DARK               = {0, 60, 255};    // RGB(0, 60, 255) - Темно-синій
constexpr RGB COLOR_BLUE                    = {0, 0, 255};     // RGB(0, 0, 255) - Чистий синій
constexpr RGB COLOR_PURPLE_DARK             = {60, 0, 255};    // RGB(60, 0, 255) - Темний фіолетовий
constexpr RGB COLOR_PURPLE_DEEP             = {120, 0, 255};   // RGB(120, 0, 255) - Глибокий фіолетовий
constexpr RGB COLOR_MAGENTA                 = {180, 0, 255};   // RGB(180, 0, 255) - Яскравий маджента

// ===== КОЛЬОРИ: ТЕПЛИЙ БУРШТИН -> ТЕМНИЙ КОРИЧНЕВИЙ (WARM AMBIENT) =====
// Теплі кольори для затишної атмосфери (режим 0 - Теплий вечір)
constexpr RGB COLOR_WARM_AMBER_BRIGHT       = {255, 140,  60}; // RGB(255, 140, 60) - Яскравий бурштин
constexpr RGB COLOR_WARM_AMBER              = {255, 130,  55}; // RGB(255, 130, 55) - Бурштин
constexpr RGB COLOR_WARM_ORANGE_SOFT        = {245, 120,  50}; // RGB(245, 120, 50) - М'який помаранчевий
constexpr RGB COLOR_WARM_ORANGE_DIM         = {235, 110,  45}; // RGB(235, 110, 45) - Приглушений помаранчевий
constexpr RGB COLOR_WARM_BROWN_LIGHT        = {225, 100,  40}; // RGB(225, 100, 40) - Світлий коричневий
constexpr RGB COLOR_WARM_BROWN              = {215,  90,  35}; // RGB(215, 90, 35) - Коричневий
constexpr RGB COLOR_WARM_BROWN_DARK         = {205,  80,  30}; // RGB(205, 80, 30) - Темний коричневий
constexpr RGB COLOR_WARM_BROWN_DEEP         = {195,  70,  25}; // RGB(195, 70, 25) - Глибокий коричневий

// ===== КОЛЬОРИ: ФІОЛЕТОВИЙ НЕОН -> СИНІЙ НЕОН (CYBER NEON) =====
// Яскраві неонові кольори для кіберпанківських режимів (режим 4, 6)
constexpr RGB COLOR_NEON_PURPLE_BRIGHT      = {120,   0, 255}; // RGB(120, 0, 255) - Яскравий неон фіолетовий
constexpr RGB COLOR_NEON_PURPLE             = {100,   0, 255}; // RGB(100, 0, 255) - Неон фіолетовий
constexpr RGB COLOR_NEON_VIOLET             = { 80,   0, 255}; // RGB(80, 0, 255) - Неон фіолетовий (темний)
constexpr RGB COLOR_NEON_BLUE_VIOLET        = { 60,   0, 255}; // RGB(60, 0, 255) - Неон синьо-фіолетовий
constexpr RGB COLOR_NEON_BLUE               = { 40,   0, 255}; // RGB(40, 0, 255) - Неон синій
constexpr RGB COLOR_NEON_BLUE_DEEP          = { 20,   0, 255}; // RGB(20, 0, 255) - Неон синій (глибокий)
constexpr RGB COLOR_NEON_BLUE_DIM           = { 10,   0, 200}; // RGB(10, 0, 200) - Неон синій (приглушений)
constexpr RGB COLOR_NEON_BLUE_DARK          = {  0,   0, 160}; // RGB(0, 0, 160) - Неон синій (темний)

// ===== КОЛЬОРИ: ЛІСОВИЙ ЗЕЛЕНИЙ -> МОХ / СИНЬО-ЗЕЛЕНИЙ (FOREST ORGANIC) =====
// Природні лісові кольори для органічних, спокійних ефектів
constexpr RGB COLOR_FOREST_GREEN_BRIGHT     = { 20, 120,  40}; // RGB(20, 120, 40) - Яскравий лісовий зелений
constexpr RGB COLOR_FOREST_GREEN            = { 25, 110,  45}; // RGB(25, 110, 45) - Лісовий зелений
constexpr RGB COLOR_FOREST_OLIVE            = { 30, 100,  50}; // RGB(30, 100, 50) - Оливковий зелений
constexpr RGB COLOR_FOREST_MOSS             = { 35,  90,  55}; // RGB(35, 90, 55) - Мох
constexpr RGB COLOR_FOREST_TEAL             = { 40,  80,  60}; // RGB(40, 80, 60) - Гірчиця
constexpr RGB COLOR_FOREST_TEAL_DIM         = { 45,  70,  65}; // RGB(45, 70, 65) - Гірчиця (приглушена)
constexpr RGB COLOR_FOREST_BLUEGREEN        = { 50,  60,  70}; // RGB(50, 60, 70) - Синьо-зелений
constexpr RGB COLOR_FOREST_BLUEGREEN_DARK   = { 55,  50,  75}; // RGB(55, 50, 75) - Синьо-зелений (темний)

// ===== КОЛЬОРИ: ЛІД / СКЛО (ICE / GLASS GRADIENT) =====
// Холодні світлі кольори, що імітують скло або лід
constexpr RGB COLOR_ICE_WHITE               = {180, 240, 255}; // RGB(180, 240, 255) - Білий лід
constexpr RGB COLOR_ICE_LIGHT               = {160, 230, 255}; // RGB(160, 230, 255) - Світлий лід
constexpr RGB COLOR_ICE_SOFT                = {140, 220, 255}; // RGB(140, 220, 255) - М'який лід
constexpr RGB COLOR_ICE_BLUE                = {120, 210, 255}; // RGB(120, 210, 255) - Синій лід
constexpr RGB COLOR_ICE_BLUE_LIGHT          = {100, 200, 255}; // RGB(100, 200, 255) - Світлий синій лід
constexpr RGB COLOR_ICE_BLUE_DIM            = { 80, 190, 245}; // RGB(80, 190, 245) - Приглушений синій лід
constexpr RGB COLOR_ICE_BLUE_DARK           = { 60, 180, 235}; // RGB(60, 180, 235) - Темний синій лід
constexpr RGB COLOR_ICE_STEEL               = { 40, 170, 225}; // RGB(40, 170, 225) - Сталевий лід

// ===== ТЕПЛІ КОЛЬОРИ (БАЗОВІ) =====
// Основні теплі кольори для простих режимів
constexpr RGB COLOR_AMBER                   = {255, 126, 0};   // RGB(255, 126, 0) - Теплий вечір (режим 0)
constexpr RGB COLOR_BROWN_DARK              = {60, 40, 25};    // RGB(60, 40, 25) - Ніч (режим 1)

// ===== УТИЛІТАРНІ КОЛЬОРИ =====
// Допоміжні кольори для спеціальних цілей
constexpr RGB COLOR_BLACK                   = {0, 0, 0};       // RGB(0, 0, 0)
constexpr RGB COLOR_WHITE                   = {255, 255, 255}; // RGB(255, 255, 255)

