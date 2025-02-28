#include <iostream>


using namespace std;

int main()
{
	char userLetter;
	int userNum;
	int spaces = 0;

	cin >> userLetter;
	cin >> userNum;

	spaces = userNum / 2;

	// Prints top half of diamond
	for (int i = 0; i < userNum / 2; i++)
	{
		// Prints spaces
		for (int k = 1; k < spaces; k++)
		{
			cout << " ";
			
		}

		// Prints userLetter
		for (int j = 0; j <= i; j++)
		{
			cout << userLetter << userLetter;
		}

		spaces--;

		cout << endl;
	}


	// Prints bottom half of diamond
	for (int i = 0; i < userNum / 2; i++)
	{
		for (int k = 0; k < spaces; k++)
		{
			cout << " ";
		}

		for (int j = userNum / 2; j > i; j--)
		{
			cout << userLetter << userLetter;
		}

		spaces++;

		cout << endl;
	}
	return 0;
}