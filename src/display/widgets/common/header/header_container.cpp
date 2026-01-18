// path: src/display/widgets/common/header/header_container.cpp
#include "header_container.h"

#include "display/widgets/ui_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_theme/ui_theme.h"

#include "widgets/header_text_widget.h"

static HeaderTextWidget textWidget;
static bool dirty = true;

void HeaderContainer_MarkDirty()
{
    dirty = true;
}

void HeaderContainer_Draw()
{
    if (!dirty)
    return;

    const auto& theme = UI_GetTheme();
    const int h = theme.header_height;

    // фон
    Display_FillRect(
        0,
        UI_HeaderTop(),
        Display_Width(),
        h,
        theme.bg
    );

    // межа
    Display_DrawLine(
        0,
        UI_HeaderBottom() - 1,
        Display_Width(),
        UI_HeaderBottom() - 1,
        theme.boundary
    );

    int x = theme.padding;
    textWidget.Draw(x, UI_HeaderTop(), h);

    dirty = false;
}