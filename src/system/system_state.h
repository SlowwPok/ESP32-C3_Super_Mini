#pragma once
#include <stdint.h>

/*
  SystemState — ЄДИНЕ МІСЦЕ,
  де зберігається стан пристрою
*/

struct SystemState
{
    bool powerOn;          // true = лента + дисплей увімкнені
    uint8_t currentMode;  // номер режиму RGB
};

// ініціалізація (один раз в setup)
void System_Init();

// доступ ТІЛЬКИ для читання
const SystemState& System_Get();

// дії над станом
void System_TogglePower();
void System_NextMode();
