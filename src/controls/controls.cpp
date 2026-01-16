#include "controls.h"

#define TOUCH_PIN 4
#define LONG_PRESS_TIME 800
#define DEBOUNCE_DELAY 50

struct ButtonFSM
{
    uint8_t pin;
    bool lastReading;
    bool stableState;
    unsigned long lastDebounce;
    unsigned long pressStart;
    bool longDone;
};

static ButtonFSM btn1;

void Controls_Init()
{
    btn1 = {
        .pin = TOUCH_PIN,
        .lastReading = false,
        .stableState = false,
        .lastDebounce = 0,
        .pressStart = 0,
        .longDone = false
    };

    pinMode(btn1.pin, INPUT);
}

static ControlEvent Button_Update(ButtonFSM& b)
{
    bool reading = digitalRead(b.pin);
    unsigned long now = millis();
    ControlEvent ev = CTRL_NONE;

    if (reading != b.lastReading)
        b.lastDebounce = now;

    if ((now - b.lastDebounce) > DEBOUNCE_DELAY)
    {
        if (reading != b.stableState)
        {
            b.stableState = reading;

            if (b.stableState)
            {
                b.pressStart = now;
                b.longDone = false;
            }
            else if (!b.longDone)
            {
                ev = CTRL_BTN1_TAP;
            }
        }
    }

    if (b.stableState && !b.longDone &&
        now - b.pressStart >= LONG_PRESS_TIME)
    {
        ev = CTRL_BTN1_HOLD;
        b.longDone = true;
    }

    b.lastReading = reading;
    return ev;
}

ControlEvent Controls_Update()
{
    return Button_Update(btn1);
}