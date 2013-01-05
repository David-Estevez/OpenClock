#include "serialinterface.h"

void OpenClockSerial::OpenClockSerial()
{
    clearbuffer();
}

void OpenClockSerial::OpenClockSerial(volatile unsigned int &encoderPos)
{
    clearbuffer();
    this->encoderPos = &encoderPos;
}


void OpenClockSerial::serial_interface()
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
	GLCD.println("Logged correctly!");

	Serial.print( "\n\n");
	Serial.println( MACHINE );

	read_command();

	Serial.println( "Disconected!");
    }

    //-- Close serial port
    Serial.end();
}


bool OpenClockSerial::login()
{
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
	    {
		Serial.println("Wrong!");
		return false;
	    }
	}
    }
    while ( digitalRead( PUSH_SWITCH) == HIGH );

    return false;
}

void OpenClockSerial::read_command()
{
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

	    //-- Decode the instruction:
	    if ( strstr( buffer, "config") != NULL )
	    {
		configuration( buffer );
	    }
	    else if ( strstr(buffer, "interactive" ) != NULL)
	    {
		interactive_console( buffer);
	    }
	    else if ( strstr( buffer, "exit") != NULL )
	    {
		break;
	    }
	}
    }
    while ( digitalRead( PUSH_SWITCH) == HIGH );

}

void OpenClockSerial::configuration( char * command, int size )
{
    GLCD.println( "Remote config");
    while ( digitalRead( PUSH_SWITCH) == HIGH )
    {}
}

void OpenClockSerial::interactive_console( char * command, int size )
{
    int prevEncoderPos = encoderPos;
    
    GLCD.println( "Interactive\nterminal");
    GLCD.ClearScreen();
    GLCD.CursorTo(0,0);

    while(true)
    {
        //-- Command recieved
	if (Serial.available() > 0 )
	{
	    //-- Wait for serial buffer to fill
	    delay(20);

	    //-- Clear buffer
	    clearbuffer( buffer, 32);

	    int j = 0;
	    while ( Serial.available() && j < 31 )
	    {
		buffer[j] = Serial.read();
		j++;
	    }
            
	    Serial.flush();

            if ( strstr( buffer, "!clr") != NULL )
            {
		GLCD.ClearScreen();
		GLCD.CursorTo(0,0);
            }
            else if ( strstr( buffer, "!nl") != NULL )
            {
                GLCD.print('\n');
            }
            else if ( strstr( buffer, "!exit") != NULL )
            {
		break;
            }
	    else
		GLCD.print( buffer );
	}

        //-- Send commands
        if ( encoderPos != prevEncoderPos )
	    Serial.print( encoderPos );

        if ( digitalRead( PUSH_SWITCH ) == LOW)
	{
            Serial.print( "Pressed" );
            delay(20);
	}
    }

}


void OpenClockSerial::clearbuffer( int size)
{
    for (int i = 0; i < size; i++)
	buffer[i] = '\0';
}


