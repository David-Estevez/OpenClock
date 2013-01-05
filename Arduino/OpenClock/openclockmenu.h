/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Date: Jan 4th, 2013
 */

#ifndef OPENCLOCKMENU_H
#define OPENCLOCKMENU_H

#define W_SCREEN_SIZE 21+1
#define H_SCREEN_SIZE 8-2

#include <WProgram.h>
#include <glcd.h>
#include <fonts/SystemFont5x7.h> 

class OpenClockMenu
{
public:
    OpenClockMenu( volatile unsigned int* currentPos);
    OpenClockMenu( glcd& myScreen , volatile unsigned int* currentPos);

    void connectScreen( glcd& myScreen);

    void setTitle(const char * title);
    void addChoice( const char * choice);

    int getNumChoices();

    int show();

private:
    char title[W_SCREEN_SIZE];
    char options[H_SCREEN_SIZE][W_SCREEN_SIZE];

    int numChoices;
    volatile unsigned int * currentChoice;

    glcd* myScreen;


};

#endif // OPENCLOCKMENU_H
