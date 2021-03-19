// Part 4 of the Battleships Project
// Written by Luca J. Ricagni
// Student Number: 200894968

#include <iostream>
#include <string>

using namespace std;

// Declare length/width of square board
#define boardSize 8

// Initialise functions
bool DisplayStartMenu();
void GetCoordinates(int &column, int &row);
bool CheckXCoord(char xCoord);
bool CheckYCoord(char yCoord);
int GetDirection();
bool CheckDirection(char direction);
void EnterToContinue();
int CoordinateToInt(char coord);
void IncrementDirection(int direction, int &xCoord, int &yCoord);

enum ShipType 
{
	Carrier,
	Battleship,
	Cruiser,
	Submarine,
	Destroyer
} shipType;

enum Direction
{
	North,
	East,
	South,
	West,
	invalid
} directionEnum;


class Board
{
private:
	// Declare game boards
	char gameBoardShipPlacement[boardSize][boardSize];
	char gameBoardShots[boardSize][boardSize];
	
public:
	
	// Constructor
	Board()
	{
		
	}
	
	void DisplayBoardPlacing() 
	{
	
		cout << "   A--B--C--D--E--F--G--H " << endl;
		
		for (int i = 0;i < boardSize;i++) 
		{
			cout << "-------------------------- " << endl;
			cout << i+1 << "|";
			for (int j = 0;j < boardSize;j++) 
			{
				if (gameBoardShipPlacement[i][j] != 'E') 
				{
					cout << " " << gameBoardShipPlacement[i][j] << " ";
				} else 
				{
					cout << "   ";
				}
			}
			cout << endl;
		}
	}
	
	void DisplayBoardFiring() 
	{
	
		cout << "   A--B--C--D--E--F--G--H " << endl;
		
		for (int i = 0;i < boardSize;i++) 
		{
			cout << "-------------------------- " << endl;
			cout << i+1 << "|";
			for (int j = 0;j < boardSize;j++) 
			{
				if (gameBoardShots[i][j] != 'E') 
				{
					cout << " " << gameBoardShots[i][j] << " ";
				} else 
				{
					cout << "   ";
				}
			}
			cout << endl;
		}
	}
	
	char GetSquareState(int row, int column)
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
	
	bool PlaceShip(int column, int row, int direction, int size)
	{
		
		for (int i = 0;i < size;i++)
		{
			gameBoardShipPlacement[row][column] = 'S';
			IncrementDirection(direction, column, row);
		}
		return true;		
	}
	
	
	bool FireAtSquare(int column, int row) 
	{
		bool validShot = false;
		
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
			validShot = true;
			
		} 
		else
		{
			cout << "You already shot there! Please try again." << endl;
		}
		
		return validShot;
	}
	
	
	bool PlacementCheck(int column, int row, int direction, int size)
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
	
	void Setup()
	{
		// Populate the boards
		for (int i = 0;i < boardSize;i++) 
		{
			for (int j = 0;j < boardSize;j++) 
			{
				gameBoardShipPlacement[i][j] = 'E';
				gameBoardShots[i][j] = 'E';
			}
		}
	}
	
	// Function to check if board has any squares with a ship left
	bool ShipLeft()
	{
		for (int i = 0;i < boardSize;i++) 
		{
			for (int j = 0;j < boardSize;j++) 
			{
				if (GetSquareState(i, j) == 'S')
				{
					return true;
				}
			}
		}
		return false;
	}
	
	// ResetBoard - Function to reset board (set all squares to empty)
	
	
};


class Player
{
private:
	string name;
	// instance of Board
	Board board;
	
	
public:

	// Constructor
	Player()
	{
		
	}
	
	void SetName(string name) 
	{
		this->name = name;
	}
	
	string GetName() 
	{
		return name;
	}
	
	bool Fire(int column, int row)
	{
		return board.FireAtSquare(column, row);
	}
	
	
	void PlaceShip(int column, int row, int direction, int size) 
	{
		board.PlaceShip(column, row, direction, size);
	}

	void DisplayBoard(int &turnNumber, bool firingBoard) 
	{
		cout << "Turn: " << turnNumber << endl;
		if(firingBoard == true)
		{
			board.DisplayBoardFiring();
		} else
		{
			board.DisplayBoardPlacing();
		}
		cout << endl;
	}
	
	bool CheckLost()
	{
		if (board.ShipLeft() == true)
		{
			return false;
		} else 
		{
			return true;
		}
	}
	
	bool PlacementCheck(int column, int row, int direction, int size)
	{
		return board.PlacementCheck(column, row, direction, size);
	}
	
	void Setup()
	{
		board.Setup();
		
	}
};


int main(){
	std::cout << "\x1b[2J\x1b[H" << std::flush; // Clear the terminal
	
	int turnNumber = 1;

	
	Player players[2];
	
	players[0].Setup();
	players[1].Setup();
	
	string name;
	
	const int playerCount = 2;

	if (DisplayStartMenu() == false)
	{
		return 0;
	}
	else
	{
		for(int p = 0; p < playerCount;p++)
		{
			cout << "Enter player name:" << endl;
			cin >> name;
		
			players[p].SetName(name);
			
			EnterToContinue();
			
			cout << "Player " << p+1 << " name is: " << players[p].GetName() << endl;
			
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
			
			int row, column, direction;
			
			int size;
			int type;
				
			for (int i = 0; i < 5; i++)
			{
				switch (i)
				{
					case Carrier:
						size = 5;
						type = Carrier;
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
				
				while(true)
				{
					players[p].DisplayBoard(turnNumber, false);
					
					GetCoordinates(column, row);
					direction = GetDirection();
					
					
					//valid location check
					if (players[p].PlacementCheck(column, row, direction, size))
					{
						
						
						players[p].PlaceShip(column, row, direction, size);
						
						break;
					}
					else
					{
						cout << "Invalid entry! Please try again" << endl;
					}
				}
				
				EnterToContinue();
				
				// Only place one ship each to speed up testing
				/*if (i == 0)
				{
					break;
				}*/
			}
		}
		
		// Print both boards after setup
		// cout << "Player 1s board looks like this: " << endl;
		//players[0].DisplayBoard(turnNumber);
		// cout << "Player 2s board looks like this: " << endl;
		//players[1].DisplayBoard(turnNumber);
		
		// Declare pointer and point it to player 1
		Player *currentPlayer = &players[0];
		
		// Declare pointer and point it to player 2
		Player *targetPlayer = &players[1];
		
		bool flip = false;
		int column, row;
		while (true)
		{
			// print game board
			targetPlayer->DisplayBoard(turnNumber, true);
			
			// shoot
			cout << currentPlayer->GetName() << " enter coordinates to fire" << endl;
			
			while (true)
			{
				GetCoordinates(column, row);
				
				if (targetPlayer->Fire(column, row))
				{
					EnterToContinue();
					break;
				}
				
			}
			
			// check if player won
			if (targetPlayer->CheckLost() == true)
			{
				//display lost
				cout << currentPlayer->GetName() << " has won!" << endl;
				targetPlayer->DisplayBoard(turnNumber, true);
				return 0;
			}

			// swap pointers
			swap(currentPlayer, targetPlayer);

			if (flip)
			{
				// increment turn number
				turnNumber++;
			}	

			flip = !flip;			
			
		}
	}	
	
	return 0;
}


void EnterToContinue(){
	cout<<"Press enter to continue!";
	cin.clear(); //clears the stream
	cin.ignore(50,'\n'); //ignores next line(enter)
	cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work
	std::cout << "\x1b[2J\x1b[H" << std::flush; // Clear the terminal
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

void IncrementDirection(int direction, int &xCoord, int &yCoord)
{
	switch (direction) 
	{
		case 0:
			yCoord--; // North
			break;
		case 1:
			xCoord++; // East
			break;
		case 2:
			yCoord++; // South
			break;
		case 3:
			xCoord--; // West
			break;
	}
}

int DirectionToInt(char direction)
{
	int result;
	switch (direction) 
	{
		case 'N':
			result = 0; // North
			break;
		case 'E':
			result = 1; // East
			break;
		case 'S':
			result = 2; // South
			break;
		case 'W':
			result = 3; // West
			break;
		default:
			result = 999; // Invalid
			break;
	}
	
	return result;
}

int GetDirection() 
{
	// Get a direction
	char direction;
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
	
	return DirectionToInt(direction);
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

void GetCoordinates(int &column, int &row) 
{
	char x, y;
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
	
	column = CoordinateToInt(x);
	row = CoordinateToInt(y);
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













