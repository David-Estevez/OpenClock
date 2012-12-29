//------------------------------------------------------------------
//-- Time source test
//------------------------------------------------------------------
//-- Testing precision of clocks to decide which one to choose
//------------------------------------------------------------------

//-- Libraries for Graphic LCD
#include <glcd.h>
#include <fonts/allFonts.h>
#include "openclocktempsensor.h"
#include "openclockmenu.h"

/*
//-- Libraries for RTC
#include <Wire.h>
#include <RTClib.h>*/

//-- Libraries for internal clock
#include <Time.h>


//-- Pin definitions
//------------------------------------------------------------------
#define ENC_A 2          //-- Encoder pin A
#define ENC_B 3          //-- Encoder pin B

#define PUSH_SWITCH 4   //-- Encoder push switch

//-- Encoder variables:
//------------------------------------------------------------------
volatile unsigned int encoderPos = 0;  // a counter for the dial
unsigned int lastReportedPos = 1;   // change management
static boolean rotating=false;      // debounce management

boolean A_set = false;
boolean B_set = false;

//-- General clock definitions
//-------------------------------------------------------------------
#define NUM_STATES 4

/*
//-- RTC clock
//-------------------------------------------------------------------
RTC_DS1307 RTC;*/

//-- Global variables
//-------------------------------------------------------------------
int state = 0;

OpenClockTempSensor temp(A5);

void setup()
{
  //-- Setup of graphic LCD
  //------------------------------------
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  
  //-- Setup of encoder
  //------------------------------------
   pinMode(ENC_A, INPUT);
   digitalWrite(ENC_A, HIGH);   // turn on pullup resistors

   pinMode(ENC_B, INPUT);
   digitalWrite(ENC_B, HIGH);   // turn on pullup resistors

   pinMode(PUSH_SWITCH, INPUT);
   digitalWrite(PUSH_SWITCH, HIGH);   // turn on pullup resistors

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

/*
  //-- Setup of RTC
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  //-- Setup of Internal Clock
  setTime(DateTime(__DATE__, __TIME__).unixtime());*/

  
}



void loop()
{  
  rotating = true;  // reset the debouncer
  
    OpenClockMenu menu( GLCD, &encoderPos);
    menu.setTitle( "Init screen");
    menu.addChoice( "Option 1");
    menu.addChoice( "Option 2");
    for (int i = 0; i < 600; i++)
    {

  menu.show();
  delay(100);
    }
  //-- Menu screen state selection
  if (state == 0)
    state0();
  if (state == 1)
    state1();
  if (state == 2)
    state2();
  if (state == 3)
    state3();
    
  delay(200);
  
  if ( digitalRead( PUSH_SWITCH) == LOW )  {
    state = 0;
    delay(200);
  }
}


//-- Menu screens:
//-----------------------------------------
void state0()
{
    bool flag = true;
    
    while (flag)
    {
      //-- Display a simple menu
      GLCD.ClearScreen();
      GLCD.CursorTo(0,0);
      GLCD.print("Select source\n");
      GLCD.print("-------------\n");
      
      if (encoderPos % (NUM_STATES-1) == 0)
      {
        //-- First option is selected
        GLCD.SetFontColor( WHITE);
        GLCD.print("> RTC\n");
        GLCD.SetFontColor(BLACK);
        GLCD.print("Internal Clock\n");
        GLCD.print("Both");
      }
      
      if (encoderPos % (NUM_STATES-1) == 1)
      {
        //-- Second choice is selected
        
        GLCD.print("RTC\n");
        GLCD.SetFontColor( WHITE);
        GLCD.print("> Internal clock\n");
        GLCD.SetFontColor(BLACK);
        GLCD.print("Both");
      }
    
      if (encoderPos % (NUM_STATES-1) == 2)
      {
        //-- Second choice is selected
        
        GLCD.print("RTC\n");
        GLCD.print("Internal clock\n");
        GLCD.SetFontColor( WHITE);
        GLCD.print("> Both");
        GLCD.SetFontColor(BLACK);
      }
      
      if ( digitalRead( PUSH_SWITCH) == LOW)
      {
        flag = false;
	state = 1 + (encoderPos % (NUM_STATES-1));
      }
      
      delay(200);    
    }
}


void state1()
{
    //-- Header
    GLCD.ClearScreen();
    GLCD.CursorTo(0,0);
    GLCD.print("Source: Temp \n");
    GLCD.print("-----------------\n");
    
    //int reading= analogRead(A5);
    // double temp = reading*0.488758553-50;
    // GLCD.println( reading);
    // GLCD.print( temp);
     GLCD.print( temp.getTemp() );
     delay(100);
     while (  digitalRead( PUSH_SWITCH) == LOW)
     {
     tone( 5, 440, 5);
     delay(250);
      tone( 5, 440, 5);
      delay(250);
     }

    /*
    //-- Get the time
    DateTime now = RTC.now();
    
    //-- Print time
    if (now.hour() < 10)
      GLCD.print("0");
    GLCD.print(now.hour(), DEC);
    GLCD.print(':');
    
    if (now.minute() < 10)
      GLCD.print("0");
    GLCD.print(now.minute(), DEC);
    GLCD.print(':');
    
    if (now.second() < 10)
      GLCD.print("0");
    GLCD.print(now.second(), DEC);
    GLCD.print('\n');
    
    //-- Print date
    GLCD.print(now.day(), DEC);
    GLCD.print('/');
    GLCD.print(now.month(), DEC);
    GLCD.print('/');
    GLCD.print(now.year(), DEC);
    
    */
    
    delay(200);
}


void state2()
{
    //-- Header
    GLCD.ClearScreen();
    GLCD.CursorTo(0,0);
    GLCD.print("Source:Internal Clock\n");
    GLCD.print("-----------------\n");
    
    //-- Print time
    if (hour() < 10)
      GLCD.print("0");
    GLCD.print(hour(), DEC);
    GLCD.print(':');
    
    if (minute() < 10)
      GLCD.print("0");
    GLCD.print(minute(), DEC);
    GLCD.print(':');
    
    if (second() < 10)
      GLCD.print("0");
    GLCD.print(second(), DEC);
    GLCD.print('\n');
    
    //-- Print date
    GLCD.print(day(), DEC);
    GLCD.print('/');
    GLCD.print(month(), DEC);
    GLCD.print('/');
    GLCD.print(year(), DEC);
      
    delay(200);
}

void state3()
{
    //-- Header
    GLCD.ClearScreen();
    GLCD.CursorTo(0,0);
    GLCD.print("Source: Both \n");
    GLCD.print("-----------------\n");
    /*
    //-- RTC stuff
    //--------------------------------
    
    //-- Get the time
    DateTime now = RTC.now();
    
    //-- Print time
    GLCD.print("RTC ");
    
    if (now.hour() < 10)
      GLCD.print("0");
    GLCD.print(now.hour(), DEC);
    GLCD.print(':');
    
    if (now.minute() < 10)
      GLCD.print("0");
    GLCD.print(now.minute(), DEC);
    GLCD.print(':');
    
    if (now.second() < 10)
      GLCD.print("0");
    GLCD.print(now.second(), DEC);
    GLCD.print(' ');
    
    //-- Print date
    GLCD.print(now.day(), DEC);
    GLCD.print('/');
    GLCD.print(now.month(), DEC);
    GLCD.print('/');
    GLCD.print(now.year(), DEC);
    
*/
        
    //-- Internal clock stuff
    //-- Print time 
    GLCD.print("\nIC  ");
        
    if (hour() < 10)
      GLCD.print("0");
    GLCD.print(hour(), DEC);
    GLCD.print(':');
    
    if (minute() < 10)
      GLCD.print("0");
    GLCD.print(minute(), DEC);
    GLCD.print(':');
    
    if (second() < 10)
      GLCD.print("0");
    GLCD.print(second(), DEC);
    GLCD.print(' ');
    
    //-- Print date
    GLCD.print(day(), DEC);
    GLCD.print('/');
    GLCD.print(month(), DEC);
    GLCD.print('/');
    GLCD.print(year(), DEC);    
    
    delay(200);
}


//--Interrupt functions
//----------------------------------------------------

// Interrupt on A changing state
void doEncoderA(){
  // debounce
  if ( rotating ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change?
  if( digitalRead(ENC_A) != A_set ) {  // debounce once more
    A_set = !A_set;

    // adjust counter + if A leads B
    if ( A_set && !B_set )
      encoderPos += 1;

    rotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doEncoderB(){
  if ( rotating ) delay (1);
  if( digitalRead(ENC_B) != B_set ) {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if( B_set && !A_set )
      encoderPos -= 1;

    rotating = false;
  }
}
