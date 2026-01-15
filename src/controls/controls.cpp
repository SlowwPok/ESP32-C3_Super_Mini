#include "controls.h"

/* =========================================================
   КОНФІГУРАЦІЯ
   ========================================================= */

#define TOUCH_PIN 4
#define LONG_PRESS_TIME 800

/* =========================================================
   ВНУТРІШНІ ТИПИ
   ========================================================= */

enum TouchState
{
    TOUCH_IDLE,
    TOUCH_PRESSED,
};

/* =========================================================
   СТАН
   ========================================================= */

static bool lastPressed = false;
static unsigned long pressStart = 0;
static bool longDone = false;

/* =========================================================
   API
   ========================================================= */

void Controls_Init()
{
    pinMode(TOUCH_PIN, INPUT);
}

ControlEvent Controls_Update()
{
    bool pressed = digitalRead(TOUCH_PIN);
    unsigned long now = millis();

    ControlEvent ev = CTRL_NONE;

    if (pressed && !lastPressed)
    {
        pressStart = now;
        longDone = false;
    }

    if (pressed && !longDone && now - pressStart >= LONG_PRESS_TIME)
    {
        ev = CTRL_TOGGLE_POWER;
        longDone = true;
    }

    if (!pressed && lastPressed && !longDone)
    {
        ev = CTRL_NEXT_MODE;
    }

    lastPressed = pressed;
    return ev;
}