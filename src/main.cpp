#include "system/system_state.h"
#include "controls/controls.h"

#include "rgb/runtime/rgb_runtime.h"
#include "rgb/strip/rgb_strip.h"

#include "display/LovyanGFX/ui/display_ui.h"
#include "display/LovyanGFX/display_LovyanGFX.h"

void setup()
{
    System_Init();
    Controls_Init();

    RGB_Runtime_Init();
    RGB_strip_Init();

    Display_Init();
}

void loop()
{
    ControlEvent ev = Controls_Update();

    if (ev == CTRL_TOGGLE_POWER)
        System_TogglePower();
    else if (ev == CTRL_NEXT_MODE)
        System_NextMode();

    const SystemState& state = System_Get();

    RGB_Runtime_Update(state);
    DisplayUI_Render(state);

    RGB_strip_Render(
        RGB_Runtime_GetStrip1(),
        RGB_Runtime_GetStrip2(),
        RGB_Runtime_GetBrightness()
    );
}
