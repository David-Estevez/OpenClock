/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Date: Jan 5th, 2013
 */

#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

//-- Arduino Libraries
#include <WProgram.h>
#include <glcd.h>
#include <fonts/SystemFont5x7.h>

//-- Project files
#include "configuration.h"

//-- Definitions
#define BAUD_RATE 9600

#define PASSWORD "!12345678"
#define MACHINE "OpenClock1.0"

//-- Variables


//-- Functions
class OpenClockSerial
{
public:
    OpenClockSerial();
    OpenClockSerial( volatile unsigned int & encoderPos);

    void connectEncoder( volatile unsigned int & encoderPos);

    void run();

private:
    char buffer[32];
    volatile unsigned int * encoderPos;

    bool login();

    void read_commands();
    void configuration();
    void interactive_console();

    void clearbuffer( int size = 32);
    void read_serial();
};

#endif // SERIALINTERFACE_H
