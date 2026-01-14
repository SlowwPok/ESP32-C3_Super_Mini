#include <Arduino.h>
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_debug.h"
#include "rgb_strip/rgb_strip.h"


void setup()
{
  Display_Init();
  Display_DrawDebugPattern();


  // Initialize the RGB strip
  RGB_strip_Init();
}

void loop()
{
    RGB_strip_Update();
}
