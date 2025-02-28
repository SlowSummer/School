/****************************************************
Name: Andrew Bracken
Date: 3/6/2022
Problem Number: Project 3
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This header file provides the prototypes of the function definitions
//for the project.

#ifndef life_h
#define life_h

#include <iostream>
#include <fstream>

using namespace std;

void populateWorld(const char * file);
void showWorld();
void iterateGeneration();
void clearGen();
void calcDisplayedCells();
void replaceGen();

int countNeighbors(int i, int j);
bool isCellValid(int rowIndex, int colIndex);
int calcGridDim(ifstream& inFile);
#endif
