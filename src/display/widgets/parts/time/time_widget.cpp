#include "time_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_theme/ui_theme.h"
#include <stdio.h>
#include <string.h>

// ===== STATE =====
static bool dirty = true;
static bool timeValid = false;

// кеш часу
static uint16_t lastYear  = 0;
static uint8_t  lastMonth = 0;
static uint8_t  lastDay   = 0;
static uint8_t  lastHour  = 255;
static uint8_t  lastMin   = 255;
static uint8_t  lastWday  = 255;

// локалізація (EN)
static const char* WEEKDAYS[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
static const char* MONTHS[]   = {
    "Jan","Feb","Mar","Apr","May","Jun",
    "Jul","Aug","Sep","Oct","Nov","Dec"
};

int TimeWidget_EstimatedWidth()
{
    const auto& theme = UI_GetTheme();
    int h = Display_GetFontHeight(theme.font_small);
    return h * 14; // стабільна ширина
}

void TimeWidget_MarkDirty()
{
    dirty = true;
}

void TimeWidget_Update(const SystemState& state)
{
    const auto& t = state.time;

    bool valid =
        t.year >= 2020 &&
        t.month >= 1 && t.month <= 12 &&
        t.weekday < 7;

    if (!valid)
        return;

    timeValid = true;

    if (t.year    != lastYear  ||
        t.month   != lastMonth ||
        t.day     != lastDay   ||
        t.hour    != lastHour  ||
        t.minute  != lastMin   ||
        t.weekday != lastWday)
    {
        lastYear  = t.year;
        lastMonth = t.month;
        lastDay   = t.day;
        lastHour  = t.hour;
        lastMin   = t.minute;
        lastWday  = t.weekday;
        dirty = true;
    }
}

void TimeWidget_Draw(int xRight, int y, int h)
{
    if (!dirty)
        return;

    const auto& theme = UI_GetTheme();

    char buf[40]; // було 48

    if (!timeValid)
{
    strcpy(buf, "--:--");
}
else
{
    uint8_t wday  = lastWday;
    uint8_t month = lastMonth - 1;

    uint8_t hour12 = lastHour % 12;
    if (hour12 == 0) hour12 = 12;
    bool pm = lastHour >= 12;

    snprintf(
        buf,
        sizeof(buf),
        "%s %02d %s %04d %02d:%02d %s",
        WEEKDAYS[wday],
        lastDay,
        MONTHS[month],
        lastYear,
        hour12,
        lastMin,
        pm ? "PM" : "AM"
    );
    }

    // === вертикаль ===
    int textH = Display_GetFontHeight(theme.font_small);
    int ty = y + (h - textH) / 2;

    // === горизонталь (RIGHT ALIGN) ===
    // LovyanGFX textWidth напряму недоступний через твій wrapper,
    // тому використовуємо стабільну оцінку:
    // середня ширина символу ≈ 0.55 * fontHeight
    int charW = (textH * 11) / 20; // ~0.55
    int textW = charW * strlen(buf);

    int drawX = xRight - textW;

    // safety clamp
    if (drawX < theme.padding)
        drawX = theme.padding;

    Display_DrawTextEx(
        drawX,
        ty,
        buf,
        theme.time_text,
        theme.bg,
        true,
        theme.font_small,
        0
    );

    dirty = false;
}

// формат залишений на майбутнє
static TimeWidgetFormat currentFormat = TIME_FULL_12H;

void TimeWidget_SetFormat(TimeWidgetFormat format)
{
    if (format != currentFormat)
    {
        currentFormat = format;
        dirty = true;
    }
}