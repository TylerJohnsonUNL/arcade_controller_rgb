#ifndef LED_H
#define	LED_H

#include "mcc_generated_files/mcc.h"
#include "clock.h"

//COLOR SETS
typedef enum {
    COLOR_OFF,
    COLOR_RAINBOW,
    COLOR_RGB,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_ORANGE
} colorSet_t;

//EFFECT SETS
typedef enum {
    EFFECT_STEADY,
    EFFECT_SLOWFADE,
    EFFECT_MEDIUMFADE,
    EFFECT_FASTFADE,
    EFFECT_STROBE,
} effectSet_t;

typedef struct {
    int32_t red;
    int32_t green;
    int32_t blue;
    int32_t white;
    int size;
} color_t;

//CALL TO INITIALIZE STARTING VALUES
void LED_init();

//CALL TO SET BRIGHTNESS
void LED_setBrightness(uint16_t newBrightness);

//SETS VALUES OF EACH COLOR MODE
void LED_colorMode();

//FUNCTION TO INTERPERT THE COLOR RATE OF CHANGE
color_t LED_interp(color_t* startColor, color_t* stopColor, int colorPeriod, int currentTime);

//CALL TO RUN MAIN LED TASK
void LED_task(colorSet_t setColor, effectSet_t setEffect);

//SENDS FINAL COLOR
void LED_setColor(color_t* pColor);

#endif	/* LED_H */