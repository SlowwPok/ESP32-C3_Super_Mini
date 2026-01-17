#include "display_ui.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_config.h"

#include "rgb/runtime/rgb_runtime.h"
#include "rgb/strip/rgb_config.h" 
#include "rgb/modes/rgb_modes.h"


static RGB previewStrip1[RGB_STRIP_LENGTH];
static RGB previewStrip2[RGB_STRIP_LENGTH];

static void DisplayUI_RenderRGB(const SystemState& state);
static void DisplayUI_RenderSystem(const SystemState& state);
static void handlePowerAndSleep(const SystemState& state);

static uint8_t  lastMode      = 0xFF;
static bool     lastAnimated  = false;

static uint8_t  lastBrightness = 0xFF;
static uint8_t  lastBaseMode   = 0xFF;

static const uint32_t DISPLAY_SLEEP_DELAY_MS = 5000; // 5 секунд

// ===== Layout =====
static const int PADDING   = 10;
static const int COLOR_BOX = 14;

// ===== Helpers =====
static void drawStripColors(int y, const RGB* colors)
{
    int x = PADDING;

    for (int i = 0; i < RGB_STRIP_LENGTH; i++)
    {
        uint16_t c565 = Display_ColorFromRGB_ForPreview(colors[i]);

        Display_FillRect(x, y, COLOR_BOX, COLOR_BOX, c565);
        Display_DrawRect(x, y, COLOR_BOX, COLOR_BOX, COLOR_WHITE);
        x += COLOR_BOX + 4;
    }
}

// ===== Main UI =====

static void handlePowerAndSleep(const SystemState& state)
{
    static bool lastPower = false;
    static bool sleeping = false;
    static uint32_t offSince = 0;

    if (!state.powerOn)
    {
        if (lastPower)
        {
            offSince = millis();
            sleeping = false;
        }

        if (!sleeping &&
            (millis() - offSince) > DISPLAY_SLEEP_DELAY_MS)
        {
            Display_Sleep();
            sleeping = true;
        }
    }
    else if (sleeping)
    {
        Display_Wakeup();
        sleeping = false;
    }

    lastPower = state.powerOn;
}

void DisplayUI_Render(const SystemState& state)
{
    handlePowerAndSleep(state);

    if (!state.powerOn)
        return;

    switch (state.activeScreen)
    {
        case SCREEN_RGB:
            DisplayUI_RenderRGB(state);
            break;

        case SCREEN_SYSTEM:
            DisplayUI_RenderSystem(state);
            break;
    }
}

static void DisplayUI_RenderRGB(const SystemState& state)
{    
    uint8_t activeMode = RGB_Runtime_GetActiveMode();
    bool animated      = RGB_Runtime_IsAnimated();
    uint16_t animSpeed = RGB_Runtime_GetAnimSpeedMs();
    uint8_t  animInt   = RGB_Runtime_GetAnimIntensity();
    uint8_t brightness = RGB_Runtime_GetBrightness();
    uint8_t baseMode   = RGB_Runtime_GetBaseMode();

    bool needRedraw =
        activeMode    != lastMode    ||
        animated      != lastAnimated ||
        brightness    != lastBrightness ||
        baseMode      != lastBaseMode;

    if (!needRedraw)
    {
        return;
    }

    lastMode       = activeMode;
    lastAnimated   = animated;
    lastBrightness = brightness;
    lastBaseMode   = baseMode;

    const RGBMode& mode = RGB_modes_Get(activeMode);

    // ===== BUILD PREVIEW (UI ONLY, NO RUNTIME) =====

    if (mode.type == MODE_SOLID)
    {
        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            previewStrip1[i] = mode.solid.strip1;
            previewStrip2[i] = mode.solid.strip2;
        }
    }
    else if (mode.type == MODE_PER_PIXEL)
    {
        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            previewStrip1[i] = mode.perPixel.strip1[i];
            previewStrip2[i] = mode.perPixel.strip2[i];
        }
    }
    else if (mode.type == MODE_ANIMATED)
    {
        const RGBMode& base = RGB_modes_Get(mode.animated.baseModeIndex);

        if (base.type == MODE_SOLID)
        {
            for (int i = 0; i < RGB_STRIP_LENGTH; i++)
            {
                previewStrip1[i] = base.solid.strip1;
                previewStrip2[i] = base.solid.strip2;
            }
        }
        else if (base.type == MODE_PER_PIXEL)
        {
            for (int i = 0; i < RGB_STRIP_LENGTH; i++)
            {
                previewStrip1[i] = base.perPixel.strip1[i];
                previewStrip2[i] = base.perPixel.strip2[i];
            }
        }
    }

    // ===== RENDER UI =====

    Display_Clear(COLOR_BLACK);

    if (!state.powerOn)
    {
        Display_DrawText(
            Display_Width() / 2 - 20,
            Display_Height() / 2,
            2,
            "OFF",
            COLOR_GRAY
        );
        return;
    }

    char title[40];

    const char* activeName = RGB_Runtime_GetActiveModeName();
    const char* baseName   = RGB_Runtime_GetBaseModeName();

    if (animated)
    {
        snprintf(title, sizeof(title),
                "ANIM %d: %s",
                activeMode,
                activeName);
    }
    else
    {
        snprintf(title, sizeof(title),
                "MODE %d: %s",
                activeMode,
                activeName);
    }

    int textY = PADDING;

    Display_DrawText(PADDING, textY, 2, title, COLOR_WHITE);
    textY += 18;

    if (animated)
    {
        char base[32];
        snprintf(base, sizeof(base), "BASE: %s", baseName);
        Display_DrawText(PADDING, textY, 1, base, COLOR_GRAY);
        textY += 14;

        char animLine[32];
        snprintf(animLine, sizeof(animLine),
                "SPD %dms  INT %d",
                animSpeed,
                animInt);
        Display_DrawText(PADDING, textY, 1, animLine, COLOR_GRAY);
        textY += 14;
    }

    char bri[16];
    snprintf(bri, sizeof(bri), "BRI %d", brightness);
    Display_DrawText(PADDING, textY, 1, bri, COLOR_GRAY);

    int y = textY + 16;

    Display_DrawText(PADDING, y, 1, "STRIP 1", COLOR_WHITE);
    y += 12;

    drawStripColors(y, previewStrip1);

    y += COLOR_BOX + 8;
    Display_DrawText(PADDING, y, 1, "STRIP 2", COLOR_WHITE);
    y += 12;

    drawStripColors(y, previewStrip2);
}

static void DisplayUI_RenderSystem(const SystemState& state)
{
    Display_Clear(COLOR_BLACK);

    Display_DrawText(
        PADDING,
        PADDING,
        2,
        "SYSTEM",
        COLOR_WHITE
    );

    // тимчасово, щоб екран не був пустий
    Display_DrawText(
        PADDING,
        PADDING + 20,
        1,
        "System screen placeholder",
        COLOR_GRAY
    );
}