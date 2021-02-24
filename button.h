#ifndef BUTTON_H
#define	BUTTON_H

#include "mcc_generated_files/mcc.h"
#include "clock.h"

#define HOLD_TIME  100
#define BUTTON_COUNT 1
#define BUTTON_SCAN_INTERVAL 10

typedef enum {
    EVENT_IDLE,
    EVENT_PRESSED,
    EVENT_HOLD
} event_t;

typedef enum {
    STATE_UNPRESSED,
    STATE_PRESSED,
    STATE_HELD
} btnState_t;

typedef struct {
    volatile uint8_t* port;
    uint8_t pin;
    btnState_t state;
    btnState_t lastState;
    event_t event;
    uint16_t timeHeld;
} button_t;

extern button_t *increase;

void BUTTONS_task();

void BUTTONS_init();

static void init(button_t* btn, volatile uint8_t* port, uint8_t pin);

bool BUTTONS_isClicked(button_t* button);

bool BUTTONS_isHeld (button_t* button);


#endif	/* BUTTON_H */