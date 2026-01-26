#include "system_state.h"
#include "system_pin_setup.h"
#include <Wire.h>

static SystemState state;

void System_Init()
{
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    state.powerOn   = true;
    state.displayOn = true;
    state.currentMode = 0;
    state.activeScreen = SCREEN_SENSOR_INFO;
    state.uptimeSec = 0;
}

const SystemState& System_Get()
{
    return state;
}

SystemState& System_GetMutable()
{
    return state;
}