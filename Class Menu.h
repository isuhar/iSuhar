#include <iostream>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

struct button
	{
		string nameOfButton;
	};

class Menu
{
public:
	Menu(int numberOfButtons, string *namesOfButtons);

	int showMenu(int numberOfbuttons, int *buttonsIDs);
	void showButton(int x, int key, int buttonID);
	int whereY();
	void curs (int x, int y);
private:
	int numberOfButtons;
	button *A;
};

int Menu::showMenu(int numberOfButtonsID, int *buttonsIDs)
{
	if (buttonsIDs)
	{
		int xx = 0;
		for (int i=0; i<numberOfButtonsID; i++)
		{
			this->showButton(xx, i+1,buttonsIDs[i]);
			xx += 15;
		}
	}
	int key;
	do
	{
		key = getch();
	} while((numberOfButtonsID-key) == 48 || (key-48) > numberOfButtonsID || (key-48) < 1 );
	return key;
}

void Menu::showButton(int x, int key, int buttonID)
{
	if (key != 1) curs (x, 3);
	printf("================\n");
	if (key != 1) curs (x, 0);
	printf("|%2d %10s |\n", key, this->A[buttonID].nameOfButton.c_str());
	if (key != 1) curs (x, 0);
	printf("================\n");
}

Menu::Menu(int numberOfButtons, string *namesOfButtons)
{
	this->numberOfButtons = numberOfButtons;
	A = new button[numberOfButtons];
	int i = 0;
	while (i < this->numberOfButtons)
	{
		this->A[i].nameOfButton = namesOfButtons[i];
		i++;
	}
}

int Menu::whereY(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}
void Menu::curs (int x, int y){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos;
	cPos.Y = whereY() - y;
	cPos.X = x;
	SetConsoleCursorPosition(h, cPos);
}