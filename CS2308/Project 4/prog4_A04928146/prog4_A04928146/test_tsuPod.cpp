/****************************************************
Name: Andrew Bracken
Date: 3/18/2022
Problem Number: Project 4
Hours spent solving the problem: 12
Instructor: Komogortsev, TSU
*****************************************************/


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "tsuPod.h"

using namespace std;

int main()
{

    // Following code initializes the tsuPod 
    initTsuPod();


    // Following code lists all songs located in tsuPod memeory 
    // The word “empty” indicates empty slot in the playlist 
    // rather than name of the song
    cout << "Initial empty list:" << endl;
    showSongList();
    cout << endl;



    // Following code tests tsuPod input functionality 
    int retCode = addSong("Runaway1", "Bon Jovi1", 1);


    // testing successful song addition
    retCode = addSong("Runaway2", "Bon Jovi2", 2);
    cout << "Added Runaway1 and Runaway2:" << endl;
    showSongList(); // to show that I have added one song


    // Testing shuffle termination with only 2 songs
    cout << endl;
    cout << "Shouldn't shuffle:" << endl;
    showSongList();
    cout << endl;



    // I’m adding next three songs successfully 
    retCode = addSong("Runaway3", "Bon Jovi3", 3);
    retCode = addSong("Runaway4", "Bon Jovi4", 1);
    retCode = addSong("Runaway5", "Bon Jovi5", 5);

    cout << "Added Runaway3, Runaway4, and Runaway5:";
    cout << endl;
    showSongList(); //showing that I have added successfully 6 songs


    // testing unsuccessful song addition
    retCode = addSong("Runaway6", "Bon Jovi6", 24); // Checks memory error
    if (retCode == -1) //-1 is the returned number for memory errors
    {
        cout << "It was not possible to add songs because memory limit was exceeded";
        cout << endl;
    }
    showSongList();
    cout << endl;

    //Filling empty slots
    retCode = addSong("Runaway6", "Bon Jovi6", 5);
    retCode = addSong("Runaway7", "Bon Jovi7", 3);
    retCode = addSong("Runaway8", "Bon Jovi8", 1);

    // Testing exceeding slot limit
    retCode = addSong("Runaway9", "Bon Jovi9", 1); // Checks slot error
    if (retCode == -2) //-2 is the returned number for slot errors
    {
        cout << "It was not possible to add songs because slot limit was exceeded";
        cout << endl;
    }
    showSongList();  
    cout << endl;



    // Following code tests tsuPod song removal functionality         
    retCode = removeSong("Runaway3");
    cout << "Removed Runaway3:" << endl;
    showSongList(); //Shows the newly compressed list
    cout << endl;

    retCode = removeSong("Runaway3"); // Tests failed song removal
    if (retCode == -1) //-1 is the returned number for failed removal
    {
        cout << "Runaway3 not found";
        cout << endl;
    }
    showSongList();
    cout << endl;


    // Following code tests tsuPod song shuffling functionality      
    shuffle();
    cout << endl;
    cout << "Shuffled list:" << endl;
    showSongList();
    cout << endl;


    // Following code tests memory clearing functionality
    clearMemory();
    cout << "Cleared list:" << endl;

    showSongList(); // Displays the empty list


    system("PAUSE");

}