#ifndef SPI_H
#define	SPI_H

#include "mcc_generated_files/mcc.h"
#include "clock.h"
#include "sevenSegment.h"

void SPI_Init();

void SPI_Write(uint8_t outputValue);

#endif	/* SENSOR_H */