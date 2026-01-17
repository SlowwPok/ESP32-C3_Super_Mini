// path: src/system/system_state.h
#pragma once
#include <stdint.h>

/*
  SystemState — ЄДИНЕ МІСЦЕ,
  де зберігається стан пристрою
*/

enum ScreenId
{
    SCREEN_RGB = 0,   // поточний екран RGB
    SCREEN_SYSTEM,    // системна інфа (uptime, датчики і т.д.)
    SCREEN_COUNT
};

struct SystemState
{
    bool powerOn;
    uint8_t currentMode;

    ScreenId activeScreen;
    uint32_t uptimeSec;
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
