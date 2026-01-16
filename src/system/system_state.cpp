#include "system/system_state.h"
#include "rgb/modes/rgb_modes.h"

static SystemState state;

void System_Init()
{
    state.powerOn = true;
    state.currentMode = 0;
}

const SystemState& System_Get()
{
    return state;
}

void System_TogglePower()
{
    state.powerOn = !state.powerOn;
}

void System_NextMode()
{
    uint8_t count = RGB_modes_Count();
    uint8_t i = state.currentMode;

    do
    {
        i = (i + 1) % count;
    }
    while (!RGB_modes_Get(i).selectable);

    state.currentMode = i;
}
