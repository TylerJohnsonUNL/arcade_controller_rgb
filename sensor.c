#include <xc.h>
#include "sensor.h"

static bool detected = false;

void SENSOR_init(){
}
void SENSOR_check(){
    if (PORTAbits.RA5 == 1){
        detected = true;
    }else{
        detected = false;
    }
}
bool MOVEMENT_detected(){
    if (detected){
        detected = false;
        return true;
    }
    return false;
}
