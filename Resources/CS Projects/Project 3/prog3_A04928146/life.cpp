/****************************************************
Name: Andrew Bracken
Date: 3/6/2022
Problem Number: Project 3
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This file provides the implementation of the life.h header file.


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "life.h"

using namespace std;

//GLOBAL VARIABLES

int ROWS = 1;         //stores the number of rows in the grid
int COLUMNS;      //stores the number of rows in the grid
bool** grid;

int** currentGen;
int** nextGen;

//This function reads input file for subsequent prosessing (add high level 
//description of your implementation logic) 
void populateWorld(const char* file)
{
	ifstream inFile;
	inFile.open (file);

	int fileLength = calcGridDim(inFile);

	grid = new bool* [ROWS]; //Declaration of three arrays

	for (int i = 0; i < ROWS; i++)
	{
		grid[i] = new bool [COLUMNS];
	}

	currentGen = new int* [ROWS];
	
	for (int i = 0; i < ROWS; i++)
	{
		currentGen[i] = new int[COLUMNS];
	}

	nextGen = new int* [ROWS];

	for (int i = 0; i < ROWS; i++)
	{
		nextGen[i] = new int[COLUMNS];
	}

	for (int i = 0; i < ROWS; i++) //Reads the first generation from file
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			char temp = inFile.get();
			currentGen[i][j] = atoi(&temp); //Converts input to int
		}
	}

	calcDisplayedCells();
	
	inFile.close();
}

//This function outputs the grid for current generation (add high level 
//description of your implementation logic) 
void showWorld()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (grid[i][j]) //Displays the live cells and dead cells directly around them
			{
				cout << currentGen[i][j];
			}
			else
			{
				cout << " ";
			}
		}

		cout << endl;
	}
}

//This function creats new geneneration grid from the old generation grid
//(add high level description of your implementation logic)
void iterateGeneration()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			int neighbors = countNeighbors(i, j); //Call to calc neighbors of each cell

			//Determines if the cell is alive or dead after iteration
			if (neighbors == 3)
			{
				nextGen[i][j] = 1;
			}
			else if (neighbors < 4 && neighbors > 1)
			{
				nextGen[i][j] = 1;
			}
			if (neighbors > 3)
			{
				nextGen[i][j] = 0;
			}
			if (neighbors <= 1)
			{
				nextGen[i][j] = 0;
			}
		}
	}

	replaceGen();

	calcDisplayedCells(); //Determines which cells actually get displayed
}

//Replaces currentGen with the next iteration
void replaceGen()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			currentGen[i][j] = nextGen[i][j]; //Sets the next generation as the current generation
		}
	}

	clearGen(); //Call to free up the memory of nextGen
}

//Clears memory of nextGen and redifines the dimensions and resets bool grid
void clearGen()
{
	for (int i = 0; i < ROWS; i++) //Clears nextGen
	{
		delete[] nextGen[i];
	}
	delete[] nextGen;

	nextGen = new int* [ROWS];

	for (int i = 0; i < ROWS; i++) //Redifines the array dimensions
	{
		nextGen[i] = new int[COLUMNS];
	}

}

//Calculates which cells will be displayed using the bool** grid
void calcDisplayedCells()
{
	for (int i = 0; i < ROWS; i++) //Resets display bool
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			grid[i][j] = false;
		}
	}

	for (int i = 0; i < ROWS; i++) //Only one layer of dead cells adjacent to living cells
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (currentGen[i][j] == 1)
			{
				grid[i][j] = true;

				//Cells above
				if (isCellValid(i - 1, j - 1))
				{
					grid[i - 1][j - 1] = true;
				}
				if (isCellValid(i - 1, j))
				{
					grid[i - 1][j] = true;
				}
				if (isCellValid(i - 1, j + 1))
				{
					grid[i - 1][j + 1] = true;
				}

				//Same row
				if (isCellValid(i, j - 1))
				{
					grid[i][j - 1] = true;
				}
				if (isCellValid(i, j + 1))
				{
					grid[i][j + 1] = true;
				}

				//Cells below
				if (isCellValid(i + 1, j - 1))
				{
					grid[i + 1][j - 1] = true;
				}
				if (isCellValid(i + 1, j))
				{
					grid[i + 1][j] = true;
				}
				if (isCellValid(i + 1, j + 1))
				{
					grid[i + 1][j + 1] = true;
				}
			}
		}
	}
}

//Counts the neighbors of ecah cell and returns total neighbors
int countNeighbors(int i, int j)
{
	int neighbors = 0;

	if (isCellValid(i + 1, j - 1) && currentGen[i + 1][j - 1] == 1) //South West cell
	{
		neighbors++;
	}
	if (isCellValid(i + 1, j) && currentGen[i + 1][j] == 1) //South cell
	{
		neighbors++;
	}
	if (isCellValid(i + 1, j + 1) && currentGen[i + 1][j + 1] == 1) //South East cell
	{
		neighbors++;
	}


	if (isCellValid(i, j - 1) && currentGen[i][j - 1] == 1) //West cell
	{
		neighbors++;
	}
	if (isCellValid(i, j + 1) && currentGen[i][j + 1] == 1) //East cell
	{
		neighbors++;
	}


	if (isCellValid(i - 1, j - 1) && currentGen[i - 1][j - 1] == 1) //North West cell
	{
		neighbors++;
	}
	if (isCellValid(i - 1, j) && currentGen[i - 1][j] == 1) //North cell
	{
		neighbors++;
	}
	if (isCellValid(i - 1, j + 1) && currentGen[i - 1][j + 1] == 1) //North East cell
	{
		neighbors++;
	}


	return neighbors;
}

//Calculates ROWS and COLUMNS passing the input file as a parameter
int calcGridDim(ifstream& inFile)
{
	int fileLength = 0;

	char currentChar;

	currentChar = inFile.get();

	while (!inFile.eof())
	{

		if (currentChar == '\n')
		{
			ROWS++;
		}
		else
		{
			fileLength++;
		}
		currentChar = inFile.get();
	}

	COLUMNS = fileLength / ROWS;

	inFile.clear();
	inFile.seekg(0, inFile.beg);
	
	return fileLength;
}

//Checks if the index excedes the size of the grid using the current index of the array
//as parameters
bool isCellValid(int rowIndex, int colIndex)
{
	//Row dimension
	if (rowIndex >= ROWS)
	{
		return false;
	}
	if (rowIndex < 0)
	{
		return false;
	}

	//Column dimension
	if (colIndex >= COLUMNS)
	{
		return false;
	}
	if (colIndex < 0)
	{
		return false;
	}

	return true;
}