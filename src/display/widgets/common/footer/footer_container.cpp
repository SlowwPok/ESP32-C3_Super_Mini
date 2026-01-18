// path: src/display/widgets/common/footer/footer_container.cpp
#include "footer_container.h"
#include "display/widgets/ui_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_color_palette.h"

#include "widgets/footer_text_widget.h"

static FooterTextWidget textWidget;

void FooterContainer_Draw()
{
    const int h = UI_FOOTER_HEIGHT;

    // фон
    Display_FillRect(0, 0, Display_Width(), h, UI_COLOR_BG);

    // межа
    Display_DrawLine(0, h - 1, Display_Width(), h - 1, UI_COLOR_DIM_TEXT);

    int x = UI_PADDING;
    textWidget.Draw(x, 0, h);
}