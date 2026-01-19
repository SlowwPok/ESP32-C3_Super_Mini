// path: src/res/ui_theme/ui_theme.h
#pragma once
#include <stdint.h>
#include <LovyanGFX.hpp>

struct UITheme
{
    // ===== COLORS =====
    uint16_t bg;
    uint16_t text;
    uint16_t text_dim;
    uint16_t header_text;
    uint16_t footer_text;
    uint16_t lines_color;

    // ===== FONTS =====
    const lgfx::v1::IFont* font_title;
    const lgfx::v1::IFont* font_body;
    const lgfx::v1::IFont* font_small;

    // ===== LAYOUT =====
    int padding;
    int header_height;
    int footer_height;
};

const UITheme& UI_GetTheme();
