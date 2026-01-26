#pragma once

struct BME280Data
{
    float temperature;   // °C
    float humidity;      // %
    float pressure;      // hPa

    bool  valid;
};