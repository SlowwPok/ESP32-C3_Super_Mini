#include <Arduino.h>

#include "system/system_state.h"
#include "controls/controls.h"
#include "display/LovyanGFX/ui/display_ui.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_debug.h"

// #include "display/AdafruitGFX/display_adafruit.h"              // Бібліотека в папці _disabled
// #include "display/AdafruitGFX/display_adafruit_debug.h"        // Бібліотека в папці _disabled

#include "rgb_strip/rgb_strip.h"


void setup()
{
    System_Init();
    Controls_Init();

    Display_Init();
    Display_DrawDebugPattern();

    // Display_DebugPattern(); Альтернатива для AdafruitGFX (якщо використовуються ці бібліотеки)

    RGB_strip_Init();
}

void loop()
{
    ControlEvent ev = Controls_Update();

    if (ev == CTRL_TOGGLE_POWER)
        System_TogglePower();
    else if (ev == CTRL_NEXT_MODE)
        System_NextMode();

    const SystemState& state = System_Get();

    DisplayUI_Render(state);
    RGB_strip_Update();
}
