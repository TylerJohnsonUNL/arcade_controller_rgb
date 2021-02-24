#include "mcc_generated_files/mcc.h"
#include "clock.h"
#include "led.h"
#include "sensor.h"
#include "spi.h"
#include "sevenSegment.h"
#include "button.h"
#include "controller.h"
#include "mode.h"

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    CLOCK_init();
    LED_init();
    SENSOR_init();
    SPI_Init();
    BUTTONS_init();
    SEVENSEGMENT_init();
    CONTROLLER_init();
    
    while (1){
        BUTTONS_task();
        CONTROLLER_task();
        SENSOR_check();
        if (MOVEMENT_detected()){
            MODE_task(CONTROLLER_currentMode());            
        }else{
            MODE_task(0);
        }
        
    }
}
/**
 End of File
*/