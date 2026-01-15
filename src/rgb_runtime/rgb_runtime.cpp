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

static inline RGB applyBrightness(const RGB& c, uint8_t brightness)
{
    RGB out;
    out.r = (uint16_t)c.r * brightness / 255;
    out.g = (uint16_t)c.g * brightness / 255;
    out.b = (uint16_t)c.b * brightness / 255;
    return out;
}

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
            RGB c1 = Animation_Apply(
                animState1,
                mode.animated.anim,
                base.perPixel.strip1[i],
                i,
                false
            );

            RGB c2 = Animation_Apply(
                animState2,
                mode.animated.anim,
                base.perPixel.strip2[i],
                i,
                true
            );

            runtimeStrip1[i] = applyBrightness(c1, brightness);
            runtimeStrip2[i] = applyBrightness(c2, brightness);
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
                runtimeStrip1[i] = applyBrightness(mode.solid.strip1, brightness);
                runtimeStrip2[i] = applyBrightness(mode.solid.strip2, brightness);
            }
            else // MODE_PER_PIXEL
            {
                runtimeStrip1[i] = applyBrightness(mode.perPixel.strip1[i], brightness);
                runtimeStrip2[i] = applyBrightness(mode.perPixel.strip2[i], brightness);
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
