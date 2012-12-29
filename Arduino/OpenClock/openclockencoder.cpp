#include "openclockencoder.h"

OpenClockEncoder::OpenClockEncoder(int pinA, int pinB, int pushButtonPin)
{
    //-- Setting variables:
    this->pinA = pinA;
    this->pinB = pinB;
    this->pushButtonPin = pushButtonPin;

    encoderPos = 0;
    lastReportedPos = 1;
    rotating=false;

    A_set = false;
    B_set = false;

    pinMode(this->pinA, INPUT);
    digitalWrite(this->pinA, HIGH);   // turn on pullup resistors

    pinMode(this->pinB, INPUT);
    digitalWrite(this->pinB, HIGH);   // turn on pullup resistors

    pinMode(this->pushButtonPin, INPUT);
    digitalWrite(this->pushButtonPin, HIGH);   // turn on pullup resistors

/*
    // encoder pin on interrupt 0 (pin 2)
    attachInterrupt(0, doEncoderA, CHANGE);
    //encoder pin on interrupt 1 (pin 3)
    attachInterrupt(1, doEncoderB, CHANGE);
*/
}

int OpenClockEncoder::getPos()
{
    return encoderPos;
}

bool OpenClockEncoder::pushed()
{
    return !digitalRead( pushButtonPin );
}

//--Interrupt functions
//----------------------------------------------------

// Interrupt on A changing state
void OpenClockEncoder::doEncoderA(){
  // debounce
  if ( rotating ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change?
  if( digitalRead(pinA) != A_set ) {  // debounce once more
    A_set = !A_set;

    // adjust counter + if A leads B
    if ( A_set && !B_set )
      encoderPos += 1;

    rotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void OpenClockEncoder::doEncoderB(){
  if ( rotating ) delay (1);
  if( digitalRead(pinB) != B_set ) {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if( B_set && !A_set )
      encoderPos -= 1;

    rotating = false;
  }
}
