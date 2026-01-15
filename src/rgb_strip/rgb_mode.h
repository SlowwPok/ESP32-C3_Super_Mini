#pragma once

#include <stdint.h>
#include "rgb_strip/rgb_types.h"
#include "rgb_runtime/animation_engine.h"
#include "rgb_strip/rgb_config.h"

enum RGBModeType
{
    MODE_SOLID,
    MODE_PER_PIXEL,
    MODE_ANIMATED
};

struct RGBMode
{
    const char* name;
    
    bool selectable;
    RGBModeType type;
    uint8_t brightness;

    union
    {
        struct
        {
            RGB strip1;
            RGB strip2;
        } solid;

        struct
        {
            RGB strip1[RGB_STRIP_LENGTH];
            RGB strip2[RGB_STRIP_LENGTH];
        } perPixel;

        struct
        {
            uint8_t baseModeIndex;
            AnimationParams anim;
        } animated;
    };
};