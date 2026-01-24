#include "time_service.h"
#include "system/time/time_compare.h"

#include <Arduino.h>

static DateTime last{};
static unsigned long lastTickMs = 0;

void TimeService_Init()
{
    // стартове "фейкове" значення
    last = {
        .year = 2026,
        .month = 1,
        .day = 1,
        .weekday = 4, // наприклад, четвер
        .hour = 12,
        .minute = 0,
        .second = 0
    };

    lastTickMs = millis();
}

static void advanceOneSecond(DateTime& t)
{
    t.second++;
    if (t.second < 60) return;
    t.second = 0;

    t.minute++;
    if (t.minute < 60) return;
    t.minute = 0;

    t.hour++;
    if (t.hour < 24) return;
    t.hour = 0;

    // спрощено: день +1
    t.day++;
    t.weekday = (t.weekday % 7) + 1;
}

void TimeService_Update(SystemState& state)
{
    unsigned long now = millis();

    if (now - lastTickMs < 1000)
        return;

    lastTickMs += 1000;

    DateTime current = last;
    advanceOneSecond(current);

    state.timeDelta = Time_Compare(last, current);
    state.time = current;

    last = current;
}