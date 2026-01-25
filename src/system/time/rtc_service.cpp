#include "rtc_service.h"
#include <Wire.h>
#include <RTClib.h>
#include "system/system_pin_setup.h"

static RTC_DS1307 rtc;
static bool rtcOk = false;

void RTC_Init()
{
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    rtcOk = rtc.begin();

    
    Serial.begin(115200);
    Serial.println("RTC begin: ");
    Serial.println(rtcOk ? "OK" : "FAIL");

    if (!rtcOk)
        return;

    Serial.println("RTC is running:");
    Serial.println(rtc.isrunning() ? "YES" : "NO");

    if (!rtc.isrunning())
    {
        Serial.println("RTC adjusted");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

bool RTC_IsOk()
{
    return rtcOk;
}

static bool firstSync = true;
static uint32_t lastRtcSync = 0;

void RTC_Update(SystemState& state)
{
    if (!rtcOk)
        return;

    uint32_t now = millis();

    if (!firstSync && now - lastRtcSync < 60000)
        return;

    firstSync = false;
    lastRtcSync = now;

    DateTime t = rtc.now();

    state.time.year    = t.year();
    state.time.month   = t.month();
    state.time.day     = t.day();
    state.time.hour    = t.hour();
    state.time.minute  = t.minute();
    state.time.second  = t.second();
    state.time.weekday = t.dayOfTheWeek();
}