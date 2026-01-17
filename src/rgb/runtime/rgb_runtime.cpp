#include "rgb_runtime.h"

#include "rgb/modes/rgb_modes.h"
#include "rgb/runtime/animation_engine.h"
#include "rgb/strip/rgb_config.h"

#include <string.h>

// ===== ВНУТРІШНІ БУФЕРИ =====

static RGB runtimeStrip1[RGB_STRIP_LENGTH];
static RGB runtimeStrip2[RGB_STRIP_LENGTH];

// ===== META =====

static uint8_t activeMode = 0;
static uint8_t baseMode   = 0;
static uint8_t brightness = 0;
static uint16_t animSpeedMs = 0;
static uint8_t  animIntensity = 0;
static bool    animated   = false;

// ===== ANIMATION STATE =====

static AnimationState animState1;
static AnimationState animState2;

const char* RGB_Runtime_GetActiveModeName()
{
    if (activeMode < RGB_modes_Count())
        return RGB_modes_Get(activeMode).name;
    return "UNKNOWN";
}

const char* RGB_Runtime_GetBaseModeName()
{
    if (baseMode < RGB_modes_Count())
        return RGB_modes_Get(baseMode).name;
    return "UNKNOWN";
}

// static inline RGB applyBrightness(const RGB& c, uint8_t brightness)
// {
//     RGB out;
//     out.r = (uint16_t)c.r * brightness / 255;
//     out.g = (uint16_t)c.g * brightness / 255;
//     out.b = (uint16_t)c.b * brightness / 255;
//     return out;
// }

void RGB_Runtime_Init()
{
    memset(runtimeStrip1, 0, sizeof(runtimeStrip1));
    memset(runtimeStrip2, 0, sizeof(runtimeStrip2));

    Animation_Init(animState1);
    Animation_Init(animState2);
}

void RGB_Runtime_Update(const SystemState& state)
{
     if (!state.powerOn)
    {
        memset(runtimeStrip1, 0, sizeof(runtimeStrip1));
        memset(runtimeStrip2, 0, sizeof(runtimeStrip2));

        animated   = false;
        // brightness = 0;
        return;
    }

    const RGBMode& mode = RGB_modes_Get(state.currentMode);

    activeMode = state.currentMode;
    brightness = mode.brightness;

    if (mode.type == MODE_ANIMATED)
    {
        animated = true;
        baseMode = mode.animated.baseModeIndex;
        animSpeedMs   = mode.animated.anim.speedMs;
        animIntensity = mode.animated.anim.intensity;

        const RGBMode& base = RGB_modes_Get(baseMode);
        if (base.type != MODE_PER_PIXEL)
        {
            // захист від неправильного base
            memset(runtimeStrip1, 0, sizeof(runtimeStrip1));
            memset(runtimeStrip2, 0, sizeof(runtimeStrip2));
            return;
        }

        AnimationParams safe = Animation_PrepareParams(mode.animated.anim);

        Animation_Update(animState1, safe);
        Animation_Update(animState2, safe);

        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            runtimeStrip1[i] = Animation_Apply(
                animState1,
                safe,
                base.perPixel.strip1[i],
                i,
                false
            );

            runtimeStrip2[i] = Animation_Apply(
                animState2,
                safe,
                base.perPixel.strip2[i],
                i,
                true
            );
        }
    }
    else
    {
        animated = false;
        baseMode = activeMode;
        animSpeedMs   = 0;
        animIntensity = 0;

        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            if (mode.type == MODE_SOLID)
            {
                runtimeStrip1[i] = mode.solid.strip1;
                runtimeStrip2[i] = mode.solid.strip2;
            }
            else // MODE_PER_PIXEL
            {
                runtimeStrip1[i] = mode.perPixel.strip1[i];
                runtimeStrip2[i] = mode.perPixel.strip2[i];
            }
        }
    }
}

// ===== GETTERS =====

const RGB* RGB_Runtime_GetStrip1() 
{ 
    return runtimeStrip1; 
}

const RGB* RGB_Runtime_GetStrip2() 
{ 
    return runtimeStrip2;
}

uint8_t RGB_Runtime_GetActiveMode() 
{ 
    return activeMode; 
}

uint8_t RGB_Runtime_GetBaseMode()   
{ 
    return baseMode; 
}

uint8_t RGB_Runtime_GetBrightness() 
{ 
    return brightness; 
}

bool    RGB_Runtime_IsAnimated()    
{ 
    return animated; 
}

uint16_t RGB_Runtime_GetAnimSpeedMs()
{
    return animSpeedMs;
}

uint8_t RGB_Runtime_GetAnimIntensity()
{
    return animIntensity;
}
