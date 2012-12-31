#include "screens.h"

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
