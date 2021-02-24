#include <xc.h>
#include "controller.h"

bool active; //NOT CURRENTLY USED
static uint16_t mode;
static time_t c = 300; //INCREASE AND DECREASE SPEED

#define SLEEP_TIME 10000

void CONTROLLER_init() {
    mode = 1;
    SEVENSEGMENT_setDigit(mode,0);
}

//INCREMENTS THE MODE AND UPDATES DISPLAY
void CONTROLLER_inc() {
    if (mode == 6)
        mode = 1;
    else
        mode++;

    //UPDATE THE DISPLAY
    SEVENSEGMENT_setDigit(mode,0);
}

//INCREMENTS THE BRIGHTNESS AND UPDATES THE DISPLAY
void CONTROLLER_heldInc() {
    static int brightnessMode = 1;
    if (brightnessMode == 9){
        brightnessMode = 1;
        LED_setBrightness(brightnessMode*100);
    } else {
        brightnessMode++;
        LED_setBrightness(brightnessMode*100);
    }
    
    //UPDATE THE DISPLAY
    SEVENSEGMENT_setDigit(brightnessMode,1); 
}

//RESTARTS MOMENTUM
void CONTROLLER_restart_momentum() {
    if (BUTTONS_isHeld(increase))
        return;
    c = 300; //RESET BACK TO 300
}

//CALL TO RUN MAIN CONTROLLER TASK
void CONTROLLER_task() {
    
    static time_t lastTime1;
    static time_t lastTime2;
    static time_t lastTime3;
    
    //RUN TIME
    time_t time = CLOCK_getTime();
    active = 1;
    if (time - lastTime1 < 1)
        return;
    lastTime1 = time;

    
    if (BUTTONS_isClicked(increase)) {
        CONTROLLER_inc();
    } else if (BUTTONS_isHeld(increase)) {
        
        if (time - lastTime2 < (c))
            return;
        lastTime2 = time;

        CONTROLLER_heldInc();

        if (c > 20) c = c - 1; //MOMENTUM
        
    } else {
        active = 0;
    }
    CONTROLLER_restart_momentum();
    
    //SLEEP SETTINGS
    if (time - lastTime3 < SLEEP_TIME)
        return;
    lastTime3 = time;
    
    if (active==false) SEVENSEGMENT_setDigit(10,0);
}

//CALL TO RETURNS CURRENT MODE
uint8_t CONTROLLER_currentMode(){
    return mode;
}
