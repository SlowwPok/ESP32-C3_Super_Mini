#pragma once
#include "rgb_strip/rgb_strip.h"
#include "rgb_strip/animation_engine.h"

/**
 * Повертає загальну кількість доступних режимів освітлення.
 * Використовується для ітерації по всіх режимах або перевірки меж.
 *
 * @return uint8_t Кількість режимів у бібліотеці
 */
uint8_t RGB_modes_Count();

/**
 * Повертає посилання на режим освітлення за його індексом.
 * Використовується для отримання конфігурації конкретного режиму.
 *
 * @param index Індекс режиму (від 0 до RGB_modes_Count() - 1)
 * @return const RGBMode& Посилання на структуру режиму (не копія)
 */
const RGBMode& RGB_modes_Get(uint8_t index);