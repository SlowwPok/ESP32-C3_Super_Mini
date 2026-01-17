#pragma once
#include "display/LovyanGFX/display_LovyanGFX.h"

// ===== GLOBAL UI LAYOUT CONFIG =====

constexpr int UI_PADDING       = 10;
constexpr int UI_HEADER_HEIGHT = 24;
constexpr int UI_FOOTER_HEIGHT = 20;

// ===== LAYOUT HELPERS =====

inline int UI_HeaderTop() {
    return 0;
}

inline int UI_HeaderBottom() {
    return UI_HEADER_HEIGHT;
}

inline int UI_BodyTop() {
    return UI_HEADER_HEIGHT;
}

inline int UI_BodyBottom() {
    return Display_Height() - UI_FOOTER_HEIGHT;
}

inline int UI_BodyHeight() {
    return UI_BodyBottom() - UI_BodyTop();
}

inline int UI_FooterTop() {
    return Display_Height() - UI_FOOTER_HEIGHT;
}
