// Author /s : Andrew Bracken
//
// Due Date : 10/27/2023
//
// Programming Assignment Number 5
//
// Fall 2023 - CS 3358 - Your Section Number
//
// Instructor: Husain Gholoom.
//
// Program generates an array of size n and uses recursive
// functions to preform various tasks

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

void populateArray(int [], int);
void display(int[], int);
void reverseArray(int [], int, int);
void squares(int, int);
int digitSum(int);
bool primeCheck(int, int);

bool getUserChoice(int&);


int main()
{
	srand(time(NULL)); // seed rand

	int n; // user inputed array size
	int sum; // int used as the return of digitSum()

	cout << "***   Welcome to My Recursion APP  ***\n\n";

	if (getUserChoice(n))
	{
		int userArray[n];

		populateArray(userArray, n);

		display(userArray, n);

		cout << "Reversed Array is : ";

		reverseArray(userArray, n, 0);

		cout << "\n\n";

		cout << "Table of Square Values From 1 to " << n
			<< " is :\n\n\nN\tN Squared\n";

		squares(n, 1);

		cout << "\n\n\n";

		cout << "Sum of " << userArray[n - 1] << " digits is : ";

		sum = digitSum(userArray[n - 1]);

		cout << sum << "\n\n\n";

		cout << "Is " << userArray[0] << " a Prime Number : ";

		if (primeCheck(userArray[0], 2))
		{
			cout << userArray[0] << " is a prime number.";
		}
		else
		{
			cout << userArray[0] << " is not a prime number.";
		}

		cout << "\n\n\n\n";

	}

	cout << "Andrew Bracken - Tweak Programming Director\n"
		<< "October 2023\n";

	return 0;
}

void populateArray(int userArray[], int n)
{
	for (int i = 0; i < n; i++)
	{
		userArray[i] = rand() % 5797 + 100; // rand 100-5896
	}
}

void display(int userArray[], int n)
{
	cout << "The Generated Array is : ";

	for (int i = 0; i < n; i++)
	{
		cout << userArray[i] << " ";
	}

	cout << "\n\n";
}

void reverseArray(int userArray[], int n, int i)
{
	if (i == n)
	{
		return;
	}
	else
	{
		reverseArray(userArray, n, i + 1);

		cout << userArray[i] << " ";
	}
}

void squares(int n, int i)
{
	if (i == n)
	{
		cout << i << "\t" << i * i << endl;
		return;
	}
	else
	{
		cout << i << "\t" << i * i << endl;
		squares(n, i + 1);
	}
}

int digitSum(int temp)
{
	if (temp == 0)
	{
		return 0;
	}

	return (temp % 10 + digitSum(temp / 10));
}

bool primeCheck(int temp, int i)
{
	if (temp <= 3) // base case
	{
		return true;
	}

	if (temp % i == 0)
	{
		return false;
	}

	if (i * i > temp)
	{
		return true;
	}

	return primeCheck(temp, i + 1);
}

bool getUserChoice(int& n)
{
	cout << "Enter Array Size. (Must be >= 5) -->  ";
	cin >> n;
	cout << "\n";

	if (!cin.good() || n < 5)
	{
		cout << "Invalid Array Size. Size must >= 5.\n\n";

		return false;
	}

	return true;
}
