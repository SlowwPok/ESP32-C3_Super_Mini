#pragma once
#include <stdint.h>

/*
  SystemState — ЄДИНЕ МІСЦЕ,
  де зберігається стан пристрою
*/

struct SystemState
{
    bool powerOn;
    uint8_t currentMode;

    uint8_t activeScreen;   // для UI
    uint32_t uptimeSec;     // для RTC / system info
};

// ініціалізація (один раз в setup)
void System_Init();

// доступ ТІЛЬКИ для читання
const SystemState& System_Get();

// ⚠️ INTERNAL — mutable доступ ТІЛЬКИ для system_control
SystemState& System_GetMutable();

// дії над станом
void System_TogglePower();
void System_NextMode();
