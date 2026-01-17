#include "system/system_state.h"
#include "system/system_control.h"

#include "controls/controls.h"

#include "rgb/runtime/rgb_runtime.h"
#include "rgb/strip/rgb_strip.h"

#include "display/display_ui.h"
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

    switch (ev)
    {
        case CTRL_BTN_POWER_HOLD:
            System_TogglePower();
            break;

        case CTRL_BTN_POWER_TAP:
            System_NextMode();
            break;

        default:
            break;
    }

    const SystemState& state = System_Get();

    RGB_Runtime_Update(state);
    DisplayUI_Render(state);

    RGB_strip_Render(
        RGB_Runtime_GetStrip1(),
        RGB_Runtime_GetStrip2(),
        RGB_Runtime_GetBrightness()
    );
}
