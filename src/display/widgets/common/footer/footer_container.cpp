// path: src/display/widgets/common/footer/footer_container.cpp
#include "footer_container.h"

#include "display/widgets/ui_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_color_palette.h"

#include "widgets/footer_text_widget.h"

static FooterTextWidget textWidget;

static bool dirty = true;

void FooterContainer_MarkDirty()
{
    dirty = true;
}

void FooterContainer_SetText(const char* text)
{
    textWidget.SetText(text);
    dirty = true;
}

void FooterContainer_Draw()
{
    if (!dirty)
        return;

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
        theme.lines_color
    );

    int x = theme.padding;
    FooterContainer_SetText("Hold: Power | Tap: Mode");
    textWidget.Draw(x, yTop, theme.footer_height);

    dirty = false;
}