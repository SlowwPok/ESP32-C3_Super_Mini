#include "system_state.h"

static SystemState state;

void System_Init()
{
    state.powerOn = true;
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