#include "openclockmenu.h"

OpenClockMenu::OpenClockMenu(const int &currentPos)
{
    numChoices = 0;
    currentChoice = &currentPos;
}

OpenClockMenu::OpenClockMenu(glcd &myScreen, const int &currentPos)
{
    numChoices = 0;
    currentChoice = &currentPos;
    this->myScreen = &myScreen;
}

void OpenClockMenu::connectScreen( glcd& myScreen)
{
    this->myScreen = &myScreen;
}

void OpenClockMenu::setTitle(const char * title)
{
    strcpy( this->title, title);
}

void OpenClockMenu::addChoice( const char * choice)
{
    if (numChoices < H_SCREEN_SIZE)
    {
	strcpy( options[numChoices], choice);
	numChoices++;
    }
}

int OpenClockMenu::show()
{
    myScreen->ClearScreen();
    myScreen->CursorTo(0,0);
    myScreen->println(title);
    myScreen->println("---------------------");

}
