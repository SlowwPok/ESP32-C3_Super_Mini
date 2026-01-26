// path: src/display/display_ui.cpp
#include "display_ui.h"
#include "res/fonts/ui_fonts.h"
#include "system/system_state.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"
#include "display/widgets/common/header/header_container.h"
#include "display/widgets/common/footer/footer_container.h"
#include "display/widgets/screens/sensor_info/ui_sensor_info_screen.h"
#include "display/widgets/screens/rgb_preview/ui_rgb_screen.h"
#include "res/ui_color_palette.h"
#include "system/user_config.h"

void DisplayUI_Render(const SystemState& state)
{
    if (!state.displayOn)
    return;
    
    // Оновлюй дисплей максимум 30 FPS
    static unsigned long lastUpdate = 0;
    unsigned long now = millis();
    
    if (now - lastUpdate < DISPLAY_REFRESH_RATE_MS) { // ~30 FPS
        return;
    }
    lastUpdate = now;

    static ScreenId lastScreen = SCREEN_RGB;

    // handlePowerAndSleep(state);
    // if (!state.displayOn)
    //     return;

    if (state.activeScreen != lastScreen)
    {
        Display_Clear(UI_COLOR_BG);
        HeaderContainer_MarkDirty();
        FooterContainer_MarkDirty();

        if (state.activeScreen == SCREEN_RGB)
            UI_RGBScreen_Init();
        else if (state.activeScreen == SCREEN_SENSOR_INFO)
        UI_SensorInfoScreen_Init();

        lastScreen = state.activeScreen;
    }

    HeaderContainer_Draw();
    FooterContainer_Draw();

    if (state.activeScreen == SCREEN_RGB)
    {
        UI_RGBScreen_Update(state);
        UI_RGBScreen_Render();
    }
    else if (state.activeScreen == SCREEN_SENSOR_INFO)
    {
        UI_SensorInfoScreen_Update(state);
        UI_SensorInfoScreen_Render();
    }
}

