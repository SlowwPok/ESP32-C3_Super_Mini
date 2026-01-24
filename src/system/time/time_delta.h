#pragma once
#include <stdint.h>

/*
    TimeDelta — результат порівняння двох DateTime
    UI дивиться СЮДИ, а не в секунди напряму
*/

struct TimeDelta
{
    bool second;
    bool minute;
    bool hour;
    bool day;
};