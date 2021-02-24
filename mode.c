#include <xc.h>
#include "mode.h"

void MODE_task(uint8_t MODE){
    //TODO: make a better method for brightness as it throws off values...
    //possibly add the bightness to the end using some method to scale the brightness
    //TODO: Make a starting fade for beginning of sensor read
    if(MODE==1){
        LED_task(COLOR_RAINBOW,EFFECT_MEDIUMFADE);
        //LED_setBrightness(1000);
        PORTCbits.RC7 = 0;
        PORTAbits.RA4 = 1;
        return;
    }
    if(MODE==2){
        LED_task(COLOR_RAINBOW,EFFECT_STROBE);
        //LED_setBrightness(150);
        PORTCbits.RC7 = 0;
        PORTAbits.RA4 = 1;
        return;
    }
    if(MODE==3){
        LED_task(COLOR_RED,EFFECT_STEADY);
        //LED_setBrightness(200);
        PORTCbits.RC7 = 0;
        PORTAbits.RA4 = 1;
        return;
    }
    if(MODE==4){
        LED_task(COLOR_GREEN,EFFECT_STEADY);
        //LED_setBrightness(200);
        PORTCbits.RC7 = 0;
        PORTAbits.RA4 = 1;
        return;
    }
    if(MODE==5){
        LED_task(COLOR_BLUE,EFFECT_STEADY);
        //LED_setBrightness(200);
        PORTCbits.RC7 = 0;
        PORTAbits.RA4 = 1;
        return;
    }
    if(MODE==6){
        LED_task(COLOR_ORANGE,EFFECT_STEADY);
        //LED_setBrightness(200);
        PORTCbits.RC7 = 0;
        PORTAbits.RA4 = 1;
        return;
    }
    if(MODE==0){
        LED_task(COLOR_OFF,EFFECT_MEDIUMFADE);
        PORTCbits.RC7 = 1;
        PORTAbits.RA4 = 0;
        return;
    }
}
