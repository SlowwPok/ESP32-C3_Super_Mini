// path: src/display/widgets/common/header/header_container.cpp
#include "header_container.h"
#include "display/widgets/ui_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_color_palette.h"

#include "widgets/header_text_widget.h"

static HeaderTextWidget textWidget;

void HeaderContainer_Draw()
{
    const int h = UI_HEADER_HEIGHT;

    // фон
    Display_FillRect(0, 0, Display_Width(), h, UI_COLOR_BG);

    // межа
    Display_DrawLine(0, h - 1, Display_Width(), h - 1, UI_COLOR_BOUNDARY);

    int x = UI_PADDING;
    textWidget.Draw(x, 0, h);
}