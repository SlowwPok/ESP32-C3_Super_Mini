#include "controls.h"

/* =========================================================
   КОНФІГУРАЦІЯ
   ========================================================= */

#define TOUCH_PIN 4
#define LONG_PRESS_TIME 800
#define DEBOUNCE_DELAY 50 // 50 мс

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
static unsigned long lastDebounceTime = 0;
static bool lastStableState = false;
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
    bool reading = digitalRead(TOUCH_PIN);
    unsigned long now = millis();
    
    ControlEvent ev = CTRL_NONE;

    // Дебаунсинг
    if (reading != lastPressed) {
        lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > DEBOUNCE_DELAY) {
        if (reading != lastStableState) {
            lastStableState = reading;
            
            if (lastStableState) {
                // Натиснуто (стабільно)
                pressStart = now;
                longDone = false;
            } else if (!longDone) {
                // Відпущено (короткий тап)
                ev = CTRL_BTN1_TAP;
            }
        }
    }

    // Довге натискання
    if (lastStableState && !longDone && 
        now - pressStart >= LONG_PRESS_TIME) {
        ev = CTRL_BTN1_HOLD;
        longDone = true;
    }

    lastPressed = reading;
    return ev;
}