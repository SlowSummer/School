/****************************************************
Name: Andrew Bracke
Date: 3/18/2022
Problem Number: Project 4
Hours spent solving the problem: 12
Instructor: Komogortsev, TSU
*****************************************************/

#ifndef tsuPod_h
#define tsuPod_h

#include <string>

using namespace std;


////////////////////////////////
/* FUNCTION - void initTsuPod

 Initialize all the slots to blank and 0 size memory

input parms - N/A

 output parms - N/A
*/
void initTsuPod();



///////////////////////////////
/* FUNCTION - int addSong
 * attempts to add a new song to the tsuPod
          o returns a 0 if successful
          o returns -1 if not enough memory to add the song
          o returns -2 for any other error

 input parms - 
    o newTitle: title of the newly added song
    o newArtist: name of the artist of the song
    o size: size of file in MB

 output parms -
    o returns a 0 if successful
    o returns -1 if not enough memory to add the song
    o returns -2 for any other error
*/
int addSong(string newTitle, string newArtist, int size);




////////////////////////////
/* FUNCTION - int removeSong
    * attempts to remove a song from the tsuPod
          o returns 0 if successful
          o returns -1 if nothing is removed


input parms - title: the tittle of the song being removed

output parms - 0 if successful, -1 if nothing removed
*/
int removeSong(string title);





////////////////////////////
/* FUNCTION - void clearMemory
* clears all the songs from memory

input parms - N/A

output parms - N/A
*/
void clearMemory();




/////////////////////////////
/* FUNCTION - void showSongList
    * prints the current list of songs in order from first to last to standard output
    * format - slot #, Title, Artist, size in MB (one song per line)
    * print "Empty" for any slots that do not contain a song

input parms - N/A

output parms - N/A
*/
void showSongList();



////////////////////////////
/* FUNCTION - void shuffle
    *  shuffles the songs into random order
          o will do nothing if there are less than two songs in the current list

input parms - N/A

output parms - N/A
*/
void shuffle();


////////////////////////////
/* FUNCTION - bool wasIndexUsed
    *  determines if random index has been used or not

input parms - 
    o int currentIndex: the index being checked
    o int usedIndex[]: were used indecise are stored

output parms - 
    o bool:
        o true if the index has been used
        o false if it hasn't been used
*/
bool wasIndexUsed(int currentIndex, int usedIndex[]);

#endif