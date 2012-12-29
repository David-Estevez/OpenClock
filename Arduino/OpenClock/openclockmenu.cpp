#include "openclockmenu.h"

OpenClockMenu::OpenClockMenu( volatile unsigned int* currentPos)
{
    numChoices = 0;
    currentChoice = currentPos;
    strcpy( title, "                     ");
    for (int i = 0; i < H_SCREEN_SIZE; i++)
    {
	strcpy( options[i], "                     ");
    }
}

OpenClockMenu::OpenClockMenu(glcd &myScreen, volatile unsigned int* currentPos)
{
    numChoices = 0;
    currentChoice = currentPos;
    strcpy( title, "                     ");
    for (int i = 0; i < H_SCREEN_SIZE; i++)
    {
	strcpy( options[i], "                     ");
    }
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
    //-- Print window title:
    myScreen->ClearScreen();
    myScreen->CursorTo(0,0);
    myScreen->println(title);
    myScreen->println("---------------------");

    for (int i = 0; i < numChoices; i++)
    {
	if( *currentChoice % numChoices == i)
	{
	    myScreen->SetFontColor( WHITE);
	    myScreen->print( "> ");
	    myScreen->println( options[i]);
	    myScreen->SetFontColor( BLACK);
	}
	else
	    myScreen->println( options[i]);
    }
}
