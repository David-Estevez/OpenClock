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
void serial_interface();
bool login();

void clearbuffer( char * buffer, int size);

#endif // SERIALINTERFACE_H
