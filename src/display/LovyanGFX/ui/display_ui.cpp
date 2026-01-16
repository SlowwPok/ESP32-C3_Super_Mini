#include "display_ui.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_config.h"
#include "rgb_runtime/rgb_runtime.h"
#include "rgb_strip/rgb_config.h"   // RGB_STRIP_LENGTH

static bool     lastPowerOn   = false;
static uint8_t  lastMode      = 0xFF;
static bool     lastAnimated  = false;

static uint8_t  lastBrightness = 0xFF;
static uint8_t  lastBaseMode   = 0xFF;

static bool     displaySleeping = false;
static uint32_t powerOffSinceMs = 0;

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
void DisplayUI_Render(const SystemState& state)
{
    bool prevPower = lastPowerOn;
    lastPowerOn = state.powerOn;
    
    uint8_t activeMode = RGB_Runtime_GetActiveMode();
    bool animated      = RGB_Runtime_IsAnimated();
    uint16_t animSpeed = RGB_Runtime_GetAnimSpeedMs();
    uint8_t  animInt   = RGB_Runtime_GetAnimIntensity();
    uint8_t brightness = RGB_Runtime_GetBrightness();
    uint8_t baseMode   = RGB_Runtime_GetBaseMode();

    // --- handle power off timing ---
    if (!state.powerOn)
    {
        if (prevPower) // щойно вимкнули
        {
            powerOffSinceMs = millis();
            displaySleeping = false;
        }

        // якщо вже OFF і пройшло 30 сек → гасимо дисплей
        if (!displaySleeping &&
            (millis() - powerOffSinceMs) > DISPLAY_SLEEP_DELAY_MS)
        {
            Display_Sleep();     // ← має бути у твоєму драйвері
            displaySleeping = true;
            return;
        }
    }

    // --- wake up display on power on ---
    if (state.powerOn && displaySleeping)
    {
        Display_Wakeup();   // ← вмикає підсвітку + дисплей
        displaySleeping = false;

        // примусово оновимо UI
        lastMode = 0xFF;
    }

    bool needRedraw =
        state.powerOn != prevPower ||
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

    const RGB* strip1 = RGB_Runtime_GetStrip1();
    const RGB* strip2 = RGB_Runtime_GetStrip2();

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
    drawStripColors(y, strip1);

    y += COLOR_BOX + 8;
    Display_DrawText(PADDING, y, 1, "STRIP 2", COLOR_WHITE);
    y += 12;
    drawStripColors(y, strip2);
}
