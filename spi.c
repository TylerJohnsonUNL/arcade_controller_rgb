#include <xc.h>
#include "spi.h"

static time_t lastTimeSPI = 0;

void SPI_Init(){
    SPI1_Initialize();
    SPI1_Open(SPI1_DEFAULT);
}

void SPI_Write(uint8_t outputValue){
    SPI1_WriteByte(outputValue);
    
    time_t time = CLOCK_getTime();
    if (time - lastTimeSPI > 25){
        PORTBbits.RB5 = 1;
        PORTBbits.RB5 = 0;
    }
    lastTimeSPI = time;
}