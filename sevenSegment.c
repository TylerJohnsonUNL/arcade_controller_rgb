#include <xc.h>
#include "sevenSegment.h"

static uint8_t numbTable[] = {
    0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90, 0xFF
};

void SEVENSEGMENT_init(){
    SEVENSEGMENT_setDigit(1,0);
    PORTBbits.RB5 = 1;
    __delay_us(500);
    PORTBbits.RB5 = 0;
}

void SEVENSEGMENT_setDigit(uint8_t digit,bool dotpoint){
    if (dotpoint == false) numbTable[digit] = numbTable[digit] | 0b10000000; //disables dot point
    if (dotpoint == true) numbTable[digit] = numbTable[digit] & 0b01111111; //enables dot point
    
    SPI_Write(numbTable[digit]);
    SPI_Write(0x7F);
}