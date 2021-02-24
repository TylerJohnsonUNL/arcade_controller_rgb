#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include "mcc_generated_files/mcc.h"
#include "button.h"
#include "clock.h"
#include "sevenSegment.h"
#include "led.h"

void CONTROLLER_init();

//INCREMENTS THE ADDRESS AND UPDATES DISPLAY
void CONTROLLER_inc();

//INCREMENTS THE ADDRESS AND UPDATES THE DISPLAY
void CONTROLLER_heldInc();

//RESTARTS MOMENTUM
void CONTROLLER_restart_momentum();

//CALL TO RUN MAIN CONTROLLER TASK
void CONTROLLER_task();

//CALL TO RETURNS CURRENT MODE
uint8_t CONTROLLER_currentMode();

#endif /* CONTROLLER_H */
