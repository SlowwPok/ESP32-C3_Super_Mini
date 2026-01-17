// path: src/display/display_ui.cpp
#include "display_ui.h"

#include "display/widgets/ui_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/screens/ui_rgb_screen.h"
#include "system/system_state.h"
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
    Display_DrawText(
        UI_PADDING,
        6,
        1,
        "тут буде header",
        UI_COLOR_TEXT
    );

    // нижня межа header
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
    int y = UI_FooterTop();

    // верхня межа footer
    Display_DrawLine(
        0,
        y,
        Display_Width(),
        y,
        UI_COLOR_BOUNDARY
    );

    Display_DrawText(
        UI_PADDING,
        y + 4,
        1,
        "тут буде footer",
        UI_COLOR_TEXT
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

