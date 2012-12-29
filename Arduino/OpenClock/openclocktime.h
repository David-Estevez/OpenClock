/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Date: Dec 27th, 2012
 */

#include <WProgram.h>

class OpenClockTime
{
	public:
		//! \brief Default constructor.
		OpenClockTime();

		//-- Time functions:
		int getHours();
		int getMinutes();
		int getSeconds();

		//-- Date functions:
		int getDay();
		int getMonth();
		int getYear();
};
