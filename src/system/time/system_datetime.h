// path: src/system/time/datetime.h
#pragma once
#include <stdint.h>

struct SystemDateTime
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
    uint8_t  weekday; // 0 = Sun
};