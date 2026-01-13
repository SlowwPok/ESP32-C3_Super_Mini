#include <Arduino.h>
#include "rgb_strip.h"
#include "display_LovyanGFX.h"


void setup()
{
  Display_Init();
  Display_DrawGrid();


  // Initialize the RGB strip
  RGB_strip_Init();
}

void loop()
{
    RGB_strip_Update();
}
