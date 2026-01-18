//path: src/display/widgets/ui_widget.h
#pragma once
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_theme/ui_theme.h"

// ===== LAYOUT HELPERS (THEME-BASED) =====

inline int UI_Padding()
{
    return UI_GetTheme().padding;
}

inline int UI_HeaderHeight()
{
    return UI_GetTheme().header_height;
}

inline int UI_FooterHeight()
{
    return UI_GetTheme().footer_height;
}

inline int UI_HeaderTop() { return 0; }
inline int UI_HeaderBottom() { return UI_HeaderHeight(); }

inline int UI_BodyTop()
{
    return UI_HeaderHeight();
}

inline int UI_BodyBottom()
{
    return Display_Height() - UI_FooterHeight();
}

inline int UI_FooterTop()
{
    return Display_Height() - UI_FooterHeight();
}