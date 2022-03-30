/****************************************************
Name: Andrew Bracken 
Date: 3/18/2022
Problem Number: Project 4
Hours spent solving the problem: 12
Instructor: Komogortsev, TSU
*****************************************************/


#include <iostream>
#include <fstream>

#include "tsuPod.h"

using namespace std;

int main() 
{
     
    // Following code initializes the tsuPod 
    initTsuPod(/*add nessesary parameters here*/);


    
    // Following code lists all songs located in tsuPod memeory 
    // The word “empty” indicates empty slot in the playlist 
    // rather than name of the song
    showSongList(/*add nessesary parameters here*/);
    cout << endl;
    


    // Following code tests tsuPod input functionality 
    int retCode = addSong("Runaway1", "Bon Jovi1", 1);
    // testing successful song addition
    retCode = addSong(/*add nessesary parameters here*/
        "Runaway2", "Bon Jovi2", 2);
    showSongList(); // to show that I have added one song
    // I’m adding next six songs successfully 
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway3", "Bon Jovi3", 3);
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway4", "Bon Jovi4", 1);
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway5", "Bon Jovi5", 5);
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway6", "Bon Jovi6", 6);
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway7", "Bon Jovi7", 1);
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway8", "Bon Jovi8", 1);
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway8", "Bon Jovi8", 1);
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway8", "Bon Jovi8", 1);
    showSongList(); //showing that I have added successfully 6 songs
    // testing unsuccessful song addition
    retCode = addSong(/*add nessesary parameters here*/ 
        "Runaway8", "Bon Jovi8", 1);
    cout << retCode 
        << "It was not possible to add songs because memory limit was exceeded" 
        <<endl;   
    showSongList();
    cout << endl;



    // Following code tests tsuPod song removal functionality         
    retCode = removeSong("Runaway100");
    cout << retCode << endl;    
    showSongList();
    cout << endl;



    // Following code tests tsuPod song shuffling functionality      
    shuffle();
    cout << endl;
    showSongList();
    cout << endl;
    
    system("PAUSE");
    
}