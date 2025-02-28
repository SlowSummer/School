/****************************************************
Name:Andrew Bracken
Date: 3/6/2022
Problem Number: Project 3
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

// This is driver's code


#ifdef linux 
#define LINUX true
#define WINDOWS false
#endif

#ifdef __CYGWIN32__
#define LINUX false 
#define WINDOWS true
#endif

#define WINDOWS true

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>

#include "life.h"

//const char FILE_NAME[] = "glider_gun_fight.txt";
const char FILE_NAME[] = "Text.txt";


using namespace std;

const int NUM_GENERATIONS = 10; //set to a smaller number for debugging

int main() 
{
    populateWorld(FILE_NAME);
        
    showWorld();

    for (int iteration = 0; iteration < NUM_GENERATIONS; iteration++) 
    {

        if (WINDOWS)
        	system("cmd.exe /c cls"); //Windows only
        else
           system("clear"); //Linux only
        iterateGeneration();
        showWorld();
    } 
	//char * c = "Hello";  //I could not figure out what this line does and it was constantly causing compiler errors
    if (WINDOWS)
        system("cmd.exe /c PAUSE");
    return 0;
}
