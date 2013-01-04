#ifndef SCREENS_H
#define SCREENS_H

#include <glcd.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/fixednums15x31.h>
#include <Time.h>

#include "configuration.h"
#include "openclocktempsensor.h"

//-- Configuration screens:
//-----------------------------------------------
void set_time_screen(volatile unsigned int& encoderPos);

//-- Clock screens:
//------------------------------------------------
void digital_clock( OpenClockTempSensor& temp );
//void analog_clock();
//void binary_clock();

//-- Extra functions:
//------------------------------------------------
//void pomodoro_timer();

#endif // SCREENS_H
