#include "led.h"
//CONTAINS ALL LED FUNCTIONS

static uint16_t brightness;
static color_t* currentColor;
static color_t* nextColor;
static color_t color[10][10]; //[MODE][PHASE]

//CALL TO INITIALIZE STARTING VALUES
void LED_init(){
    static color_t resetColor;
    currentColor = &resetColor;
    nextColor = &resetColor;
    LED_colorMode();
    LED_setBrightness(100); //STARTING BRIGHTNESS
}

//CALL TO SET BRIGHTNESS
void LED_setBrightness(uint16_t newBrightness){
    brightness = newBrightness;
    LED_colorMode();
}

//SETS VALUES OF EACH COLOR MODE
void LED_colorMode(){    
    //OFF
    color[0][0].size = 1;
    
    //RAINBOW
    color[1][0].red = brightness;
    color[1][0].white = brightness;
    color[1][1].red = brightness;
    color[1][1].green = brightness;
    color[1][1].white = brightness;
    color[1][2].green = brightness;
    color[1][2].white = brightness;
    color[1][3].green = brightness;
    color[1][3].blue = brightness;
    color[1][3].white = brightness;
    color[1][4].blue = brightness;
    color[1][4].white = brightness;
    color[1][5].blue = brightness;
    color[1][5].red = brightness;
    color[1][5].white = brightness;
    color[1][0].size = 6;
    
    //RGB
    color[2][0].red = brightness;
    color[2][0].white = brightness;
    color[2][1].green = brightness;
    color[2][1].white = brightness;
    color[2][2].blue = brightness;
    color[2][2].white = brightness;
    color[2][0].size = 3;
        
    //RED
    color[3][0].red = brightness;
    color[3][0].white = brightness;
    color[3][0].size = 1;
    
    //GREEN
    color[4][0].green = brightness;
    color[4][0].white = brightness;
    color[4][0].size = 1;
    
    //BLUE
    color[5][0].blue = brightness;
    color[5][0].white = brightness;
    color[5][0].size = 1;
    
    //ORANGE
    color[6][0].red = 255;
    color[6][0].green = 100;
    color[6][0].blue = 0;
    color[6][0].white = brightness;
    color[6][0].size = 1;
}

//CALL FUNCTION TO INTERPERT THE COLOR RATE OF CHANGE
color_t LED_interp(color_t* startColor, color_t* stopColor, int colorPeriod, int currentTime) {
    
    color_t colorDifference;
    color_t newColor;
  
    //DIFFERENCE OF START AND END COLOR
    colorDifference.red = ((startColor->red)-(stopColor->red));
    colorDifference.green = ((startColor->green)-(stopColor->green));
    colorDifference.blue = ((startColor->blue)-(stopColor->blue));
    colorDifference.white = ((startColor->white)-(stopColor->white));
        
    //DIFFERENCE MULTIPLIED BY CURRENT TIME, DIVIDED BY PERIOD, ADDED TO STARTING COLOR  
    newColor.red = (startColor->red) + ((colorDifference.red * currentTime)/(-colorPeriod));
    newColor.green = (startColor->green) + ((colorDifference.green * currentTime)/(-colorPeriod));
    newColor.blue = (startColor->blue) + ((colorDifference.blue * currentTime)/(-colorPeriod));
    newColor.white = (startColor->white) + ((colorDifference.white * currentTime)/(-colorPeriod));
    
    //RETURN OFFICIAL COLOR
    return newColor;
}

//CALL TO RUN MAIN LED TASK
void LED_task(colorSet_t setColor, effectSet_t setEffect){
    
    static int currentColorTime, colorCounter, colorDelay, taskDelay;
    static time_t lastTime = 0;
       
    //TASK DELAY TIME
    time_t time = CLOCK_getTime();
    if (time - lastTime < taskDelay)
        return;  
    lastTime = time;
    
    //PERFORM COLOR CALCULATIONS
    color_t newColor = LED_interp(currentColor, nextColor, colorDelay, currentColorTime++);
    
    //SET NEW COLOR
    LED_setColor(&newColor);
    
    //SET EFFECT
    if (setEffect == EFFECT_STEADY){
        colorDelay = 0;
        taskDelay = 0;
    }else if(setEffect == EFFECT_SLOWFADE){
        colorDelay = 150;
        taskDelay = 0;
    }else if(setEffect == EFFECT_MEDIUMFADE){
        colorDelay = 100;
        taskDelay = 0;
    }else if(setEffect == EFFECT_FASTFADE){
        colorDelay = 30;
        taskDelay = 0;
    }else if(setEffect == EFFECT_STROBE){
        colorDelay = 1;
        taskDelay = 1000;
    }
    
    //SELECT NEXT COLOR
    if(currentColorTime>=colorDelay){
        currentColor = nextColor;
        
        //UPDATE COLOR BRIGHTNESS VALUES
        LED_colorMode();
                
        //CHECK COLOR RANGE BOUNDS
        if(colorCounter>=color[setColor][0].size)
            colorCounter = 0;
                
        //ADVANCE TO NEXT COLOR
        nextColor = &color[setColor][colorCounter++];
        
        //RESET BACK TO ZERO
        currentColorTime=0;       
    }
}

//SENDS FINAL COLOR
void LED_setColor(color_t* pColor) {
    CCPR1 = pColor->red;
    CCPR2 = pColor->green;
    CCPR3 = pColor->blue;
    CCPR4 = pColor->white;
}