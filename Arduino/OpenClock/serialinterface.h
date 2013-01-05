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

    void serial_interface();

private:
    char buffer[32];
    volatile unsigned int * encoderPos;
    volatile unsigned int prevEncoderPos;

    bool login();

    void read_command();
    void configuration( char * command, int size  =32);
    void interactive_console( char * command, int size = 32 );

    void clearbuffer( int size = 32);
};

#endif // SERIALINTERFACE_H
