// Andrew Bracken
//
// Serial Number / s:
//
// Due Date : 09/18/2023
// Programming Assignment Number 2
// Fall 2023 - CS 3358 - Section 001
//
// Instructor: Husain Gholoom.
//
// Program generates a random vector of integers of size N
// and removes duplicate numbers and sorts the values within.


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;


void PopulateVector(vector<int>&, int);
void DisplayVector(vector<int>);
void NumCount(vector<int>);
void RemoveDup(vector<int>&);
void SortVector(vector<int>&);

int main()
{
	vector<int> v; // random int vector that will be generated

	string sizeStr; //string representing size of the vector
	int size; // int representation of sizeStr
	string userInput; // string representing users choice
					  // 1 - generate array; 9 - exit app

	// seed rand using current time
	srand(time(NULL));

	cout << "Welcome to My Vector APP\n\n";
	cout << "The purpose of this app is to :\n  ";
	cout << "A. generate random numbers between 1 and 5 (inclusive) "
		<< "and stores them in\n     the vector array.\n  ";
	cout << "B. Display the array.\n  ";
	cout << "C. Display the an output in 2 column list. The first  "
		<< "column is a list of the\n\     distinct array elements; "
		<< "the second column is the count of the number of\n     "
		<< "occurrences of each element. The list should be sorted on "
		<< "entries in the\n     first column, largest to smallest.\n  ";
	cout << "D. Remove the repeated numbers from vector array and display "
		<< "the array.\n  ";
	cout << "E. Sort the vector array in an ascending order from lowest to "
		<< "highest. Diplay\n     the sorted vector array.\n\n";

	while (userInput != "9")
	{
		cout << "Select one of the follow:\n\n";
		cout << "\t1 - Generate the Array.\n";
		cout << "\t9 - Exit the App.\n\n";
		cout << "Enter Your Choice: ";

		getline (cin, userInput);

		cout << "\n\n";

		if (userInput == "1")
		{
			cout << "Enter the size of the array : ";


			getline(cin, sizeStr);

			cout << "\n\n";

			size = stoi(sizeStr); // convert sizeStr to int

			if (size > 30) //check if size is within range
			{
				cout << "Invalid. Size must be <= 30\n\n\n";
			}
			else
			{
				PopulateVector(v, size);

				RemoveDup(v);

				SortVector(v);

				v.clear(); // clear for next loop
			}
		}
		else if (userInput == "9")
		{
			cout << "\n\n\n\n";
			cout << "Thanks for Using the Vector APP.\n";
			cout << "Andrew Bracken \n9 - 18 - 2023\n";

			return 0;
		}
		else
		{
			cout << "Invalid Selection\n\n\n";
		}
	}

	return 0;
}

void PopulateVector(vector<int> &v, int size)
{
	for (int i = 0; i < size; i++)
	{
		v.push_back(rand() % 5 + 1);
	}

	cout << "The generated array is: \n\n\n";

	DisplayVector(v);
	NumCount(v);
}

void DisplayVector(vector<int> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}

	cout << "\n\n\n";
}

void NumCount(vector<int> v)
{
	int oneCount = 0; // int itterator to track the count of each num
	int twoCount = 0; // int itterator to track the count of each num
	int threeCount = 0; // int itterator to track the count of each num
	int fourCount = 0; // int itterator to track the count of each num
	int fiveCount = 0; // int itterator to track the count of each num

	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i) == 1)
		{
			oneCount++;
		}
		else if (v.at(i) == 2)
		{
			twoCount++;
		}
		else if (v.at(i) == 3)
		{
			threeCount++;
		}
		else if (v.at(i) == 4)
		{
			fourCount++;
		}
		else if (v.at(i) == 5)
		{
			fiveCount++;
		}
	}

	cout << "Number \t Count\n";

	if (fiveCount > 0)
	{
		cout << "5\t " << fiveCount << endl;
	}

	if (fourCount > 0)
	{
		cout << "4\t " << fourCount << endl;
	}

	if (threeCount > 0)
	{
		cout << "3\t " << threeCount << endl;
	}

	if (twoCount > 0)
	{
		cout << "2\t " << twoCount << endl;
	}

	if (oneCount > 0)
	{
		cout << "1\t " << oneCount << endl;
	}

	cout << "\n\n";
}

void RemoveDup(vector<int>& v)
{
	bool one = false; // bool to track if num has occured
	bool two = false; // bool to track if num has occured
	bool three = false; // bool to track if num has occured
	bool four = false; // bool to track if num has occured
	bool five = false; // bool to track if num has occured

	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i) == 1)
		{
			if (!one)
			{
				one = true; // first occurance of num
			}
			else
			{
				v.erase(v.begin() + i);
				i--; // accomadate the shifting of remaining elem
			}
		}
		else if (v.at(i) == 2)
		{
			if (!two)
			{
				two = true; // first occurance of num
			}
			else
			{
				v.erase(v.begin() + i);
				i--; // accomadate the shifting of remaining elem
			}
		}
		else if (v.at(i) == 3)
		{
			if (!three)
			{
				three = true; // first occurance of num
			}
			else
			{
				v.erase(v.begin() + i);
				i--; // accomadate the shifting of remaining elem
			}
		}
		else if (v.at(i) == 4)
		{
			if (!four)
			{
				four = true; // first occurance of num
			}
			else
			{
				v.erase(v.begin() + i);
				i--; // accomadate the shifting of remaining elem
			}
		}
		else if (v.at(i) == 5)
		{
			if (!five)
			{
				five = true; // first occurance of num
			}
			else
			{
				v.erase(v.begin() + i);
				i--; // accomadate the shifting of remaining elem
			}
		}
	}

	cout << "Array after removing repeated elements;\n\n\n";

	DisplayVector(v);
}

void SortVector(vector<int>& v)
{
	int temp; // temp integer used for swaping

	for (int i = 0; i < v.size() - 1; i++)
	{
		for (int j = i + 1; j <= v.size() - 1; j++)
		{
			if (v.at(i) > v.at(j))
			{
				temp = v.at(i);
				v.at(i) = v[j];
				v[j] = temp;
			}
		}
	}

	cout << "Sorted array:\n\n\n";

	DisplayVector(v);

	cout << "\n\n";
}
