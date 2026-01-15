#include "rgb_strip/rgb_modes.h"
#include "rgb_strip/color_palette.h"

/* =========================================================
   БІБЛІОТЕКА РЕЖИМІВ RGB СВІТЛОДІОДІВ
   Усі режими (solid, per-pixel, animated) у одному місці
   ========================================================= */

static const RGBMode modes[] = {

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 0: Теплий вечір (Warm Evening)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Warm Evening",
        .selectable = true,          // Доступний користувачеві (кнопка TAP)
        .type = MODE_SOLID,          // Одноколірний режим
        .brightness = 35,            // Яскравість: 35% (затишно для очей)
        .solid = {
            COLOR_AMBER,             // RGB(255, 126, 0)
            COLOR_AMBER
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 1: Ніч (Night)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Night",
        .selectable = true,          // Доступний користувачеві
        .type = MODE_SOLID,          // Одноколірний режим
        .brightness = 18,            // Яскравість: 18% (мінімальна)
        .solid = {
            COLOR_BROWN_DARK,        // RGB(60, 40, 25)
            COLOR_BROWN_DARK
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 2: Базовий веселковий градієнт (Base Rainbow) - СЛУЖБОВИЙ
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Base Rainbow",
        .selectable = false,         // Тільки для анімацій (режим 3)
        .type = MODE_PER_PIXEL,      // Окремий колір на піксель
        .brightness = 40,            // Яскравість: 40%
        .perPixel = {
            {   // Смуга 1: Червоний → Зелений
                COLOR_RED,               // RGB(255, 0, 0)
                COLOR_ORANGE_DEEP,       // RGB(255, 80, 0)
                COLOR_ORANGE_VIVID,      // RGB(255, 160, 0)
                COLOR_YELLOW_LIGHT,      // RGB(255, 220, 0)
                COLOR_GREEN_LIME,        // RGB(220, 255, 0)
                COLOR_GREEN_BRIGHT,      // RGB(160, 255, 0)
                COLOR_GREEN_ELECTRIC,    // RGB(80, 255, 0)
                COLOR_GREEN              // RGB(0, 255, 0)
            },
            {   // Смуга 2: Бірюзовий → Маджента
                COLOR_CYAN,              // RGB(0, 255, 255)
                COLOR_CYAN_BRIGHT,       // RGB(0, 180, 255)
                COLOR_BLUE_DEEP,         // RGB(0, 120, 255)
                COLOR_BLUE_DARK,         // RGB(0, 60, 255)
                COLOR_BLUE,              // RGB(0, 0, 255)
                COLOR_PURPLE_DARK,       // RGB(60, 0, 255)
                COLOR_PURPLE_DEEP,       // RGB(120, 0, 255)
                COLOR_MAGENTA            // RGB(180, 0, 255)
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 3: Ходячий піксель по веселці (Walking Pixel)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Walking Pixel",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 40,            // Яскравість: 40%
        .animated = {
            .baseModeIndex = 2,      // База: режим 2 (веселка)
            .anim = {
                .type = ANIM_WALKING_PIXEL,    // Один піксель ходить
                .speedMs = 90,                 // Інтервал: 90 мс (9 FPS)
                .syncStrips = true,            // Обидві смуги синхронізовані
                .invertSecond = true,          // Друга смуга: дзеркальний напрямок
                .intensity = 8,                // Видимість хвоста: 8/10
                .invertEffect = false
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 4: Неоновий кіберпанк (Cyberpunk Neon Gradient)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Cyberpunk Neon",
        .selectable = true,
        .type = MODE_PER_PIXEL,
        .brightness = 60,            // Яскравість: 60% (висока для неону)
        .perPixel = {
            {   // Смуга 1: Неон фіолет → синій
                COLOR_NEON_PURPLE_BRIGHT,   // RGB(120, 0, 255)
                COLOR_NEON_PURPLE,          // RGB(100, 0, 255)
                COLOR_NEON_VIOLET,          // RGB(80, 0, 255)
                COLOR_NEON_BLUE_VIOLET,     // RGB(60, 0, 255)
                COLOR_NEON_BLUE,            // RGB(40, 0, 255)
                COLOR_NEON_BLUE_DEEP,       // RGB(20, 0, 255)
                COLOR_NEON_BLUE_DIM,        // RGB(10, 0, 200)
                COLOR_NEON_BLUE_DARK        // RGB(0, 0, 160)
            },
            {   // Смуга 2: Неон блакитний
                COLOR_ICE_WHITE,            // RGB(180, 240, 255)
                COLOR_ICE_LIGHT,            // RGB(160, 230, 255)
                COLOR_ICE_SOFT,             // RGB(140, 220, 255)
                COLOR_ICE_BLUE,             // RGB(120, 210, 255)
                COLOR_ICE_BLUE_LIGHT,       // RGB(100, 200, 255)
                COLOR_ICE_BLUE_DIM,         // RGB(80, 190, 245)
                COLOR_ICE_BLUE_DARK,        // RGB(60, 180, 235)
                COLOR_ICE_STEEL             // RGB(40, 170, 225)
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 5: Неон + Гліч база (Neon Glitch Base) - СЛУЖБОВИЙ
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Neon Base",
        .selectable = false,         // Тільки для анімацій (режим 6)
        .type = MODE_PER_PIXEL,
        .brightness = 35,            // Яскравість: 35%
        .perPixel = {
            {   // Смуга 1: Неон фіолет
                COLOR_NEON_PURPLE_BRIGHT,   // RGB(120, 0, 255)
                COLOR_NEON_PURPLE,          // RGB(100, 0, 255)
                COLOR_NEON_VIOLET,          // RGB(80, 0, 255)
                COLOR_NEON_BLUE_VIOLET,     // RGB(60, 0, 255)
                COLOR_NEON_BLUE,            // RGB(40, 0, 255)
                COLOR_NEON_BLUE_DEEP,       // RGB(20, 0, 255)
                COLOR_NEON_BLUE_DIM,        // RGB(10, 0, 200)
                COLOR_NEON_BLUE_DARK        // RGB(0, 0, 160)
            },
            {   // Смуга 2: Неон блакитний
                COLOR_ICE_WHITE,            // RGB(180, 240, 255)
                COLOR_ICE_LIGHT,            // RGB(160, 230, 255)
                COLOR_ICE_SOFT,             // RGB(140, 220, 255)
                COLOR_ICE_BLUE,             // RGB(120, 210, 255)
                COLOR_ICE_BLUE_LIGHT,       // RGB(100, 200, 255)
                COLOR_ICE_BLUE_DIM,         // RGB(80, 190, 245)
                COLOR_ICE_BLUE_DARK,        // RGB(60, 180, 235)
                COLOR_ICE_STEEL             // RGB(40, 170, 225)
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 6: Гліч над неоном (Glitch over Neon)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Glitch over Neon",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 35,            // Яскравість: 35%
        .animated = {
            .baseModeIndex = 5,      // База: режим 5 (неонова палітра)
            .anim = {
                .type = ANIM_GLITCH,       // Випадкові спалахи
                .speedMs = 120,            // Інтервал: 120 мс (8 FPS)
                .syncStrips = false,       // Кожна смуга: незалежні спалахи
                .invertSecond = false,
                .intensity = 10,           // Інтенсивність: максимальна
                .invertEffect = false
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 7: Дзеркальна стрічка (Mirror Running)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Mirror Running",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 40,            // Яскравість: 40%
        .animated = {
            .baseModeIndex = 4,      // База: режим 4 (неон)
            .anim = {
                .type = ANIM_WALKING_PIXEL,    // Ходячий піксель
                .speedMs = 130,                // Інтервал: 130 мс (7 FPS)
                .syncStrips = true,            // Синхронізовані
                .invertSecond = true,          // Дзеркальний напрямок
                .intensity = 1,                // Мінімальний хвіст
                .invertEffect = true           // Інвертований режим
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 8: Теплий бурштин (Warm Ambient) - СЛУЖБОВИЙ
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Warm Ambient",
        .selectable = false,         // База для PULSE/NOISE анімацій
        .type = MODE_PER_PIXEL,
        .brightness = 30,            // Яскравість: 30%
        .perPixel = {
            {   // Смуга 1: Бурштин → коричневий
                COLOR_WARM_AMBER_BRIGHT,   // RGB(255, 140, 60)
                COLOR_WARM_AMBER,          // RGB(255, 130, 55)
                COLOR_WARM_ORANGE_SOFT,    // RGB(245, 120, 50)
                COLOR_WARM_ORANGE_DIM,     // RGB(235, 110, 45)
                COLOR_WARM_BROWN_LIGHT,    // RGB(225, 100, 40)
                COLOR_WARM_BROWN,          // RGB(215, 90, 35)
                COLOR_WARM_BROWN_DARK,     // RGB(205, 80, 30)
                COLOR_WARM_BROWN_DEEP      // RGB(195, 70, 25)
            },
            {   // Смуга 2: Дзеркально
                COLOR_WARM_BROWN_DEEP,
                COLOR_WARM_BROWN_DARK,
                COLOR_WARM_BROWN,
                COLOR_WARM_BROWN_LIGHT,
                COLOR_WARM_ORANGE_DIM,
                COLOR_WARM_ORANGE_SOFT,
                COLOR_WARM_AMBER,
                COLOR_WARM_AMBER_BRIGHT
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 9: Неон WAVE (Cyber Wave Base) - СЛУЖБОВИЙ
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Cyber Wave",
        .selectable = false,         // База для WAVE анімацій
        .type = MODE_PER_PIXEL,
        .brightness = 45,            // Яскравість: 45%
        .perPixel = {
            {   // Смуга 1: Неон фіолет → синій
                COLOR_NEON_PURPLE_BRIGHT,   // RGB(120, 0, 255)
                COLOR_NEON_PURPLE,          // RGB(100, 0, 255)
                COLOR_NEON_VIOLET,          // RGB(80, 0, 255)
                COLOR_NEON_BLUE_VIOLET,     // RGB(60, 0, 255)
                COLOR_NEON_BLUE,            // RGB(40, 0, 255)
                COLOR_NEON_BLUE_DEEP,       // RGB(20, 0, 255)
                COLOR_NEON_BLUE_DIM,        // RGB(10, 0, 200)
                COLOR_NEON_BLUE_DARK        // RGB(0, 0, 160)
            },
            {   // Смуга 2: Бірюза → магента
                COLOR_CYAN,                 // RGB(0, 255, 255)
                COLOR_CYAN_BRIGHT,          // RGB(0, 180, 255)
                COLOR_BLUE_DEEP,            // RGB(0, 120, 255)
                COLOR_BLUE_DARK,            // RGB(0, 60, 255)
                COLOR_BLUE,                 // RGB(0, 0, 255)
                COLOR_PURPLE_DARK,          // RGB(60, 0, 255)
                COLOR_PURPLE_DEEP,          // RGB(120, 0, 255)
                COLOR_MAGENTA               // RGB(180, 0, 255)
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 10: Лісовий зелений (Forest Organic) - СЛУЖБОВИЙ
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Forest Organic",
        .selectable = false,         // База для NOISE анімацій
        .type = MODE_PER_PIXEL,
        .brightness = 35,            // Яскравість: 35%
        .perPixel = {
            {   // Смуга 1: Зелень → синьозелень
                COLOR_FOREST_GREEN_BRIGHT,  // RGB(20, 120, 40)
                COLOR_FOREST_GREEN,         // RGB(25, 110, 45)
                COLOR_FOREST_OLIVE,         // RGB(30, 100, 50)
                COLOR_FOREST_MOSS,          // RGB(35, 90, 55)
                COLOR_FOREST_TEAL,          // RGB(40, 80, 60)
                COLOR_FOREST_TEAL_DIM,      // RGB(45, 70, 65)
                COLOR_FOREST_BLUEGREEN,     // RGB(50, 60, 70)
                COLOR_FOREST_BLUEGREEN_DARK // RGB(55, 50, 75)
            },
            {   // Смуга 2: Дзеркально
                COLOR_FOREST_BLUEGREEN_DARK,
                COLOR_FOREST_BLUEGREEN,
                COLOR_FOREST_TEAL_DIM,
                COLOR_FOREST_TEAL,
                COLOR_FOREST_MOSS,
                COLOR_FOREST_OLIVE,
                COLOR_FOREST_GREEN,
                COLOR_FOREST_GREEN_BRIGHT
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 11: Лід / Скло (Ice Glass) - СЛУЖБОВИЙ
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Ice Glass",
        .selectable = false,         // База для PULSE/WAVE анімацій
        .type = MODE_PER_PIXEL,
        .brightness = 40,            // Яскравість: 40%
        .perPixel = {
            {   // Смуга 1: Лід від світлого до темного
                COLOR_ICE_WHITE,            // RGB(180, 240, 255)
                COLOR_ICE_LIGHT,            // RGB(160, 230, 255)
                COLOR_ICE_SOFT,             // RGB(140, 220, 255)
                COLOR_ICE_BLUE,             // RGB(120, 210, 255)
                COLOR_ICE_BLUE_LIGHT,       // RGB(100, 200, 255)
                COLOR_ICE_BLUE_DIM,         // RGB(80, 190, 245)
                COLOR_ICE_BLUE_DARK,        // RGB(60, 180, 235)
                COLOR_ICE_STEEL             // RGB(40, 170, 225)
            },
            {   // Смуга 2: Дзеркально
                COLOR_ICE_STEEL,
                COLOR_ICE_BLUE_DARK,
                COLOR_ICE_BLUE_DIM,
                COLOR_ICE_BLUE_LIGHT,
                COLOR_ICE_BLUE,
                COLOR_ICE_SOFT,
                COLOR_ICE_LIGHT,
                COLOR_ICE_WHITE
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 12: Пульс (Warm Pulse)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Warm Pulse",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 35,            // Яскравість: 40%
        .animated = {
            .baseModeIndex = 8,      // База: режим 8 (теплий)
            .anim = {
                .type = ANIM_PULSE,        // Пульсуючий ефект
                .speedMs = 80,             // Інтервал: 80 мс (дихання)
                .syncStrips = true,        // Синхронізовані
                .invertSecond = false,
                .intensity = 3,            // Сила пульсу: 3/10 (м'яка)
                .invertEffect = false
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 13: Пульс льоду (Ice Pulse)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Ice Pulse",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 28,            // Яскравість: 40%
        .animated = {
            .baseModeIndex = 11,     // База: режим 11 (лід)
            .anim = {
                .type = ANIM_PULSE,        // Пульсуючий ефект
                .speedMs = 80,             // Інтервал: 80 мс
                .syncStrips = true,        // Синхронізовані
                .invertSecond = false,
                .intensity = 3,            // Сила пульсу: 3/10
                .invertEffect = false
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 14: Хвиля неону (Neon Wave)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Neon Wave",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 45,            // Яскравість: 45%
        .animated = {
            .baseModeIndex = 9,      // База: режим 9 (неон WAVE)
            .anim = {
                .type = ANIM_WAVE,         // Хвильовий ефект
                .speedMs = 70,             // Інтервал: 70 мс (14 FPS)
                .syncStrips = true,        // Синхронізовані
                .invertSecond = true,      // Дзеркальний напрямок
                .intensity = 5,            // Сила хвилі: 6/10
                .invertEffect = false
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 15: Хвиля льоду (Ice Wave)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Ice Wave",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 40,            // Яскравість: 45%
        .animated = {
            .baseModeIndex = 11,     // База: режим 11 (лід)
            .anim = {
                .type = ANIM_WAVE,         // Хвильовий ефект
                .speedMs = 90,             // Інтервал: 90 мс
                .syncStrips = true,        // Синхронізовані
                .invertSecond = true,      // Дзеркальний напрямок
                .intensity = 6,            // Сила хвилі: 6/10
                .invertEffect = false
            }
        }
    },

    // ═════════════════════════════════════════════════════════════════════
    // РЕЖИМ 16: Шум (Organic Noise)
    // ═════════════════════════════════════════════════════════════════════
    {
        .name = "Organic Noise",
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 30,            // Яскравість: 35%
        .animated = {
            .baseModeIndex = 10,     // База: режим 10 (лісовий)
            .anim = {
                .type = ANIM_NOISE,        // Органічний шум
                .speedMs = 120,            // Інтервал: 120 мс (8 FPS)
                .syncStrips = false,       // Кожна смуга: незалежний шум
                .invertSecond = false,
                .intensity = 2,            // Інтенсивність: 2/10 (дуже м'яка)
                .invertEffect = false
            }
        }
    },
    
};

uint8_t RGB_modes_Count()
{
    return sizeof(modes) / sizeof(modes[0]);
}

const RGBMode& RGB_modes_Get(uint8_t index)
{
    return modes[index];
}
