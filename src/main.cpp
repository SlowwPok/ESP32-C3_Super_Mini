#include <Arduino.h>

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_debug.h"
// #include "display/AdafruitGFX/display_adafruit.h"              //бібліотека в _disabled
// #include "display/AdafruitGFX/display_adafruit_debug.h"        //бібліотека в _disabled

#include "rgb_strip/rgb_strip.h"


void setup()
{
  Display_Init();                 // Initialize the display (using AdafruitGFX same as LovyanGFX)  
  Display_DrawDebugPattern();  // LovyanGFX
  // Display_DebugPattern();      // AdafruitGFX -> бібліотека в _disabled

  // Initialize the RGB strip
  RGB_strip_Init();
}

void loop()
{
    RGB_strip_Update();
}
