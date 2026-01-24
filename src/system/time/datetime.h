#pragma once
#include <stdint.h>

/*
    DateTime — сирі дані часу
    ❗ ЖОДНОГО форматування
    ❗ ЖОДНОГО дисплея
*/

struct DateTime
{
    uint16_t year;     // 2026
    uint8_t  month;    // 1–12
    uint8_t  day;      // 1–31
    uint8_t  weekday; // 1–7 (обираємо один стандарт)
    uint8_t  hour;     // 0–23
    uint8_t  minute;   // 0–59
    uint8_t  second;   // 0–59
};