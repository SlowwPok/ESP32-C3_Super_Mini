#include "time_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_theme/ui_theme.h"
#include <stdio.h>

// ===== STATE =====
static bool dirty = true;

// кеш
static uint16_t lastYear  = 0;
static uint8_t  lastMonth = 0;
static uint8_t  lastDay   = 0;
static uint8_t  lastHour  = 255;
static uint8_t  lastMin   = 255;
static uint8_t  lastWday  = 255;

// локалізація (EN, стабільно)
static const char* WEEKDAYS[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
static const char* MONTHS[]   = { "Jan","Feb","Mar","Apr","May","Jun",
                                  "Jul","Aug","Sep","Oct","Nov","Dec" };
uint8_t wday  = (lastWday < 7) ? lastWday : 0;
uint8_t month = (lastMonth >= 1 && lastMonth <= 12) ? lastMonth : 1;

int TimeWidget_EstimatedWidth()
{
    // "Sat 24 Jan 2026 10:07 PM"
    return 170; // нормальний запас
}

void TimeWidget_MarkDirty()
{
    dirty = true;
}

void TimeWidget_Update(const SystemState& state)
{
    const auto& t = state.time;

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

void TimeWidget_Draw(int x, int y, int h)
{
    if (!dirty)
        return;

    const auto& theme = UI_GetTheme();
    char buf[48];

    // 12h формат
    uint8_t hour12 = lastHour % 12;
    if (hour12 == 0) hour12 = 12;
    bool pm = lastHour >= 12;

    snprintf(
        buf,
        sizeof(buf),
        "%s %02d %s %04d %02d:%02d %s",
        WEEKDAYS[lastWday],
        lastDay,
        MONTHS[lastMonth - 1],
        lastYear,
        hour12,
        lastMin,
        pm ? "PM" : "AM"
    );

    int textH = Display_GetFontHeight(theme.font_small);
    int ty = y + (h - textH) / 2;

    Display_DrawTextEx(
        x,
        ty,
        buf,
        theme.time_text, // ⬅ окремий колір, як ти хотів
        theme.bg,
        false,
        theme.font_small,
        0
    );

    dirty = false;
}

static TimeWidgetFormat currentFormat = TIME_FULL_12H;

void TimeWidget_SetFormat(TimeWidgetFormat format)
{
    if (format != currentFormat)
    {
        currentFormat = format;
        dirty = true;
    }
}