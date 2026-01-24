#include "rtc_service.h"
#include <Wire.h>
#include <RTClib.h>
#include "system/system_pin_setup.h"

static RTC_DS1307 rtc;

void RTC_Init()
{
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

    if (!rtc.begin())
    {
        // RTC не знайдений – залишаємо час нульовим
        return;
    }

    if (!rtc.isrunning())
    {
        // ВАЖЛИВО: один раз виставляєш реальний час
        rtc.adjust(
            ::DateTime(F(__DATE__), F(__TIME__))
        );
    }
}

void RTC_Update(SystemState& state)
{
    static uint32_t lastUpdate = 0;
    uint32_t now = millis();

    if (now - lastUpdate < 1000)
        return;

    lastUpdate = now;

    DateTime t = rtc.now();

    state.time.second  = t.second();
    state.time.minute  = t.minute();
    state.time.hour    = t.hour();
    state.time.day     = t.day();
    state.time.month   = t.month();
    state.time.year    = t.year();
    state.time.weekday = t.dayOfTheWeek(); // 0=Sun
}