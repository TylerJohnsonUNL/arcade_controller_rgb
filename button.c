#include <xc.h>
#include "button.h"

static button_t buttons[BUTTON_COUNT];
button_t *increase;


void BUTTONS_task() {
    
    static uint8_t lastTime = 0;
    
    //RUN TIME
    time_t time = CLOCK_getTime();
    if (time - lastTime < BUTTON_SCAN_INTERVAL)
        return;
    lastTime = time;

    //CHECK STATUS OF EACH BUTTON
    for (uint8_t i = 0; i < BUTTON_COUNT; i++){
        button_t* btn = buttons + i;
        
        //CHECK IF BUTTON IS CURRENTLY ACTIVATED OR NOT
        if ((*(btn->port) & (1 << (btn->pin))) == 0){ 
            btn->state = STATE_PRESSED;
            btn->timeHeld = btn->timeHeld++;
        }else if ((*(btn->port) & (1 << (btn->pin))) != 0) {
            btn->state = STATE_UNPRESSED;
            btn->timeHeld = 0;
            btn->event = EVENT_IDLE;
        }
        if (
            btn->state == STATE_UNPRESSED 
            && btn->lastState == STATE_PRESSED
            ){ 
            // BUTTON RELEASED
            btn->event = EVENT_PRESSED;
        }
        if((btn->timeHeld)>=HOLD_TIME){
            btn->event=EVENT_HOLD;
            btn->state=STATE_HELD;
        }
        btn->lastState = btn->state;
    }
}

static void init(button_t* btn, volatile uint8_t* port, uint8_t pin) {
    btn->port = port;
    btn->pin = pin;
    btn->state = STATE_UNPRESSED;
    btn->event = EVENT_IDLE;
    btn->timeHeld = 0;
}

void BUTTONS_init() {
    increase = &buttons[0];

    init(increase, &PORTA, 2);
}

bool BUTTONS_isClicked(button_t* button) {
    if (button->event == EVENT_PRESSED) {
        button->event = EVENT_IDLE;
        return true;
    }
    return false;
}

bool BUTTONS_isHeld(button_t* button){
    if(button->event==EVENT_HOLD){
        return true;
    }
    return false;
}