#include <Arduino.h>


#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_debug.h"

// #include "display/AdafruitGFX/display_adafruit.h"              // Бібліотека в папці _disabled
// #include "display/AdafruitGFX/display_adafruit_debug.h"        // Бібліотека в папці _disabled

#include "controls/controls.h"
#include "rgb_strip/rgb_strip.h"


void setup()
{
    Display_Init();
    Display_DrawDebugPattern();

    // Display_DebugPattern(); Альтернатива для AdafruitGFX (якщо використовуються ці бібліотеки)

    Controls_Init();
    RGB_strip_Init();
}

void loop()
{
    // Оновлення стану RGB смуг: обробка сенсора, оновлення рендеринга
    RGB_strip_Update();
}
