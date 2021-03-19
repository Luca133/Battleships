// Part 2 of the Battleships Project
// Written by Luca J. Ricagni
// Student Number: 200894968

#include <iostream>
using namespace std;

// Initialise functions
bool displayStartMenu();
void getCoordinates(char &x, char &y);
bool checkXCoord(char xCoord);
bool checkYCoord(char yCoord);
char getPlayerName();
void addShip();
void getDirection(char &direction);
bool checkDirection(char direction);
void displayBoardState(int &turnNumber);
void playerFire(char playerName);
void enterToContinue();

int main(){
	std::cout << "\x1b[2J\x1b[H" << std::flush; // Clear the terminal
	
	char player1;
	int turnNumber = 1;
	
	if (displayStartMenu() == false)
	{
		return 0;
	}
	else
	{
		player1 = getPlayerName();
		cout << "Player 1 name is: " << player1 << endl;
		
		addShip();
		
		do {
			displayBoardState(turnNumber);
			
			playerFire(player1);
			
			turnNumber++;
		} while (true);
	}
	
	
	
	
	
	
	
	return 0;
}

void enterToContinue(){
	cout<<"Press enter to continue!";
	cin.clear(); //clears the stream
	cin.ignore(50,'\n'); //ignores next line(enter)
	cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work
	std::cout << "\x1b[2J\x1b[H" << std::flush; // Clear the terminal
}

void playerFire(char playerName) {
	
	cout << "Player " << playerName << " enter coordinates to fire" << endl;
	
	char x, y;
	getCoordinates(x, y);
	
	cout << "You fired at X: " << x << " and Y: " << y << endl;
	
	enterToContinue();
}


void displayBoardState(int &turnNumber) {
	cout << "Turn: " << turnNumber << endl;
	cout << "Displaying the current board state!" << endl;
	cout << endl;
}


void addShip() {
	
	// Display add ship menu
	cout << "----------------------------- " << endl;
	cout << "          Add Ship            " << endl;
	cout << "------------------------------" << endl;
	cout << "        No Name      Squares  " << endl;
	cout << "------------------------------" << endl;
	cout << "        1  Carrier      5     " << endl;
	cout << "        1  Battleship   4     " << endl;
	cout << "        2  Cruiser      3     " << endl;
	cout << "        1  Submarine    3     " << endl;
	cout << "        1  Destroyer    2     " << endl;
	cout << "------------------------------" << endl;
	
	for (int i = 1; i <= 5; i++)
	{
		cout << "Adding ship " << i << " of 5" << endl;
		
		char x, y, direction;
		
		getCoordinates(x, y);
		
		getDirection(direction);
		
		cout << "You added a ship to x: " << x << " and y: " << y << " Direction: " << direction << endl;
	}
	
	enterToContinue();
}


void getDirection(char &direction) {
	// Get a direction
	do
	{
		cout << "Enter the direction (N/E/S/W): " << endl;
		cin >> direction;
	
		if (checkDirection(direction))
		{
			break;
		}
		else
		{
			cout << "Invalid entry! Please try again." << endl;
		}
	} while (true);
}


bool checkDirection(char direction)
{
	switch (direction)
	{
		case 'N':
		case 'E':
		case 'S':
		case 'W':
			return true;
		default:
			return false;
	}
}


bool displayStartMenu() {
	// Display start menu
	cout << "------------------------------" << endl;
	cout << "          Battleships         " << endl;
	cout << "          Main Menu           " << endl;
	cout << "------------------------------" << endl;
	cout << "          1. Start Game       " << endl;
	cout << "          2. Exit Game        " << endl;
	
	
	// Ask user for start menu input until a valid input is given
	// When "1. Start Game" is selected get a player name
	do {
		char charSelected;
		cout << "Enter menu selection(1-2):" << endl;
		cin >> charSelected;
	
		if (charSelected == '1') {
			// Play the game
			enterToContinue();
			return true;
		
		} else if (charSelected == '2') {
			// Exit the game
			cout << "Goodbye!" << endl;
			return false;
		} else {
			// Ask for another input from the user
			cout << "Invalid entry! Please try again." << endl;
		}
	}
	while (true);
	

	
}

void getCoordinates(char &x, char &y) {
	
	// Get x coordinate for shot
	do
	{
		cout << "Enter the x coordinate (A-H)" << endl;
		cin >> x;
	
		if (checkXCoord(x))
		{
			break;
		}
		else
		{
			cout << "Invalid entry! Please try again." << endl;
		}
	} while (true);
	
	// Get y coordinate for shot
	do
	{
		cout << "Enter the y coordinate (1-8)" << endl;
		cin >> y;
	
		if (checkYCoord(y))
		{
			break;
		}
		else
		{
			cout << "Invalid entry! Please try again." << endl;
		}
	} while (true);
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


char getPlayerName() {
	char playerName;
	cout << "Enter player name (single character):" << endl;
	cin >> playerName;
	
	enterToContinue();
	
	return playerName;

}











