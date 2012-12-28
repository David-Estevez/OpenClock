/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Date: Dec 27th, 2012
 */

#include <WProgram.h>

class OpenClockTempSensor 
{
	public:
	//! \brief Default constructor.
	OpenClockTempSensor( const int pin );

	//! \brief Obtain temperature from sensor.
	double getTemp();

	private:
	//! \brief Stores sensor pin.
	int pin;
	
	//! \brief Calculate temperature from readings.
	double calculateTemp(int reading);
};
