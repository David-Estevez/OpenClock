#include "screens.h"

static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};

void set_time_screen(volatile unsigned int& encoderPos)
{
    int new_time[5] = { hour(), minute() , 1970-year(), month()-1, day()-1 };


    for (int i = 0; i < 5; i++)
    {
	    encoderPos = new_time[i];

	do
	{
	    switch ( i )
	    {
		case 0:
		    new_time[i] = encoderPos % 24;
		    break;
		case 1:
		    new_time[i] = encoderPos % 60;
		    break;
		case 4:
		    new_time[i] = (encoderPos % monthDays[ new_time[3]-1 ])+1;
		    break;
		case 3:
		    new_time[i] = (encoderPos % 12)+1;
		    break;
		case 2:
                    if ( (new_time[i] + encoderPos) < 1970 )
                    {
                      new_time[i] = 1970; 
                      encoderPos = 0;
                    }
                    else
                      new_time[i] = 1970 + encoderPos;

                    break;
	    }

	    GLCD.ClearScreen();
	    GLCD.println("Configure time & date");
	    GLCD.println("---------------------");

	    GLCD.CursorTo(0, 2);
	    GLCD.print("Time: ");
	    for (int j = 0; j < 2; j++)
	    {
		if ( j == i )
		{
		    GLCD.SetFontColor( WHITE );
		    if (new_time[j] < 10)
			GLCD.print( "0");
		    GLCD.print( new_time[j]);
		    GLCD.SetFontColor( BLACK );
		}
		else
		{
		    if (new_time[j]< 10)
			GLCD.print( "0");
		    GLCD.print( new_time[j] );
		}

		GLCD.print( ":" );
	    }

	    GLCD.print( "00" );

	    GLCD.CursorTo(0, 3);
	    GLCD.print("Date: ");
	    for (int j = 4; j >=2; j--)
	    {
		if ( j == i )
		{
		    GLCD.SetFontColor( WHITE );
		    if (new_time[j] < 10)
			GLCD.print( "0");
		    GLCD.print( new_time[j]);
		    GLCD.SetFontColor( BLACK );
		}
		else
		{
		    if (new_time[j] < 10)
			GLCD.print( "0");
		    GLCD.print( new_time[j] );
		}
		if ( j > 2 )
		    GLCD.print( "-" );
	    }

	    //--Debug
	    GLCD.print( "\n");
	    GLCD.print( now() );
	    delay(DELAY);
	}
	while( digitalRead( PUSH_SWITCH) == HIGH );

        //-- Change the time
        setTime(new_time[0], new_time[1], 0, new_time[4],new_time[3],new_time[2]);
    }
}

void digital_clock( OpenClockTempSensor& temp)
{
    //-- Prepare screen:
    GLCD.ClearScreen();

    //-- Print temperature:
    //-----------------------------------
    GLCD.CursorTo(15, 0);
    GLCD.print( temp.getTemp(), 1) ;
    GLCD.println( "C");
    
    //-- Print date:
    //-----------------------------------
    GLCD.CursorToXY(0, 0);
    GLCD.CursorTo(0, 7);
    if (day() < 10)
      GLCD.print("0");
    GLCD.print( day(), DEC );
    
    GLCD.print( "-" );
    if (month() < 10)
      GLCD.print("0");
    GLCD.print( month() , DEC);
    
    GLCD.print( "-" );
    GLCD.print( year() , DEC);
    
    GLCD.print( " ");
    GLCD.print( dayStr( weekday() ));
    
    //-- Time:
    //---------------------------------
    GLCD.SelectFont( fixednums15x31 );
    GLCD.CursorToXY(0,16);
    if (hour() < 10)
      GLCD.print("0");
    GLCD.print( hour(), DEC );
    
    GLCD.print( ":" );
    if (minute() < 10)
      GLCD.print("0");
    GLCD.print( minute() , DEC);
    
    GLCD.print( ":" );
        if (second() < 10)
      GLCD.print("0");
    GLCD.print( second() , DEC);
    GLCD.SelectFont( SystemFont5x7 );
  }
