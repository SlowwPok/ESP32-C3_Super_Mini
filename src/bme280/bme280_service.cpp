#include "bme280_service.h"
#include <Adafruit_BME280.h>
#include "system/system_pin_setup.h"

static Adafruit_BME280 bme;
static bool bmeOk = false;

void BME280_Init()
{
    // 0x76 — найчастіше, 0x77 — другий варіант
    bmeOk = bme.begin(0x76);

    if (!bmeOk)
    {
        bmeOk = bme.begin(0x77);
    }

    Serial.print("BME280: ");
    Serial.println(bmeOk ? "OK" : "NOT FOUND");
}

bool BME280_IsOk()
{
    return bmeOk;
}

void BME280_Update(SystemState& state)
{
    static uint32_t lastRead = 0;
    uint32_t now = millis();

    if (now - lastRead < 1000)
        return;

    lastRead = now;

    if (!bmeOk)
    {
        state.bme.valid = false;
        return;
    }

    state.bme.temperature = bme.readTemperature();          // °C
    state.bme.humidity    = bme.readHumidity();             // %
    state.bme.pressure    = bme.readPressure() / 100.0f;    // hPa
    state.bme.valid       = true;
}