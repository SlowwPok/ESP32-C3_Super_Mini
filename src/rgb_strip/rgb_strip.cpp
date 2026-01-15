#include "rgb_strip/rgb_strip.h"
#include <Adafruit_NeoPixel.h>
#include "rgb_strip/rgb_config.h"



static Adafruit_NeoPixel strip1(RGB_STRIP_LENGTH, LED_1_PIN, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip2(RGB_STRIP_LENGTH, LED_2_PIN, NEO_GRB + NEO_KHZ800);

void RGB_strip_Init()
{
    strip1.begin();
    strip2.begin();
    strip1.show();
    strip2.show();
}

void RGB_strip_Render(const RGB* s1, const RGB* s2)
{
    for (int i = 0; i < RGB_STRIP_LENGTH; i++)
    {
        strip1.setPixelColor(i, strip1.Color(s1[i].r, s1[i].g, s1[i].b));
        strip2.setPixelColor(i, strip2.Color(s2[i].r, s2[i].g, s2[i].b));
    }

    strip1.show();
    strip2.show();
}