#include "display_ui.h"

#include "display/widgets/ui_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/screens/ui_rgb_screen.h"

#include "res/ui_color_palette.h"

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
    if (!state.powerOn)
        return;

    Display_Clear(UI_COLOR_BG);

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
