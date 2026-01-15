#pragma once
#include "rgb_strip/rgb_types.h"
#include "rgb_runtime/animation_engine.h"
#include "rgb_strip/rgb_mode.h"

/* =========================================================
   БІБЛІОТЕКА РЕЖИМІВ RGB СВІТЛОДІОДІВ
   ========================================================= */

#define RGB_MODES_MAX 17 // Загальна кількість режимів освітлення (включаючи службові режими)

/**
 * Повертає загальну кількість доступних режимів освітлення.
 * Використовується для ітерації по всіх режимах або перевірки меж індексу.
 * 
 * Приклад використання:
 * @code
 *   for (uint8_t i = 0; i < RGB_modes_Count(); i++) {
 *       const RGBMode& mode = RGB_modes_Get(i);
 *       if (mode.selectable) { ... }
 *   }
 * @endcode
 *
 * @return uint8_t Кількість режимів у бібліотеці (включаючи службові режими)
 */
uint8_t RGB_modes_Count();

/**
 * Повертає посилання на режим освітлення за його індексом.
 * Використовується для отримання конфігурації конкретного режиму.
 * 
 * Режиму мають три типи:
 * - MODE_SOLID: один колір на всю смугу (поле .solid)
 * - MODE_PER_PIXEL: окремий колір на кожен піксель (поле .perPixel)
 * - MODE_ANIMATED: анімація поверх базового режиму (поле .animated)
 *
 * Приклад використання:
 * @code
 *   const RGBMode& currentMode = RGB_modes_Get(modeIndex);
 *   if (currentMode.type == MODE_ANIMATED) {
 *       uint8_t baseIndex = currentMode.animated.baseModeIndex;
 *       const RGBMode& base = RGB_modes_Get(baseIndex);
 *   }
 * @endcode
 *
 * @param index Індекс режиму (від 0 до RGB_modes_Count() - 1)
 * @return const RGBMode& Посилання на структуру режиму (не копія, не переміщується)
 * 
 * @note Повертає посилання, тому даних залишаються в пам'яті PROGMEM
 * @warning Індекс не перевіряється! Переконайтеся, що він в діапазоні RGB_modes_Count()
 */
const RGBMode& RGB_modes_Get(uint8_t index);