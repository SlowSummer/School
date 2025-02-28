// Author : Andrew Bracken
//
// Due Date : 11/27/2023
//
// Programming Assignment Number 7 -
//
// Fall 2023 - CS 3358 - 001
//
// Instructor: Husain Gholoom.
//
// Program implements a hash table and preforms various
// changes to the initially generated table


#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Hash
{
	private:
		int hash_pos;
		int array[20];
		int linearProb;

	public:
		Hash();
		void insert(int);
		void search(int);
		int hash(int);
		int reHash(int);
		int getLinearProb();
		void Delete(int);
		void Display();
		void initialGen();
};

int main()
{
	// seed rand with time
	srand(time(NULL));

	Hash h;

	cout << "Welcome to my Hashing Program\n\n"
		<< " -----------------------------\n\n";
	cout << "A.\tCreate an integer array of size 20. "
		<< "Assigning # to each\n\tlocation in the array indicating"
		<< "the array is empty.\n";
	cout << "B.\tPopulate 18 elements of the array with random "
		<< "integer\n\tnumbers.\n";
	cout << "C.\tIf a collision occurs, linear probing will find the "
		<< "next\n\tavailable position / location.\n";
	cout << "D.\tThe generated array will be displayed in 3 lines. "
		<< "First line\n\tcontains 6 numbers seperated by a tab "
		<< "space, Second and\n\tthe Third lines contain 7 numbers "
		<< "seperated by a tab space.\n\n\n";

	cout << "The Generated Array.\n\n\n";

	h.initialGen();

	h.Display();

	h.search(168);

	h.search(172);

	h.insert(162);

	h.insert(163);

	h.insert(165);

	h.Delete(163);

	h.Delete(175);

	cout << "The Final Array.\n\n\n";

	h.Display();

	cout << "\nThe number of linear probes occured when adding "
		<< "an element in the\nTable is " << h.getLinearProb()
		<< "\n\n\n";
	cout << "This Hashing Program was Implemented by\n"
		<< "Andrew Bracken - November 27th, 2023\n";

	return 0;
}

Hash::Hash()
{
	hash_pos = 0;
	linearProb = 0; // int # of linear probes used

	for (int i = 0; i < 20; i++)
	{
		array[i] = '*';
	}
}

void Hash::initialGen()
{
	int data; // rand value to be stored

	for (int i = 0; i < 18; i++)
	{		data = rand() % 6 + 164;
		hash_pos = hash(data);

		// linear probe on collision
		while (array[hash_pos] != '*')
		{
			hash_pos = reHash(hash_pos);
			linearProb++;
		}

		array[hash_pos] = data;
	}
}

void Hash::insert(int data)
{
	int count = 0; // int to check if table is full

	hash_pos = hash(data);

	cout << "Inserting " << data << " in the Table.\n";

	while (array[hash_pos] != '*')
	{
		hash_pos = reHash(hash_pos);

		linearProb++;

		count++;

		if (count >= 20)
		{
			cout << data << " is not inserted. Table is Full."
				<< "\n\n\n";

			return;
		}
	}

	array[hash_pos] = data;

	cout << data << " is stored at index " << hash_pos
		<< "\n\n\n";
}

void Hash::search(int data)
{
	int i = 0; // int used to terminate while()
	bool isFound = false; // bool tracking if data was found

	hash_pos = hash(data);

	cout << "Searching For " << data << " in the Table.\n";

	if (array[hash_pos] == '*')
	{
		cout << data << " was not found in Table.\n\n\n";
		return;
	}

	while (i < 20)
	{
		if (array[hash_pos] != data)
		{
			hash_pos = reHash(hash_pos);
		}
		else
		{
			isFound = true;

			break;
		}

		i++;
	}

	if (isFound)
	{
		cout << data << " was found in location\t: "
			<< hash_pos << "\n\n\n";
	}
	else
	{
		cout << data << " was not found in Table.\n\n\n";
	}
}

void Hash::Delete(int data)
{
	int hash_pos = hash(data);
	int i = 0; // int used to terminate while()
	bool isFound = false; // bool tracking if data was found

	cout << "Deleting " << data << " from the Table.\n";

	while (i < 20)
	{
		if (array[hash_pos] == data)
		{
			isFound = true;
			break;
		}
		else
		{
			hash_pos = reHash(hash_pos);
		}

		i++;
	}

	if (isFound)
	{
		array[hash_pos] = '*';
		cout << data << " is Deleted from the Table\n\n\n";
	}
	else
	{
		cout << data << " was not found.\n\n\n";
	}
}

void Hash::Display()
{
	for (int i = 0; i < 20; i++)
	{
		cout << array[i] << "\t";

		if (i == 5)
		{
			cout << "\n\n";
		}

		if (i == 12 || i == 19)
		{
			cout << "\n\n";
		}

	}

	cout << "\n\n";
}

int Hash::hash(int key)
{
	return key % 20;
}

int Hash::reHash(int key)
{
	return (key + 1) % 20;
}

int Hash::getLinearProb()
{
	return linearProb;
}
