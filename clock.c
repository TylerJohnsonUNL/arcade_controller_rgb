#include "clock.h"

static time_t currentTime = 0;

static void CLOCK_timerCallback();

void CLOCK_init()
{
    //REDIRECT MCC's Timer0 CALLBACK TO FUNCTION
    TMR0_SetInterruptHandler(CLOCK_timerCallback);
}

time_t CLOCK_getTime() {
    return currentTime;
}

static void CLOCK_timerCallback() {
    currentTime++;
}
