#include "display_ui.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/screens/ui_rgb_screen.h"

static const int HEADER_HEIGHT = 24;
static const int FOOTER_HEIGHT = 20;

static void DrawHeader()
{
    Display_DrawText(
        10,
        4,
        1,
        "тут буде header",
        COLOR_GRAY
    );
}

static void DrawFooter()
{
    int y = Display_Height() - FOOTER_HEIGHT + 4;

    Display_DrawText(
        10,
        y,
        1,
        "тут буде footer",
        COLOR_GRAY
    );
}

void DisplayUI_Render(const SystemState& state)
{
    if (!state.powerOn)
        return;

    Display_Clear(COLOR_BLACK);

    // ===== HEADER =====
    DrawHeader();

    // ===== BODY =====
    switch (state.activeScreen)
    {
        case SCREEN_RGB:
            UI_RGBScreen_Update(state);
            UI_RGBScreen_Render();
            break;

        case SCREEN_SYSTEM:
            // пізніше
            break;
    }

    // ===== FOOTER =====
    DrawFooter();
}
