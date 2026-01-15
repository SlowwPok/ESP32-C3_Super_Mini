#include "rgb_runtime.h"

#include "rgb_strip/rgb_modes.h"
#include "rgb_strip/animation_engine.h"
#include "rgb_strip/rgb_config.h"

#include <string.h>

// ===== ВНУТРІШНІ БУФЕРИ =====

static RGB runtimeStrip1[RGB_STRIP_LENGTH];
static RGB runtimeStrip2[RGB_STRIP_LENGTH];

// ===== META =====

static uint8_t activeMode = 0;
static uint8_t baseMode   = 0;
static uint8_t brightness = 0;
static bool    animated   = false;

// ===== ANIMATION STATE =====

static AnimationState animState1;
static AnimationState animState2;

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
        brightness = 0;
        return;
    }

    const RGBMode& mode = RGB_modes_Get(state.currentMode);

    activeMode = state.currentMode;
    brightness = mode.brightness;

    if (mode.type == MODE_ANIMATED)
    {
        animated = true;
        baseMode = mode.animated.baseModeIndex;

        const RGBMode& base = RGB_modes_Get(baseMode);

        Animation_Update(animState1, mode.animated.anim);
        Animation_Update(animState2, mode.animated.anim);

        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            runtimeStrip1[i] = Animation_Apply(
                animState1,
                mode.animated.anim,
                base.perPixel.strip1[i],
                i,
                false
            );

            runtimeStrip2[i] = Animation_Apply(
                animState2,
                mode.animated.anim,
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

const RGB* RGB_Runtime_GetStrip1() { return runtimeStrip1; }
const RGB* RGB_Runtime_GetStrip2() { return runtimeStrip2; }

uint8_t RGB_Runtime_GetActiveMode() { return activeMode; }
uint8_t RGB_Runtime_GetBaseMode()   { return baseMode; }
uint8_t RGB_Runtime_GetBrightness() { return brightness; }
bool    RGB_Runtime_IsAnimated()    { return animated; }
