// Author : Andrew Bracken
//
// Serial number :
//
// Due Date : 09/29/2023
// Programming Assignment Number 3
// Fall 2023 - CS 3358 - 001
//
// Instructor: Husain Gholoom.
//
// Implement a class with a single integer attribute that can find the
// factors, square root, sum of the digits, and if the integer is a 
// multiple of 7, 11, or 13.


#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

class myInt
{
private:
	int value;

public:
	myInt();
	void setValue(int x)
	{
		this->value = x;
	}
	void sumDigits();
	void squareRoot();
	void factorCheck();
	void primeNum();
	void perfectNum();
};


void checkUserInput(string&);
bool checkUserInt(string, int&);


int main()
{
	string userInput = "Y"; // char representing user's input
						  // Y or y to continue
						  // N or n to exit
	string userInt; // string representing user's integer
	int strInt; // int representing user's integer converted from string

	myInt x; // users object of class myInt

	cout << "Welcome to my Integer Manipulation Program.\n\n\n";

	while (userInput != "n" && userInput != "N")
	{
		cout << "Enter an Integer: ";
		getline(cin, userInt);
		cout << "\n\n";

		if (checkUserInt(userInt, strInt))
		{
			x.setValue(strInt); // update value

			x.factorCheck();

			x.sumDigits();

			x.squareRoot();

			x.primeNum();

			x.perfectNum();
		}

		cout << "Would you like to re-run the program again\n";
		cout << "Enter Y or N --->  ";
		getline(cin, userInput);
		cout << "\n\n";

		checkUserInput(userInput);
	}

	return 0;
}

void checkUserInput(string &userInput)
{
	bool properInput = false; // bool representing if userInput is a proper response

	while (!properInput)
	{
		if (userInput != "y" && userInput != "Y")
		{
			if (userInput != "n" && userInput != "N")
			{
				cout << "Error*** Invalid choice - Must enter y|Y or n|N\n\n\n";
			}
			else // userInput == n || N
			{
				cout << "\n\n\nThis program is implemented by Andrew Bracken\n";
				cout << "September - 2023";
				return;
			}
		}
		else // userInput == y || Y
		{
			return;
		}

		cout << "Would you like to re-run the program again\n";
		cout << "Enter Y or N --->  ";
		getline(cin, userInput);
		cout << "\n\n";

	}
}

bool checkUserInt(string x, int &userInt)
{
	for (int i = 0; i < x.size(); i++) // check if all of x is digits
	{
		if (!isdigit(x[i]))
		{
			cout << "Error*** -Must enter an integer that is >= 100\n\n";
			return false;
		}
	}
	
	userInt = stoi(x); //convert to int

	if (userInt < 100)
	{
		cout << "Error*** -Integer must be >=100\n\n";
		return false;
	}

	return true;
}

myInt::myInt()
{
	value = 0;
}

void myInt::factorCheck()
{
	if (this->value % 7 == 0) // check 7
	{
		cout << "A\t" << this->value << " is multiple of 7, ";
	}
	else
	{
		cout << "A\t" << this->value << " is not multiple of 7, ";
	}

	if (this->value % 11 == 0) // check 11
	{
		cout << "is multiple of 11, ";
	}
	else
	{
		cout << "is not multiple of 11, ";
	}

	if (this->value % 13 == 0) // check 13
	{
		cout << "and is multiple of 13\n";
	}
	else
	{
		cout << "and is not multiple of 13\n";
	}
}

void myInt::sumDigits()
{
	int value = this->value; // temp copy of value to be manipulated 
	int sum = 0; // int representing the sum of the digits of value

	while (value != 0) // sum digits
	{
		sum += value % 10;

		value /= 10;
	}

	if (sum % 2 == 0)
	{
		cout << "B\tSum of its digits is even\n";
	}
	else
	{
		cout << "B\tSum of its digits is odd\n";
	}
}

void myInt::squareRoot()
{
	double temp = this->value;

	temp = sqrt(temp);

	cout << "C\tSQRT of " << this->value << " is " << temp << endl;
}

void myInt::primeNum()
{
	for (int i = 2; i <= this->value / 2; i++)
	{
		if (this->value % i == 0)
		{
			cout << "D\t" << this->value << " is not a prime number\n";
			return;
		}
	}

	cout << "D\t" << this->value << " is a prime number\n";
}

void myInt::perfectNum()
{
	int sum = 0; // int representing the sum of value's factors

	for (int i = 1; i < this->value - 1; i++)
	{
		if (this->value % i == 0)
		{
			sum += i;
		}
	}

	if (sum == this->value)
	{
		cout << "E\t" << this->value << " is perfect number\n\n\n";
	}
	else
	{
		cout << "E\t" << this->value << " is not perfect number\n\n\n";
	}
}