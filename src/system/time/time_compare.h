#pragma once
#include "datetime.h"
#include "time_delta.h"

inline TimeDelta Time_Compare(const DateTime& prev, const DateTime& now)
{
    TimeDelta d{};

    d.second = (prev.second != now.second);
    d.minute = (prev.minute != now.minute);
    d.hour   = (prev.hour   != now.hour);
    d.day    = (prev.day    != now.day ||
                prev.month  != now.month ||
                prev.year   != now.year);

    return d;
}