#include "rgb_strip/rgb_modes.h"
#include "rgb_strip/color_palette.h"

/* =========================================================
   БІБЛІОТЕКА РЕЖИМІВ RGB СВІТЛОДІОДІВ
   ЄДИНЕ МІСЦЕ ДЛЯ ВИЗНАЧЕННЯ ВСІХ РЕЖИМІВ
   ========================================================= */

static const RGBMode modes[] = {

    // ========================================================================
    // РЕЖИМ 0: Теплий вечір (Warm Evening)
    // ========================================================================
    // Опис: Спокійний теплий колір, імітує світло заходу сонця.
    // Використовується для створення затишної атмосфери ввечері.
    // Колір: Теплий помаранчевий з відтінком жовтого.
    {
        .selectable = true,          // Режим доступний для вибору користувачем
        .type = MODE_SOLID,          // Тип режиму: суцільний колір
        .brightness = 35,            // Яскравість: 35%
        .solid = {
            COLOR_AMBER,      
            COLOR_AMBER         // Альтернативний колір (якщо потрібно)
        }
    },

    // ========================================================================
    // РЕЖИМ 1: Ніч (Night)
    // ========================================================================
    // Опис: Темний, приглушений колір для нічного освітлення.
    // Створює мінімальне світло, щоб не заважати сну.
    // Колір: Темно-коричневий з відтінком.
    {
        .selectable = true,          // Режим доступний для вибору
        .type = MODE_SOLID,          // Тип режиму: суцільний колір
        .brightness = 18,            // Яскравість: 18% (дуже низька)
        .solid = {
            COLOR_BROWN_DARK,           
            COLOR_BROWN_DARK            // Альтернативний колір (той самий)
        }
    },

    // ========================================================================
    // РЕЖИМ 2: Базовий градієнт (Base Gradient) - СЛУЖБОВИЙ
    // ========================================================================
    // Опис: Градієнт кольорів веселки для двох смуг світлодіодів.
    // Використовується як основа для анімованих режимів.
    // Не доступний для прямого вибору користувачем.
    // Смуга 1: Від червоного до зеленого
    // Смуга 2: Від блакитного до фіолетового
    {
        .selectable = false,         // Режим не доступний для вибору (службовий)
        .type = MODE_PER_PIXEL,      // Тип режиму: окремий колір на кожен піксель
        .brightness = 40,            // Яскравість: 40%
        .perPixel = {
            {   // Смуга 1: Градієнт від червоного до зеленого
                COLOR_RED,
                COLOR_ORANGE_DEEP,
                COLOR_ORANGE_VIVID,     
                COLOR_YELLOW_LIGHT,  
                COLOR_GREEN_LIME,    
                COLOR_GREEN_BRIGHT,   
                COLOR_GREEN_ELECTRIC,  
                COLOR_GREEN             
            },
            {   // Смуга 2: Градієнт від блакитного до фіолетового
                COLOR_CYAN,      
                COLOR_CYAN_BRIGHT,     
                COLOR_BLUE_DEEP,   
                COLOR_BLUE_DARK,    
                COLOR_BLUE,       
                COLOR_PURPLE_DARK,     
                COLOR_PURPLE_DEEP,     
                COLOR_MAGENTA      
            }
        }
    },

    // ========================================================================
    // РЕЖИМ 3: Анімований - Ходячий піксель по градієнту (Walking Pixel over Gradient)
    // ========================================================================
    // Опис: Анімація, де яскравий піксель "ходить" вздовж градієнта.
    // Використовує базовий градієнт (режим 2) як основу.
    // Створює динамічний, рухливий ефект.
    {
        .selectable = true,          // Режим доступний для вибору
        .type = MODE_ANIMATED,       // Тип режиму: анімований
        .brightness = 40,            // Яскравість: 40%
        .animated = {
            .baseModeIndex = 2,     // Використовує режим 2 як основу
            .anim = {
                .type = ANIM_WALKING_PIXEL,     // Тип анімації: ходячий піксель
                .speedMs = 90,                 // Швидкість анімації: 120 мс між кадрами
                .syncStrips = true,             // Синхронізація: так
                .invertSecond = true,           // інвертувати другу смугу
            }
        }
    },

    // ========================================================================
    // РЕЖИМ 4: Кіберпанківський градієнт (Cyberpunk Gradient)
    // ========================================================================
    // Опис: Неонові кольори в стилі кіберпанку.
    // Фіолетові та блакитні відтінки для футуристичного вигляду.
    // Смуга 1: Від фіолетового до рожевого
    // Смуга 2: Від блакитного до синього
    {
        .selectable = true,          // Режим доступний для вибору
        .type = MODE_PER_PIXEL,      // Тип режиму: окремий колір на кожен піксель
        .brightness = 60,            // Яскравість: 60% (вища для неонового ефекту)
        .perPixel = {
            {   // Смуга 1: Градієнт від фіолетового до рожевого
                {180, 0, 255},      // Фіолетовий
                {200, 0, 255},      // Яскраво-фіолетовий
                {220, 0, 255},      // Фіолетово-рожевий
                {255, 0, 220},      // Рожевий
                {255, 0, 180},      // Світло-рожевий
                {255, 0, 140},      // Помаранчево-рожевий
                {255, 0, 100},      // Темно-рожевий
                {255, 0, 60}        // Бордово-рожевий
            },
            {   // Смуга 2: Градієнт від блакитного до синього
                {0, 255, 200},      // Блакитний
                {0, 220, 255},      // Світло-блакитний
                {0, 180, 255},      // Блакитний
                {0, 140, 255},      // Темно-блакитний
                {0, 100, 255},      // Синьо-блакитний
                {0, 60, 255},       // Синій
                {0, 30, 255},       // Темно-синій
                {0, 0, 255}         // Яскраво-синій
            }
        }
    },

    // ========================================================================
    // РЕЖИМ 5: Кіберпанківський гліч (Cyberpunk Glitch) - СЛУЖБОВИЙ
    // ========================================================================
    // Опис: Неонові кольори для гліч-ефекту.
    // Використовується як основа для анімованого гліч-режиму.
    // Не доступний для прямого вибору.
    // Смуга 1: Неоновий маджента
    // Смуга 2: Електричний блакитний
    {
        .selectable = false,         // Режим не доступний для вибору (службовий)
        .type = MODE_PER_PIXEL,      // Тип режиму: окремий колір на кожен піксель
        .brightness = 35,            // Яскравість: 40%
        .perPixel = {
            {   // Смуга 1: Неоновий маджента
                {200, 0, 255},      // Фіолетово-рожевий
                {220, 0, 255},      // Яскраво-фіолетовий
                {255, 0, 220},      // Рожевий
                {255, 0, 180},      // Світло-рожевий
                {255, 0, 140},      // Помаранчево-рожевий
                {255, 0, 100},      // Темно-рожевий
                {255, 0, 60},       // Бордово-рожевий
                {255, 0, 30}        // Темно-бордовий
            },
            {   // Смуга 2: Електричний блакитний
                {0, 255, 220},      // Блакитний
                {0, 255, 180},      // Світло-блакитний
                {0, 255, 140},      // Блакитний
                {0, 255, 100},      // Темно-блакитний
                {0, 255, 60},       // Синьо-блакитний
                {0, 255, 30},       // Темно-синьо-блакитний
                {0, 200, 255},      // Світло-блакитний
                {0, 160, 255}       // Блакитний
            }
        }
    },

    // ========================================================================
    // РЕЖИМ 6: Анімований - Гліч над неоном (Glitch over Neon)
    // ========================================================================
    // Опис: Гліч-анімація над неоновими кольорами.
    // Створює ефект цифрового збою з неоновими спалахами.
    // Використовує кіберпанківський гліч (режим 5) як основу.
    {
        .selectable = true,          // Режим доступний для вибору
        .type = MODE_ANIMATED,       // Тип режиму: анімований
        .brightness = 35,            // Яскравість: 40%
        .animated = {
            .baseModeIndex = 5,     // Використовує режим 5 як основу (неоновий гліч)
            .anim = {
                .type = ANIM_GLITCH,        // Тип анімації: гліч
                .speedMs = 120,              // Швидкість анімації: 90 мс між кадрами
                .syncStrips = false,         // Синхронізація: ні
                .invertSecond = false,      // Додатковий параметр (не використовується)
                .intensity = 10,              // Параметр глічу: м'який гліч (soft glitch)
                .invertEffect = false       // Інверсія ефекту
            }
        }
    },
    // ========================================================================
    // РЕЖИМ 7: Анімований - Бігаюча стрічка дзеркальна (Even-Odd Mirror Running)
    // ========================================================================
    // Опис: Гліч-анімація над градіентом.
    // Створює 2 дзеркальні бігаючі вогники по лінійкам.
    // Використовує режим 2 як основу.
    {
        .selectable = true,          // Режим доступний для вибору
        .type = MODE_ANIMATED,       // Тип режиму: анімований
        .brightness = 40,            // Яскравість: 40%
        .animated = {
            .baseModeIndex = 4,     // Використовує режим 5 як основу (неоновий гліч)
            .anim = {
                .type = ANIM_WALKING_PIXEL,        // Тип анімації: бігаючий піксель
                .speedMs = 130,              // Швидкість анімації: 90 мс між кадрами
                .syncStrips = true,         // Синхронізація: ні
                .invertSecond = true,        // Додатковий параметр (не використовується)
                .intensity = 1,             // Параметр глічу: м'який гліч (soft glitch)
                .invertEffect = true        // Інверсія ефекту
            }
        }
    },
    //РЕЖИМ 8: Warm Ambient (Pulse / Noise base)
    //     Ідеально для
    // ANIM_PULSE
    // ANIM_NOISE (intensity 2–3)
    // нічні режими, invertEffect = true
    {
        .selectable = true,
        .type = MODE_PER_PIXEL,
        .brightness = 30,
        .perPixel = {
            {   // Смуга 1: Теплий бурштин → темний коричневий
                COLOR_WARM_AMBER_BRIGHT,
                COLOR_WARM_AMBER,
                COLOR_WARM_ORANGE_SOFT,
                COLOR_WARM_ORANGE_DIM,
                COLOR_WARM_BROWN_LIGHT,
                COLOR_WARM_BROWN,
                COLOR_WARM_BROWN_DARK,
                COLOR_WARM_BROWN_DEEP
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
    //РЕЖИМ 9: Cyber Neon (Wave / Scanline base)
    //     Ідеально для
    // ANIM_WAVE
    // invertSecond = true
    // швидкі scanline / cyber ефекти
    {
        .selectable = true,
        .type = MODE_PER_PIXEL,
        .brightness = 45,
        .perPixel = {
            {   // Смуга 1: Фіолетовий неон → синій
                COLOR_NEON_PURPLE_BRIGHT,
                COLOR_NEON_PURPLE,
                COLOR_NEON_VIOLET,
                COLOR_NEON_BLUE_VIOLET,
                COLOR_NEON_BLUE,
                COLOR_NEON_BLUE_DEEP,
                COLOR_NEON_BLUE_DIM,
                COLOR_NEON_BLUE_DARK
            },
            {   // Смуга 2: Бірюзово-блакитний неон
                COLOR_CYAN,
                COLOR_CYAN_BRIGHT,
                COLOR_BLUE_DEEP,
                COLOR_BLUE_DARK,
                COLOR_BLUE,
                COLOR_PURPLE_DARK,
                COLOR_PURPLE_DEEP,
                COLOR_MAGENTA
            }
        }
    },
    //РЕЖИМ 10: Forest / Organic (Noise base)
    //     🌿 Ідеально для
    // ANIM_NOISE
    // intensity 2–4
    // повільні, “живі” режими
    {
        .selectable = true,
        .type = MODE_PER_PIXEL,
        .brightness = 35,
        .perPixel = {
            {   // Смуга 1: Лісовий зелений → мох / синьо-зелений
                COLOR_FOREST_GREEN_BRIGHT,
                COLOR_FOREST_GREEN,
                COLOR_FOREST_OLIVE,
                COLOR_FOREST_MOSS,
                COLOR_FOREST_TEAL,
                COLOR_FOREST_TEAL_DIM,
                COLOR_FOREST_BLUEGREEN,
                COLOR_FOREST_BLUEGREEN_DARK
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
    //РЕЖИМ 11: Ice / Glass (Pulse + Wave base)
    // Ідеально для
    // ANIM_PULSE
    // ANIM_WAVE
    // повільні, “скандинавські” сцени
    {
        .selectable = true,
        .type = MODE_PER_PIXEL,
        .brightness = 40,
        .perPixel = {
            {   // Смуга 1: Лід / скло
                COLOR_ICE_WHITE,
                COLOR_ICE_LIGHT,
                COLOR_ICE_SOFT,
                COLOR_ICE_BLUE,
                COLOR_ICE_BLUE_LIGHT,
                COLOR_ICE_BLUE_DIM,
                COLOR_ICE_BLUE_DARK,
                COLOR_ICE_STEEL
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
    // 12 mode
    {
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 40,
        .animated = {
            .baseModeIndex = 8, // будь-який гарний per-pixel base
            .anim = {
                .type = ANIM_PULSE,
                .speedMs = 80,        // швидкість дихання
                .syncStrips = true,
                .invertSecond = false,
                .intensity = 4,       // сила пульсу
                .invertEffect = false
            }
        }
    },
    // 13 mode
    {
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 40,
        .animated = {
            .baseModeIndex = 11, // будь-який гарний per-pixel base
            .anim = {
                .type = ANIM_PULSE,
                .speedMs = 80,        // швидкість дихання
                .syncStrips = true,
                .invertSecond = false,
                .intensity = 4,       // сила пульсу
                .invertEffect = false
            }
        }
    },
    // 13 mode
    {
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 45,
        .animated = {
            .baseModeIndex = 9,   // градієнт
            .anim = {
                .type = ANIM_WAVE,
                .speedMs = 90,
                .syncStrips = true,
                .invertSecond = true,
                .intensity = 6,   // сила хвилі
                .invertEffect = false
            }
        }
    },
    // 14 mode
    {
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 45,
        .animated = {
            .baseModeIndex = 11,   // градієнт
            .anim = {
                .type = ANIM_WAVE,
                .speedMs = 90,
                .syncStrips = true,
                .invertSecond = true,
                .intensity = 6,   // сила хвилі
                .invertEffect = false
            }
        }
    },
    // 14 mode
    {
        .selectable = true,
        .type = MODE_ANIMATED,
        .brightness = 35,
        .animated = {
            .baseModeIndex = 10, // градієнт або теплий base
            .anim = {
                .type = ANIM_NOISE,
                .speedMs = 120,
                .syncStrips = false,
                .invertSecond = false,
                .intensity = 3,   // дуже важливо: low–mid
                .invertEffect = false
            }
        }
    },
    
};

// ========================================================================
// ДОПОМІЖНІ ФУНКЦІЇ ДЛЯ РОБОТИ З РЕЖИМАМИ
// ========================================================================

/**
 * Повертає загальну кількість доступних режимів.
 * Використовується для ітерації по всіх режимах.
 *
 * @return uint8_t Кількість режимів у масиві
 */
uint8_t RGB_modes_Count()
{
    return sizeof(modes) / sizeof(modes[0]);
}

/**
 * Повертає посилання на режим за індексом.
 * Використовується для отримання конфігурації конкретного режиму.
 *
 * @param index Індекс режиму (починається з 0)
 * @return const RGBMode& Посилання на структуру режиму
 */
const RGBMode& RGB_modes_Get(uint8_t index)
{
    return modes[index];
}
