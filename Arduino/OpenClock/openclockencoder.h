/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Based on playground.arduino.cc code about encoders
 * Date: Dec 27th, 2012
 */

#ifndef OPENCLOCKENCODER_H
#define OPENCLOCKENCODER_H

#include <WProgram.h>

class OpenClockEncoder
{
public:
    /*!
     * \brief Creates an Encoder from its pins and the push button pin
     *
     * \param pinA Interrupt pin A.
     * \param pinB Interrupt pin B.
     * \param pushButtonPin Push button pin.
     */
    OpenClockEncoder(int pinA, int pinB, int pushButtonPin);

    int getPos();
    bool pushed();

 private:
    /*! \var int pinA
     *  \brief Interrupt pin A.
     */
    int pinA;

    /*! \var int pinB
     *  \brief Interrupt pin B.
     */

    int pinB;

    /*! \var int pushButtonPin
     *  \brief Interrupt pin A.
     */
    int pushButtonPin;

    //-- Other variables:
    volatile unsigned int encoderPos;  // a counter for the dial
    unsigned int lastReportedPos;   // change management
    static boolean rotating;      // debounce management

    boolean A_set, B_set;

    //--Interrupt functions
    //----------------------------------------------------
public:
    // Interrupt on A changing state
    void doEncoderA();
    // Interrupt on B changing state, same as A above
    void doEncoderB();

private:
    //! \brief Private default constructor.
    OpenClockEncoder();

};

#endif // OPENCLOCKENCODER_H
