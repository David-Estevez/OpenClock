#include "serialinterface.h"

void serial_interface()
{
   //-- Start serial port
   Serial.begin( BAUD_RATE);
   Serial.flush();


   //-- Login:
   int i = 0;

   while ( i < 3 && !login())
	i++;

   //-- If logged correctly:
   if ( i < 3 )
   {
       GLCD.ClearScreen();
       GLCD.CursorTo(0,0);
       GLCD.print("Logged correctly!");

       Serial.print( "\n\n");
       Serial.println( MACHINE );
   }

   //-- Close serial port
   Serial.end();
}


bool login()
{
    char buffer[32];

    //-- Display text on screen:
    GLCD.ClearScreen();
    GLCD.CursorTo(0,0);
    GLCD.print("Ready, waiting for\nlogin...");

    //-- Display text on serial:
    Serial.println( "OpenClock Login");
    Serial.print( "Password:");

    //-- Wait for user input, key to abort:
    do
    {
	if (Serial.available() > 0 )
	{
	    //-- Wait for serial buffer to fill
	    delay(20);

	    //-- Clear buffer
	    clearbuffer( buffer, 32);

	    int j = 0;
	    while ( Serial.available() && j < 32 )
	    {
		buffer[j] = Serial.read();
		j++;
	    }

	    Serial.flush();

	    if ( strcmp( buffer, PASSWORD) == 0)
		return true;
	    else
		return false;
	}
    }
    while ( digitalRead( PUSH_SWITCH) == HIGH );

    return false;
}

void clearbuffer( char * buffer, int size)
{
    for (int i = 0; i < size; i++)
	buffer[i] = '\0';
}
