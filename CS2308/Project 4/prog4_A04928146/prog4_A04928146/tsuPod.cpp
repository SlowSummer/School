/****************************************************
Name: Andrew Bracken
Date: 3/18/2022
Problem Number: Project 4
Hours spent solving the problem: 12
Instructor: Komogortsev, TSU
*****************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "tsuPod.h"

using namespace std;


const int NUM_SONGS = 8;
const int MEMORY_SIZE = 25;

struct TsuPod
{
	string title;
	string artist;
	int size;
};

TsuPod* songList;

int SUM_MEMORY = 0;
int CURRENT_SLOT = 0; //The next empty slot on the list


void initTsuPod()
{
	songList = new TsuPod[NUM_SONGS];
	
	for (int i = 0; i < NUM_SONGS; i++)
	{
		songList[i].title = "Empty";
		songList[i].artist = "Empty";
		songList[i].size = 0;
	}
}


int addSong(string newTitle, string newArtist, int size)
{
	if ((SUM_MEMORY + size) <= MEMORY_SIZE ) //Check for memory space
	{
		if (CURRENT_SLOT < NUM_SONGS) //Checks if there's room on the list
		{
			songList[CURRENT_SLOT].title = newTitle;
			songList[CURRENT_SLOT].artist = newArtist;
			songList[CURRENT_SLOT].size = size;
		
			CURRENT_SLOT++;

			SUM_MEMORY += size;
		}
		else
		{
			return -2; //Returns slot error before memory error
		}
	}
	else
	{
		return -1;
	}


	return 0; //If no error detected
}


int removeSong(string title)
{
	for (int i = 0; i < CURRENT_SLOT; i++)
	{
		if (title == songList[i].title)
		{
			for (i; i < CURRENT_SLOT - 1; i++) //Shuffles the song to the bottom
			{
				TsuPod temp = songList[i];
				songList[i] = songList[i + 1];
				songList[i + 1] = temp;
			} 

			TsuPod& lastSong = songList[CURRENT_SLOT - 1];

			SUM_MEMORY -= lastSong.size;

			lastSong.title = "Empty"; // Clears last slot of list
			lastSong.artist = "Empty";
			lastSong.size = 0;

			CURRENT_SLOT--;

			return 0;
		}
	}

	return -1; //No match found
}


void clearMemory()
{
	delete[] songList; // Clears entire list memory

	initTsuPod(); // Re-initializes the list with all empty slots
}


void showSongList()
{
	for (int i = 0; i < NUM_SONGS; i++)
	{
		if (songList[i].title == "Empty")
		{
			cout << i + 1 << ". "; //Slot#
			cout << "Empty" << endl;
		}
		else
		{
			cout << i + 1 << ". "; //Slot#
			cout << songList[i].title;
			cout << ", " << songList[i].artist;
			cout << ", " << songList[i].size << "MB";
			cout << endl;
		}
	}

	cout << endl;
}


void shuffle()
{
	// Terminates function if less than 2 songs are stored
	if (CURRENT_SLOT < 3) 
	{
		return;
	}

	TsuPod* tempList = new TsuPod[NUM_SONGS];

	for (int i = 0; i < NUM_SONGS; i++) //Stores the list to be shuffled
	{
		tempList[i] = songList[i];
	}

	int usedIndex[NUM_SONGS];

	for (int i = 0; i < CURRENT_SLOT; i++)
	{
		int randNum = rand() % CURRENT_SLOT; //Generates random index
		if (!wasIndexUsed(randNum, usedIndex))
		{
			usedIndex[i] = randNum; //Storing already used index
			
			//Populates list with shuffled songs
			songList[i] = tempList[randNum]; 
		}
		else
		{
			i--; //Goes back to generate an unused index
		}

	}

	delete[] tempList; //Clears up memory
}


bool wasIndexUsed(int currentIndex, int usedIndex[])
{
	for (int i = 0; i < CURRENT_SLOT; i++)
	{
		if (currentIndex == usedIndex[i]) //Checks old used index
		{
			return true;
		}
	}

	return false;
}