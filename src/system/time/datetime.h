#pragma once
#include <stdint.h>

/*
    DateTime — універсальна модель часу
    ❗ без форматування
    ❗ без RTC
    ❗ без UI
*/

struct DateTime
{
    uint16_t year;     // 2026
    uint8_t  month;    // 1–12
    uint8_t  day;      // 1–31
    uint8_t  weekday; // 0–6 (Sun = 0)
    uint8_t  hour;     // 0–23
    uint8_t  minute;   // 0–59
    uint8_t  second;   // 0–59
};