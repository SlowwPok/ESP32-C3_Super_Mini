// path: src/display/display_ui.cpp
#include "display_ui.h"
#include "display/widgets/ui_widget.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/screens/ui_rgb_screen.h"
#include "system/system_state.h"

#include "res/fonts/ui_fonts.h"
#include "res/ui_color_palette.h"

static void handlePowerAndSleep(const SystemState& state)
{
    static bool lastPower = true;

    if (state.powerOn != lastPower)
    {
        if (!state.powerOn)
            Display_Sleep();
        else
            Display_Wakeup();

        lastPower = state.powerOn;
    }
}

static void DrawHeader()
{
    static const char* headerText = "ESP32-C3 Super Mini";

    // 1. Очистити область header
    Display_FillRect(
        0,
        0,
        Display_Width(),
        UI_HEADER_HEIGHT,
        UI_COLOR_BG
    );

    // 2. Обрати шрифт
    const lgfx::v1::IFont* font = UIFonts::Small_8pt7b();

    // 3. Порахувати вертикальне центрування
    int textHeight = Display_GetFontHeight(font);
    int y = (UI_HEADER_HEIGHT - textHeight) / 2;

    // 4. Намалювати текст
    Display_DrawTextEx(
        UI_PADDING,
        y,
        headerText,
        UI_COLOR_TEXT,
        UI_COLOR_BG,
        false,
        font,
        0
    );

    // 5. Нижня межа header
    Display_DrawLine(
        0,
        UI_HEADER_HEIGHT - 1,
        Display_Width(),
        UI_HEADER_HEIGHT - 1,
        UI_COLOR_BOUNDARY
    );
}

static void DrawFooter()
{
    static const char* footerText = "Hold: Power | Tap: Mode";

    int yTop = UI_FooterTop();
    const lgfx::v1::IFont* font = UIFonts::Small_8pt7b();

    // 1. Очистити footer
    Display_FillRect(
        0,
        yTop,
        Display_Width(),
        UI_FOOTER_HEIGHT,
        UI_COLOR_BG
    );

    // 2. Висота шрифту
    int textHeight = Display_GetFontHeight(font);

    // 3. Вертикальне центрування
    int y = yTop + (UI_FOOTER_HEIGHT - textHeight) / 2;

    // 4. Верхня межа footer
    Display_DrawLine(
        0,
        yTop,
        Display_Width(),
        yTop,
        UI_COLOR_BOUNDARY
    );

    // 5. Текст
    Display_DrawTextEx(
        UI_PADDING,
        y,
        footerText,
        UI_COLOR_DIM_TEXT,
        UI_COLOR_BG,
        false,
        font,
        0
    );
}

void DisplayUI_Render(const SystemState& state)
{
    static ScreenId lastScreen = SCREEN_RGB;

    handlePowerAndSleep(state);
    if (!state.powerOn)
        return;

    if (state.activeScreen != lastScreen)
    {
        Display_Clear(UI_COLOR_BG); 

        switch (state.activeScreen)
        {
            case SCREEN_RGB:
                UI_RGBScreen_Init();
                break;

            case SCREEN_SYSTEM:
                // UI_SystemScreen_Init();
                break;
        }
        lastScreen = state.activeScreen;
    }

    DrawHeader();
    DrawFooter();

    switch (state.activeScreen)
    {
        case SCREEN_RGB:
            UI_RGBScreen_Update(state);
            UI_RGBScreen_Render();
            break;
    }
}

