/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Date: Dec 27th, 2012
 */

#ifndef OPENCLOCKTEMPSENSOR_H
#define OPENCLOCKTEMPSENSOR_H

#include <WProgram.h>

class OpenClockTempSensor 
{
	public:
	//! \brief  Creates a temperature sensor and assigns it a pin.
	OpenClockTempSensor( const int pin );

	//! \brief Obtain temperature from sensor.
	double getTemp();

	private:
	/*! 	\var int pin
	 *	\brief Stores sensor pin.
	 */
	int pin;
	
	//! \brief Calculate temperature from readings.
	double calculateTemp(int reading);
};

#endif // OPENCLOCKTEMPSENSOR_H
