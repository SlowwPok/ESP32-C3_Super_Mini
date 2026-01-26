#include "bme280_service.h"
#include <Adafruit_BME280.h>
#include "system/system_pin_setup.h"

static Adafruit_BME280 bme;
static bool bmeOk = false;

void BME280_Init()
{
    Serial.println("BME280_Init: Starting...");
    
    // ✅ Спроба 1: адреса 0x76
    unsigned long start = millis();
    bmeOk = bme.begin(0x76);
    
    if (!bmeOk && (millis() - start < 1000))  // ✅ Таймаут 1 секунда
    {
        Serial.println("BME280: Trying 0x77...");
        bmeOk = bme.begin(0x77);
    }

    Serial.print("BME280: ");
    Serial.println(bmeOk ? "OK" : "NOT FOUND");
    
    if (!bmeOk)
    {
        Serial.println("⚠️  BME280 not detected - sensor data will be unavailable");
    }
}

bool BME280_IsOk()
{
    return bmeOk;
}

void BME280_Update(SystemState& state)
{
    static uint32_t lastRead = 0;
    static bool firstRead = true;

    uint32_t now = millis();

    if (!firstRead && now - lastRead < 1000)
        return;

    firstRead = false;
    lastRead = now;

    if (!bmeOk)
    {
        state.bme.valid = false;
        return;
    }

    state.bme.temperature = bme.readTemperature();
    state.bme.humidity    = bme.readHumidity();
    state.bme.pressure    = bme.readPressure() / 100.0f;
    state.bme.valid       = true;
}