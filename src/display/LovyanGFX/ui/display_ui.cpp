#include "display_ui.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_rgb_preview.h"

static void handlePowerAndSleep(const SystemState& state);

void DisplayUI_Render(const SystemState& state)
{
    handlePowerAndSleep(state);

    if (!state.powerOn)
        return;

    if (state.activeScreen == SCREEN_RGB)
    {
        UI_RGBPreview_Update(state);
        UI_RGBPreview_Render();
    }
}
