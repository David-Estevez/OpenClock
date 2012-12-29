/*!
 * OpenClock project
 *
 * Author: David Estévez
 * Date: Dec 29th, 2012
 */

#ifndef OPENCLOCKMENU_H
#define OPENCLOCKMENU_H

#define W_SCREEN_SIZE 21+1
#define H_SCREEN_SIZE 8-2

#include <WProgram.h>
#include <glcd.h>

class OpenClockMenu
{
public:
    OpenClockMenu( const int& currentPos);
    OpenClockMenu( glcd& myScreen , const int& currentPos);

    void connectScreen( glcd& myScreen);

    void setTitle(const char * title);
    void addChoice( const char * choice);

    int show();

private:
    char title[W_SCREEN_SIZE];
    char options[W_SCREEN_SIZE][H_SCREEN_SIZE];

    int numChoices;
    int * currentChoice;

    glcd* myScreen;


};

#endif // OPENCLOCKMENU_H
