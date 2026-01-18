// path: src/display/widgets/common/footer/footer_container.cpp
#include "footer_container.h"

#include "display/widgets/ui_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_color_palette.h"

#include "widgets/footer_text_widget.h"

static FooterTextWidget textWidget;

void FooterContainer_Draw()
{
    const auto& theme = UI_GetTheme();
    int yTop = UI_FooterTop();

    Display_FillRect(
        0,
        yTop,
        Display_Width(),
        theme.footer_height,
        theme.bg
    );

    Display_DrawLine(
        0,
        yTop,
        Display_Width(),
        yTop,
        theme.boundary
    );

    int x = theme.padding;
    textWidget.SetText("Hold: Power | Tap: Mode");
    textWidget.Draw(x, yTop, theme.footer_height);
}