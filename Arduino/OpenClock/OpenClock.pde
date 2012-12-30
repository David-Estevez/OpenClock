//------------------------------------------------------------------
//-- Time source test
//------------------------------------------------------------------
//-- Testing precision of clocks to decide which one to choose
//------------------------------------------------------------------

//-- Libraries / Includes:
//------------------------------------------------------------------
#include <glcd.h>		      //-- Libraries for Graphic LCD
#include <fonts/allFonts.h>	      //-- Fonts for Graphic LCD
#include <Time.h>		      //-- Internal Clock Library

#include "openclocktempsensor.h"      //-- Temp sensor class
#include "openclockmenu.h"	      //-- GLCD menus

#include "configuration.h"	      //-- Pin definitions, etc
#include "screens.h"		      //-- Different screens for the clock



//-- Encoder variables:
//------------------------------------------------------------------
volatile unsigned int encoderPos = 0;  // a counter for the dial
unsigned int lastReportedPos = 1;   // change management
static boolean rotating=false;      // debounce management

boolean A_set = false;
boolean B_set = false;


//-- Global variables
//-------------------------------------------------------------------
int state = 0;
bool sound_enable = false;
int clock_style = 0;

OpenClockTempSensor temp( TEMP_SENSOR);
OpenClockMenu main_menu( GLCD, &encoderPos);
OpenClockMenu setup_menu(GLCD, &encoderPos);
OpenClockMenu clock_style_menu( GLCD, &encoderPos);


void setup()
{
  //-- Setup of graphic LCD
  //------------------------------------
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  
  //-- Setup of encoder
  //------------------------------------
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  pinMode(PUSH_SWITCH, INPUT);

  digitalWrite(ENC_A, HIGH);         // turn on pullup resistors
  digitalWrite(ENC_B, HIGH);         // turn on pullup resistors
  digitalWrite(PUSH_SWITCH, HIGH);   // turn on pullup resistors


  attachInterrupt(0, doEncoderA, CHANGE);  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(1, doEncoderB, CHANGE);  // encoder pin on interrupt 1 (pin 3)

  //-- Setup of menus
  //-------------------------------------
  //-- Main menu setup
  main_menu.setTitle( "OpenClock - by DEF");
  main_menu.addChoice( "Configuration");
  main_menu.addChoice( "Show clock");

  //-- Setup menu setup
  setup_menu.setTitle("OpenClock Setup");
  setup_menu.addChoice("Setup time and date");
  setup_menu.addChoice("Select clock style");
  setup_menu.addChoice("Toogle sound");
  setup_menu.addChoice("Return");

  //-- Select clock style menu setup
  clock_style_menu.setTitle("Choose clock style:");
  clock_style_menu.addChoice("Digital clock");
  clock_style_menu.addChoice("Return");

/*//-- Setup of Internal Clock
  setTime(DateTime(__DATE__, __TIME__).unixtime());*/
  
}




void loop()
{  
  rotating = true;  // reset the debouncer
  

  //-- State selection
  switch( state)
  {
    case 0:
      //-- Main menu
      state0();
      break;

    case 1:
      //-- Setup menu
      state1();
      break;

    case 2:
      //-- Edit time & date
      state2();
      break;

    case 3:
      //-- Choose clock style
      state3();
      break;

    case 4:
      //-- Show clock
      state4();
      break;

    default:
	//-- Error message
	error();
  }

  delay(DELAY);
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


//-- Error message:
//--------------------------------------------------------
void error()
{
    GLCD.ClearScreen();
    GLCD.CursorTo(0,0);
    GLCD.println( "Unknown Error");
}



//-- State definitions
//-----------------------------------------
void state0()
{
    //--Show main menu
    do
    {
	main_menu.show();
	delay( DELAY);
    }
    while ( digitalRead( PUSH_SWITCH) == HIGH);

    //-- Transitions to other states:
    switch( encoderPos % main_menu.getNumChoices())
    {
	case 0:
	    encoderPos = 0;
	    state = 1;
	    break;

	case 1:
	    encoderPos = 0;
	    state = 4;
	    break;

	default:
	    //-- Error message
	    error();
    }
}


void state1()
{
    //--Show setup menu
    do
    {
	setup_menu.show();
	delay(DELAY);
    }
    while ( digitalRead( PUSH_SWITCH) == HIGH);

    //-- Transitions to other states:
    switch( encoderPos % setup_menu.getNumChoices())
    {
	case 0:
	    encoderPos = 0;
	    state = 2; //-- Setup time & date
	    break;

	case 1:
	    encoderPos = 0;
	    state = 3; //-- Clock style
	    break;

	case 2:
	    sound_enable = !sound_enable; //-- Toggle sound on/off
	    break;

	case 3:
	    encoderPos = 0;
	    state = 0; //-- Main menu
	    break;

	default:
	    //-- Error message
	    error();
    }
}


void state2()
{
      //-- Edit time & date
      GLCD.ClearScreen();
      GLCD.GotoXY(0,0);
      GLCD.println( "Edit time & date screen\nComing soon.");

      while( digitalRead( PUSH_SWITCH) == HIGH )
      {
	  delay(DELAY);
      }

      state = 1; //-- Setup menu
}

void state3()
{
    //-- Choose clock style
    do
    {
	clock_style_menu.show();
	delay(DELAY);
    }
    while( digitalRead( PUSH_SWITCH) == HIGH );

    //-- Transitions to other states:
    switch( encoderPos % clock_style_menu.getNumChoices())
    {
	case 0:
	    clock_style = 0; //-- Digital clock
	    encoderPos = 0;
	    state = 1; //-- Setup menu
	    break;

	default:
	    encoderPos = 0;
	    state = 1; //-- Setup menu
    }
}

void state4()
{
    //-- Show clock
    GLCD.ClearScreen();
    GLCD.GotoXY(0,0);
    GLCD.println( "Show clock\nComing soon.");

    while( digitalRead( PUSH_SWITCH) == HIGH )
    {
	delay(DELAY);
    }

    state = 0; //-- Main menu
}
