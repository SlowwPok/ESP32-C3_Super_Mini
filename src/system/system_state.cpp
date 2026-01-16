#include "system_state.h"

SystemState state;

void System_Init()
{
    state.powerOn = true;
    state.currentMode = 0;
    state.activeScreen = 0;
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