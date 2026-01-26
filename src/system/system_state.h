// path: src/system/system_state.h
#pragma once
#include <stdint.h>
#include "system/time/system_datetime.h"
#include "bme280/bme280_types.h"

/*
  SystemState — ЄДИНЕ МІСЦЕ,
  де зберігається стан пристрою
*/

enum ScreenId
{
    SCREEN_SENSOR_INFO = 0,
    SCREEN_RGB,
    SCREEN_SYSTEM,
    SCREEN_COUNT
};

struct SystemState
{
    bool powerOn;
    uint8_t currentMode;

    ScreenId activeScreen;
    uint32_t uptimeSec;

    SystemDateTime time;

    BME280Data bme;
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

