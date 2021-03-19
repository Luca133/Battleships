// Part 1 of the Battleships Project
// Written by Luca J. Ricagni
// Student Number: 200894968

#include <iostream>
using namespace std;

// Initialise functions
void startMenu();
char getPlayerName();
void takeShot(char playerName);
bool checkXCoord(char xCoord);
bool checkYCoord(char yCoord);


int main(){
	std::cout << "\x1b[2J\x1b[H" << std::flush; // Clear the terminal
	
	startMenu();
	
	return 0;
}

void startMenu() {
	// Display start menu
	cout << "-------------------------------------" << endl;
	cout << "          Battleships                " << endl;
	cout << "          Main Menu                  " << endl;
	cout << "-------------------------------------" << endl;
	cout << "          1. Start Game              " << endl;
	cout << "          2. Exit Game               " << endl;
	
	char playerName;
	
	// Ask user for start menu input until a valid input is given
	// When "1. Start Game" is selected get a player name
	do {
		char charSelected;
		cout << "Enter menu selection(1-2):" << endl;
		cin >> charSelected;
	
		if (charSelected == '1') {
			playerName = getPlayerName();
			break;
		
		} else if (charSelected == '2') {
			// Exit the game
			cout << "Goodbye!" << endl;
			return;
		} else {
			// Ask for another input from the user
			cout << "Invalid entry! Please try again." << endl;
		}
	}
	while (true);
	
	// Play game (to be done to take multiple shots/turns)
	takeShot(playerName); // Take a single shot
	
}

char getPlayerName() {
	char playerName;
	cout << "Enter player name (single character):" << endl;
	cin >> playerName;
	
	return playerName;

}

bool checkXCoord(char xCoord)
{
	switch (xCoord)
	{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
			return true;
		default:
			return false;
	}
}

bool checkYCoord(char yCoord)
{
	switch (yCoord)
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			return true;
		default:
			return false;
	}
}

void takeShot(char playerName)
{
	cout << "Player " << playerName << " enter coordinates to fire" << endl;
	// Get x coordinate for shot
	char xCoord;
	do
	{
		cout << "Enter the x coordinate (A-H)" << endl;
		cin >> xCoord;
	
		if (checkXCoord(xCoord))
		{
			break;
		}
		else
		{
			cout << "Invalid entry! Please try again." << endl;
		}
	} while (true);
	
	// Get y coordinate for shot
	char yCoord;
	
	do
	{
		cout << "Enter the y coordinate (1-8)" << endl;
		cin >> yCoord;
	
		if (checkYCoord(yCoord))
		{
			break;
		}
		else
		{
			cout << "Invalid entry! Please try again." << endl;
		}
	} while (true);
	
	// Display selected coords
	cout << "You entered the coordinates x:" << xCoord << " and y:" << yCoord << endl;
}
