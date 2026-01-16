#include "system_state.h"
#include "rgb/modes/rgb_modes.h"

void System_TogglePower()
{
    SystemState& s = System_GetMutable();
    s.powerOn = !s.powerOn;
}

void System_NextMode()
{
    SystemState& s = System_GetMutable();

    uint8_t count = RGB_modes_Count();
    uint8_t i = s.currentMode;

    do
    {
        i = (i + 1) % count;
    }
    while (!RGB_modes_Get(i).selectable);

    s.currentMode = i;
}
