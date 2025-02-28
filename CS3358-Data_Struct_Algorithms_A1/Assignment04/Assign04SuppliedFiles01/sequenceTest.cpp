// FILE: sequenceTest.cpp
// An interactive test program for the sequence class

#include <cctype>      // provides toupper
#include <iostream>    // provides std::cout and cin
#include <cstdlib>     // provides EXIT_SUCCESS
#include "sequence.h"
namespace seqOfNum  = CS3358_SP2023_A04_sequenceOfNum;
namespace seqOfChar = CS3358_SP2023_A04_sequenceOfChar;
using namespace std;

// PROTOTYPES for functions used by this test program:

void print_menu();
// Pre:  (none)
// Post: A menu of choices for this program is written to std::cout.
char get_user_command();
// Pre:  (none)
// Post: The user is prompted to enter a one character command.
//       The next character is read (skipping blanks and newline
//       characters), and this character is returned.
void show_list(seqOfNum::sequence<double> src);
// Pre: (none)
// Post: The items of src are printed to std::cout (one per line).
void show_list(seqOfChar::sequence<char> src);
// Pre: (none)
// Post: The items of src are printed to std::cout (one per line).
int get_object_num();
// Pre:  (none)
// Post: The user is prompted to enter either 1 or 2. The
//       prompt is repeated until a valid integer can be read
//       and the integer's value is either 1 or 2. The valid
//       integer read is returned. The input buffer is cleared
//       of any extra input until and including the first
//       newline character.
double get_number();
// Pre:  (none)
// Post: The user is prompted to enter a real number. The prompt
//       is repeated until a valid real number can be read. The
//       valid real number read is returned. The input buffer is
//       cleared of any extra input until and including the
//       first newline character.
char get_character();
// Pre:  (none)
// Post: The user is prompted to enter a non-whitespace character.
//       The prompt is repeated until a non-whitespace character
//       can be read. The non-whitespace character read is returned.
//       The input buffer is cleared of any extra input until and
//       including the first newline character.

int main(int argc, char *argv[])
{
   seqOfNum::sequence<double> s1;  // A sequence of double for testing
   seqOfChar::sequence<char> s2; // A sequence of char for testing
   int objectNum;    // A number to indicate selection of s1 or s2
   double numHold;   // Holder for a real number
   char charHold;    // Holder for a character
   char choice;      // A command character entered by the user

   std::cout << "An empty sequence of real numbers (s1) and\n"
        << "an empty sequence of characters (s2) have been created."
        << endl;

   do
   {
      if (argc == 1)
         print_menu();
      choice = toupper( get_user_command() );
      switch (choice)
      {
         case '!':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               s1.start();
               std::cout << "s1 started" << endl;
            }
            else
            {
               s2.start();
               std::cout << "s2 started" << endl;
            }
            break;
         case '&':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               s1.end();
               std::cout << "s1 ended" << endl;
            }
            else
            {
               s2.end();
               std::cout << "s2 ended" << endl;
            }
            break;
         case '+':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               if ( ! s1.is_item() )
                  std::cout << "Can't advance s1." << endl;
               else
               {
                  s1.advance();
                  std::cout << "Advanced s1 one item."<< endl;
               }
            }
            else
            {
               if ( ! s2.is_item() )
                  std::cout << "Can't advance s2." << endl;
               else
               {
                  s2.advance();
                  std::cout << "Advanced s2 one item."<< endl;
               }
            }
            break;
         case '-':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               if ( ! s1.is_item() )
                  std::cout << "Can't move back s1." << endl;
               else
               {
                  s1.move_back();
                  std::cout << "Moved s1 back one item."<< endl;
               }
            }
            else
            {
               if ( ! s2.is_item() )
                  std::cout << "Can't move back s2." << endl;
               else
               {
                  s2.move_back();
                  std::cout << "Moved s2 back one item."<< endl;
               }
            }
            break;
         case '?':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               if ( s1.is_item() )
                  std::cout << "s1 has a current item." << endl;
               else
                  std::cout << "s1 has no current item." << endl;
            }
            else
            {
               if ( s2.is_item() )
                  std::cout << "s2 has a current item." << endl;
               else
                  std::cout << "s2 has no current item." << endl;
            }
            break;
         case 'C':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               if ( s1.is_item() )
                  std::cout << "Current item in s1 is: "
                       << s1.current() << endl;
               else
                  std::cout << "s1 has no current item." << endl;
            }
            else
            {
               if ( s2.is_item() )
                  std::cout << "Current item in s2 is: "
                       << s2.current() << endl;
               else
                  std::cout << "s2 has no current item." << endl;
            }
            break;
         case 'P':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               if (s1.size() > 0)
               {
                  std::cout << "s1: ";
                  show_list(s1);
                  std::cout << endl;
               }
               else
                  std::cout << "s1 is empty." << endl;
            }
            else
            {
               if (s2.size() > 0)
               {
                  std::cout << "s2: ";
                  show_list(s2);
                  std::cout << endl;
               }
               else
                  std::cout << "s2 is empty." << endl;
            }
            break;
         case 'S':
            objectNum = get_object_num();
            if (objectNum == 1)
               std::cout << "Size of s1 is: " << s1.size() << endl;
            else
               std::cout << "Size of s2 is: " << s2.size() << endl;
            break;
         case 'A':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               numHold = get_number();
               s1.add(numHold);
               std::cout << numHold << " added to s1." << endl;
            }
            else
            {
               charHold = get_character();
               s2.add(charHold);
               std::cout << charHold << " added to s2." << endl;
            }
            break;
         case 'R':
            objectNum = get_object_num();
            if (objectNum == 1)
            {
               if ( s1.is_item() )
               {
                  numHold = s1.current();
                  s1.remove_current();
                  std::cout << numHold << " removed from s1." << endl;
               }
               else
                  std::cout << "s1 has no current item." << endl;
            }
            else
            {
               if ( s2.is_item() )
               {
                  charHold = s2.current();
                  s2.remove_current();
                  std::cout << charHold << " removed from s2." << endl;
               }
               else
                  std::cout << "s2 has no current item." << endl;
            }
            break;
         case 'Q':
            std::cout << "Quit option selected...bye" << endl;
            break;
         default:
            std::cout << choice << " is invalid...try again" << endl;
      }
   }
   while (choice != 'Q');

   cin.ignore(999, '\n');
   std::cout << "Press Enter or Return when ready...";
   cin.get();
   return EXIT_SUCCESS;
}

void print_menu()
{
   std::cout << endl;
   std::cout << "The following choices are available:\n";
   std::cout << "  !  Activate the start() function\n";
   std::cout << "  &  Activate the end() function\n";
   std::cout << "  +  Activate the advance() function\n";
   std::cout << "  -  Activate the move_back() function\n";
   std::cout << "  ?  Print the result from the is_item() function\n";
   std::cout << "  C  Print the result from the current() function\n";
   std::cout << "  P  Print a copy of the entire sequence\n";
   std::cout << "  S  Print the result from the size() function\n";
   std::cout << "  A  Add a new item with the add(...) function\n";
   std::cout << "  R  Activate the remove_current() function\n";
   std::cout << "  Q  Quit this test program" << endl;
}

char get_user_command()
{
   char command;

   std::cout << "Enter choice: ";
   cin >> command;

   std::cout << "You entered ";
   std::cout << command << endl;
   return command;
}

void show_list(seqOfNum::sequence<double> src)
{
   for ( src.start(); src.is_item(); src.advance() )
      std::cout << src.current() << "  ";
}

void show_list(seqOfChar::sequence<char> src)
{
   for ( src.start(); src.is_item(); src.advance() )
      std::cout << src.current() << "  ";
}

int get_object_num()
{
   int result;

   std::cout << "Enter object # (1 = s1, 2 = s2) ";
   cin  >> result;
   while ( ! cin.good() )
   {
      cerr << "Invalid integer input..." << endl;
      cin.clear();
      cin.ignore(999, '\n');
      std::cout << "Re-enter object # (1 = s1, 2 = s2) ";
      cin  >> result;
   }
   // cin.ignore(999, '\n');

   while (result != 1 && result != 2)
   {
      cin.ignore(999, '\n');
      cerr << "Invalid object # (must be 1 or 2)..." << endl;
      std::cout << "Re-enter object # (1 = s1, 2 = s2) ";
      cin  >> result;
      while ( ! cin.good() )
      {
         cerr << "Invalid integer input..." << endl;
         cin.clear();
         cin.ignore(999, '\n');
         std::cout << "Re-enter object # (1 = s1, 2 = s2) ";
         cin  >> result;
      }
      // cin.ignore(999, '\n');
   }

   std::cout << "You entered ";
   std::cout << result << endl;
   return result;
}

double get_number()
{
   double result;

   std::cout << "Enter a real number: ";
   cin  >> result;
   while ( ! cin.good() )
   {
      cerr << "Invalid real number input..." << endl;
      cin.clear();
      cin.ignore(999, '\n');
      std::cout << "Re-enter a real number ";
      cin  >> result;
   }
   // cin.ignore(999, '\n');

   std::cout << "You entered ";
   std::cout << result << endl;
   return result;
}

char get_character()
{
   char result;

   std::cout << "Enter a non-whitespace character: ";
   cin  >> result;
   while ( ! cin )
   {
      cerr << "Invalid non-whitespace character input..." << endl;
      cin.ignore(999, '\n');
      std::cout << "Re-enter a non-whitespace character: ";
      cin  >> result;
   }
   // cin.ignore(999, '\n');

   std::cout << "You entered ";
   std::cout << result << endl;
   return result;
}
