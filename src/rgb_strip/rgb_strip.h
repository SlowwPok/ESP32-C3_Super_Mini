#pragma once
#include <Arduino.h>
#include "rgb_strip/rgb_types.h"

void RGB_strip_Init();
void RGB_strip_Render(
    const RGB* strip1,
    const RGB* strip2,
    uint8_t brightness
);