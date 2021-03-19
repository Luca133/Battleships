// Part 3 of the Battleships Project
// Written by Luca J. Ricagni
// Student Number: 200894968

#include <iostream>
#include <string>
using namespace std;

// Declare length/width of square board
#define boardSize 8

// Declare game boards
char gameBoardShipPlacement[boardSize][boardSize];
char gameBoardShots[boardSize][boardSize];
//char gameBoardShipSize[boardSize][boardSize];

string playerName1;
	

// Initialise functions
bool DisplayStartMenu();
void GetCoordinates(char &x, char &y);
bool CheckXCoord(char xCoord);
bool CheckYCoord(char yCoord);
void GetPlayerName();
void AddShip();
void GetDirection(char &direction);
bool CheckDirection(char direction);
void DisplayBoardState(int &turnNumber);
void PlayerFire();
void EnterToContinue();
void DisplayBoardPlacing();
void DisplayBoardFiring();
void PlaceShip(int number, int type, int size);
int CoordinateToInt(char coord);
void IncrementDirection(char direction, int &xCoord, int &yCoord);
bool PlacementCheck(int x, int y, char direction, int size);
bool CheckWin();
char GetSqaureState(int row, int column);

enum ShipType 
{
	Carrier,
	Battleship,
	Cruiser,
	Submarine,
	Destroyer
} shipType;

class Ship 
{
	public:
	
	int x;
	int y;
	char direction;
	int size;
	int type;

	Ship() 
	{
	}
	
	Ship(int x, int y, char direction, int size, int type) 
	{
		x = x;
		y = y;
		direction = direction;
		size = size;
		type = type;
	}
};

// Declare array of ship objects
Ship ships[5];

int main(){
	std::cout << "\x1b[2J\x1b[H" << std::flush; // Clear the terminal
	
	int turnNumber = 1;

	// Populate the boards
	for (int i = 0;i < boardSize;i++) {
		for (int j = 0;j < boardSize;j++) {
			gameBoardShipPlacement[i][j] = 'E';
			gameBoardShots[i][j] = 'E';
			//gameBoardShipType[i][j] = 'E';
		}
	}
	

	if (DisplayStartMenu() == false)
	{
		return 0;
	}
	else
	{
		GetPlayerName();
		cout << "Player 1 name is: " << playerName1 << endl;
		
		AddShip();
		
		while (!CheckWin())
		{
			DisplayBoardState(turnNumber);
			
			PlayerFire();
			
			turnNumber++;
			
			
			// Code to show that GetSqaureState function works but is not currently used
			//cout << "State of Square A1 is: " << GetSqaureState(0, 0) << endl;
			//cout << "State of Square A2 is: " << GetSqaureState(0, 1) << endl;
			//cout << "State of Square F6 is: " << GetSqaureState(5, 5) << endl;
		}
	}	
	
	return 0;
}

char GetSqaureState(int row, int column)
{
	char boardState = gameBoardShipPlacement[row][column];
	char shotState = gameBoardShots[row][column];
	if (boardState == 'E')
	{
		return shotState;
	}
	else //Ship
	{
		if (shotState == 'H')
		{
			return shotState;
		}
		else
		{
			return boardState;
		}
	}
}

bool CheckWin()
{
	for (int i = 0;i < boardSize;i++) {
		for (int j = 0;j < boardSize;j++) {
			if (gameBoardShipPlacement[i][j] == 'S' && gameBoardShots[i][j] != 'H')
			{
				return false;
			}
		}
	}
	cout << "You won!" << endl;
	return true;
}

void DisplayBoardPlacing() {
	
	cout << "   A--B--C--D--E--F--G--H " << endl;
	
	for (int i = 0;i < boardSize;i++) {
		cout << "-------------------------- " << endl;
		cout << i+1 << "|";
		for (int j = 0;j < boardSize;j++) {
			if (gameBoardShipPlacement[i][j] != 'E') {
				cout << " " << gameBoardShipPlacement[i][j] << " ";
			} else {
				cout << "   ";
			}
		}
		cout << endl;
	}
}

void DisplayBoardFiring() {
	
	cout << "   A--B--C--D--E--F--G--H " << endl;
	
	for (int i = 0;i < boardSize;i++) {
		cout << "-------------------------- " << endl;
		cout << i+1 << "|";
		for (int j = 0;j < boardSize;j++) {
			if (gameBoardShots[i][j] != 'E') {
				cout << " " << gameBoardShots[i][j] << " ";
			} else {
				cout << "   ";
			}
		}
		cout << endl;
	}
}

void EnterToContinue(){
	cout<<"Press enter to continue!";
	cin.clear(); //clears the stream
	cin.ignore(50,'\n'); //ignores next line(enter)
	cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work
	std::cout << "\x1b[2J\x1b[H" << std::flush; // Clear the terminal
}

void PlayerFire() {
	
	cout << "Player " << playerName1 << " enter coordinates to fire" << endl;
	
	// Get firing coordinates
	char x, y;
	GetCoordinates(x, y);
	
	int column = CoordinateToInt(x);
	int row = CoordinateToInt(y);
	
	// Check shot hasn't been fired at coordinates before
	if (gameBoardShots[row][column] == 'E')
	{
		// Check if hit or miss
		if (gameBoardShipPlacement[row][column] == 'S')
		{
			cout << "It's a hit!" << endl;
			gameBoardShots[row][column] = 'H';
		} 
		else
		{
			cout << "It's a miss!" << endl;
			gameBoardShots[row][column] = 'M';
		}
	} 
	else
	{
		cout << "You already shot there!" << endl;
	}
	
	EnterToContinue();
}


void DisplayBoardState(int &turnNumber) 
{
	cout << "Turn: " << turnNumber << endl;
	DisplayBoardFiring();
	cout << endl;
}


void AddShip() 
{
	
	// Display add ship menu
	cout << "----------------------------- " << endl;
	cout << "          Add Ship            " << endl;
	cout << "------------------------------" << endl;
	cout << "        No Name      Squares  " << endl;
	cout << "------------------------------" << endl;
	cout << "        1  Carrier      5     " << endl;
	cout << "        1  Battleship   4     " << endl;
	cout << "        1  Cruiser      3     " << endl;
	cout << "        1  Submarine    3     " << endl;
	cout << "        1  Destroyer    2     " << endl;
	cout << "------------------------------" << endl;
	
	char x;
	char y;
	char direction;
	int size;
	int type;
		
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
			case Carrier:
				size = 5;
				type = Carrier;
				cout << "Adding Carrier " << endl;
				cout << "Adding a Carrier size: " << size << endl;
				break;
				
			case Battleship:
				size = 4;
				type = Battleship;
				cout << "Adding a Battleship size: " << size << endl;
				break;
			
			case Cruiser:
				size = 3;
				type = Cruiser;
				cout << "Adding a Cruiser size: " << size << endl;
				break;
			
			case Submarine:
				size = 3;
				type = Submarine;
				cout << "Adding a Submarine size: " << size << endl;
				break;
			
			case Destroyer:
				size = 2;
				type = Destroyer;
				cout << "Adding a Destroyer size: " << size << endl;
				break;
			
		}
		
		PlaceShip(i, type, size);
		DisplayBoardPlacing();
	}
	cout << "All ships have been placed!" << endl;
	EnterToContinue();
}

int CoordinateToInt(char coord)
{
	switch (coord)
	{
		case 'A': 
		case '1':
			return 0;
		case 'B':
		case '2':
			return 1;
		case 'C':
		case '3':
			return 2;
		case 'D':
		case '4':
			return 3;
		case 'E':
		case '5':
			return 4;
		case 'F': 
		case '6':
			return 5;
		case 'G':
		case '7':
			return 6;
		case 'H':
		case '8':
			return 7;
		default:
			return 99; // Error
	}
}

void IncrementDirection(char direction, int &xCoord, int &yCoord)
{
	switch (direction) 
	{
		case 'N':
			yCoord--;
			break;
		case 'E':
			xCoord++;
			break;
		case 'S':
			yCoord++;
			break;
		case 'W':
			xCoord--;
			break;
	}
}

bool PlacementCheck(int column, int row, char direction, int size)
{
	for (int i = 0; i < size;i++)
	{
		if (gameBoardShipPlacement[row][column] != 'E' || column < 0 || column > 8 || row < 0 || row > 8)
		{
			return false;
		}
		
		IncrementDirection(direction, column, row);
	}
	
	return true;
}

void PlaceShip(int number, int type, int size)
{
	char x;
	char y;
	char direction;
	
	int column;
	int row;
	
	while(true)
	{
		GetCoordinates(x, y);
		
		column = CoordinateToInt(x);
		row = CoordinateToInt(y);
			
		GetDirection(direction);
		//valid location check
		if (PlacementCheck(column, row, direction, size))
		{
			ships[number] = Ship(column, row, direction, size, type);
			
			for (int i = 0;i < size;i++)
			{
				gameBoardShipPlacement[row][column] = 'S';
				IncrementDirection(direction, column, row);
			}
			
			return;
		}
		else
		{
			cout << "Invalid entry! Please try again" << endl;
		}
	}
}

void GetDirection(char &direction) 
{
	// Get a direction
	do
	{
		cout << "Enter the direction (N/E/S/W): " << endl;
		cin >> direction;
	
		if (CheckDirection(direction))
		{
			break;
		}
		else
		{
			cout << "Invalid entry! Please try again." << endl;
		}
	} while (true);
}

bool CheckDirection(char direction)
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

bool DisplayStartMenu() 
{
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
		//cin.clear();
	
		if (charSelected == '1') {
			// Play the game
			EnterToContinue();
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

void GetCoordinates(char &x, char &y) 
{
	
	// Get x coordinate for shot
	do
	{
		cout << "Enter the x coordinate (A-H)" << endl;
		cin >> x;
	
		if (CheckXCoord(x))
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
	
		if (CheckYCoord(y))
		{
			break;
		}
		else
		{
			cout << "Invalid entry! Please try again." << endl;
		}
	} while (true);
}

bool CheckXCoord(char xCoord)
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

bool CheckYCoord(char yCoord)
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

void GetPlayerName() 
{
	cout << "Enter player name:" << endl;
	cin >> playerName1;
	
	EnterToContinue();
}











