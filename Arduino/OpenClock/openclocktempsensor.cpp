/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Date: Dec 27th, 2012
 */

#include "openclocktempsensor.h"

OpenClockTempSensor::OpenClockTempSensor( const int pin )
{
	this->pin = pin; 
}


double OpenClockTempSensor::getTemp()
{
	//-- Take 5 measures and average them:
	double  sum = 0;
	
	for (int i = 0; i < 5 ; i++)
		sum += calculateTemp( analogRead(pin) );

	return sum / 5.0;
}

double OpenClockTempSensor::calculateTemp( int reading )
{
	return reading *  0.48876 - 50;
}

