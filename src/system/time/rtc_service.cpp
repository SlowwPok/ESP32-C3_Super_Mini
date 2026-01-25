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

    bool running = rtc.isrunning();
    Serial.println("RTC is running:");
    Serial.println(running ? "YES" : "NO");

    if (!running)
    {
        Serial.println("RTC was STOPPED - setting compile time with offset...");
        
        // ✅ Додати компенсацію ~60 секунд
        DateTime compileTime = DateTime(F(__DATE__), F(__TIME__));
        
        // Додаємо 60 секунд до часу компіляції
        DateTime adjustedTime = DateTime(compileTime.unixtime() + 30);
        
        rtc.adjust(adjustedTime);
        
        Serial.println("RTC time set with +60s offset!");
    }
    else
    {
        Serial.println("RTC is already running - keeping current time");
    }
    
    DateTime now = rtc.now();
    Serial.printf("Current RTC time: %04d/%02d/%02d %02d:%02d:%02d\n",
                  now.year(), now.month(), now.day(),
                  now.hour(), now.minute(), now.second());
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

    if (!firstSync && now - lastRtcSync < 10000)
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

void RTC_SetTime(int year, int month, int day, int hour, int minute, int second)
{
    if (!rtcOk)
    {
        Serial.println("ERROR: RTC not available!");
        return;
    }
    
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
    
    Serial.printf("✓ RTC set to: %04d-%02d-%02d %02d:%02d:%02d\n",
                  year, month, day, hour, minute, second);
    
    // Перевірка
    DateTime now = rtc.now();
    Serial.printf("✓ RTC read back: %04d-%02d-%02d %02d:%02d:%02d\n",
                  now.year(), now.month(), now.day(),
                  now.hour(), now.minute(), now.second());
}

// **Як користуватись:**

// 1. Відкрий Serial Monitor
// 2. Встанови "Both NL & CR" (або просто "Newline")
// 3. Подивись на годинник - зараз **13:20:00**
// 4. Відправ команду:
// ```
//    TIME 2026 01 26 13 20 00
// ```
// 5. Побачиш:
// ```
//    ✓ RTC set to: 2026-01-26 13:20:00
//    ✓ RTC read back: 2026-01-26 13:20:00