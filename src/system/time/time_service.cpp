#include "time_service.h"
#include "system/system_state.h"
#include <Arduino.h>

void TimeService_Init()
{
    auto& t = System_GetMutable().time;

    t.year = 2026;
    t.month = 1;
    t.day = 24;
    t.weekday = 6; // Sat
    t.hour = 22;
    t.minute = 7;
    t.second = 0;
}

void TimeService_Update()
{
    static uint32_t lastTick = 0;
    uint32_t now = millis();

    if (now - lastTick < 1000)
        return;

    lastTick = now;

    auto& t = System_GetMutable().time;

    t.second++;
    if (t.second >= 60)
    {
        t.second = 0;
        t.minute++;
    }
    if (t.minute >= 60)
    {
        t.minute = 0;
        t.hour++;
    }
    if (t.hour >= 24)
    {
        t.hour = 0;
        t.day++;
        t.weekday = (t.weekday + 1) % 7;
    }
}