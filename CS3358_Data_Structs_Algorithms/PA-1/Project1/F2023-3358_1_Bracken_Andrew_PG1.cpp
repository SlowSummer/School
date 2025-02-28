// Andrew Bracken
// Serial Number /s :
// Due Date : 9/07/2023
// Programming Assignment Number 1
// Fall 2023 - CS 3358 - Section 1
//
// Instructor: Husain Gholoom.
//
// Program takes two 2D arrays and finds their sum, product,
// and determines if the arrays are special arrays. 

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std; 

void PrintArray(int a[][3]);
void PopulateArray(int a[][3]);
void SumArrays(int a1[][3], int a2[][3], int a3[][3]);
void ArrayProduct(int a1[][3], int a2[][3], int a3[][3]);
void TransposeArray(int a[][3]);
void SumRow(int a[][3], int rowNum, bool &special, int sNum);
void SumColumn(int a[][3], int columnNum, bool &special, int sNum);
void SumDiagonals(int a[][3], bool &special1, bool &special2, int sNum);
bool isSpecial(bool sum1, bool sum2, bool sum3);
bool Contains(int a[][3], int current);

int main()
{
	int Array_1[3][3];
	int Array_2[3][3];
	int Array_3[3][3];
	int Array_4[3][3];

	int specialNum = 15; //the special num for a 3 x 3 matrix; n = 3

	bool rowSum1 = false; //bool to check if each sum == sepcial num
	bool rowSum2 = false; //bool to check if each sum == sepcial num
	bool rowSum3 = false; //bool to check if each sum == sepcial num
	bool colSum1 = false; //bool to check if each sum == sepcial num
	bool colSum2 = false; //bool to check if each sum == sepcial num
	bool colSum3 = false; //bool to check if each sum == sepcial num
	bool diagSum1 = false; //bool to check if each sum == sepcial num
	bool diagSum2 = false; //bool to check if each sum == sepcial num


	//Seed rand() using time
	srand(time(NULL));
	
	//formated intro and list
	cout << "Welcome to my Array program. The function of the";
	cout << " program is to :\n\n\n\t";

	cout << "1. Create two Arrays (Array_1, Array2). "
		<< "Each Array is of size 3 x 3.\n\t";

	cout << "2. Populate both Arrays with distinct random "
		<< "numbers that are between 1 and 15.\n\t   ";
	cout << "Display both Arrays.\n\t";

	cout << "3. Adding and multiplying Array_1 and Array_2.\n\t";

	cout << "4. Displaying the transposed of Array_1.\n\t";

	cout << "5. Display the sum of elemnts of each row of Array_1, "
		<< "displaying the sum of\n\t   elements each column of Array_1, "
		<< "displaying the sum of both diagonal elements of\n\t   Array_1.\n\t";

	cout << "6. Finally, determining whether or not Array_1 is "
		<< "special array.\n\n\n\n";

	cout << "Array 1  :\n\n\n";

	//populate and output A1
	PopulateArray(Array_1);
	PrintArray(Array_1);

	cout << "Array 2  :\n\n\n";

	//populate and output A2
	PopulateArray(Array_2);
	PrintArray(Array_2);

	cout << "Sum of Array 1 and Array 2\n\n\n";

	//calc and output sum of A1 and A2 as A3
	SumArrays(Array_1, Array_2, Array_3);
	PrintArray(Array_3);

	cout << "Product of Array 1 and Array 2\n\n\n";

	//calc and output product of A1 and A2 as A4
	ArrayProduct(Array_1, Array_2, Array_4);
	PrintArray(Array_4);

	cout << "Transpose of Array 1\n\n\n";

	//calc and output transposition of Array_1
	TransposeArray(Array_1);

	//calc and output row sums
	SumRow(Array_1, 1, rowSum1, specialNum);
	SumRow(Array_1, 2, rowSum2, specialNum);
	SumRow(Array_1, 3, rowSum3, specialNum);

	cout << "\n\n\n";

	//calc and output col sums
	SumColumn(Array_1, 1, colSum1, specialNum);
	SumColumn(Array_1, 2, colSum2, specialNum);
	SumColumn(Array_1, 3, colSum3, specialNum);

	cout << "\n\n\n";

	//calc and output diag sums
	SumDiagonals(Array_1, diagSum1, diagSum2, specialNum);

	cout << "The special number for Array  1  is  "
		<< specialNum << "\n\n\n";


	//check rows, cols, and diag sums for special num
	if (isSpecial(rowSum1, rowSum2, rowSum3)) 
	{
		if (isSpecial(colSum1, colSum2, colSum3))
		{
			if (isSpecial(diagSum1, diagSum2, true))
			{
				cout << "The above is Special Array\n\n\n\n\n";
			}

		}
		else
		{
			cout << "The above is not a Special Array\n\n\n\n\n";
		}

	}
	else 
	{
		cout << "The above is not a Special Array\n\n\n\n\n";
	}
	
	cout << "This algorithm is implemented By Andrew Bracken\n"
		<< "September - 2023\n";

	return 0;
}

void PrintArray(int a[][3])
{
	string arrayString; //current element of a[][] as a string
	int widthMax = 0; //max width of the elements of a[][]
	int stringSize; //size of current element of a[][]

	//find widthMax
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arrayString = to_string(a[i][j]);
			stringSize = arrayString.size();
			widthMax = max(widthMax, stringSize);
		}
	}

	//itterate widthMax to fit format
	widthMax += 3;

	//formatted output
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << a[i][j];
			arrayString = to_string(a[i][j]);
			stringSize = (widthMax - arrayString.size());

			while (stringSize--)
			{
				cout << " ";
			}
		}
		cout << "\n\n";
	}

	cout << "\n";
}

void PopulateArray(int a[][3])
{
	int temp = 0; //integer value for the next element of a[][]

	// Initialize first element
	temp = rand() % 15 + 1;
	a[0][0] = temp;

	//populate the rest of a with unique elements
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//check if temp already exists in a
			while (Contains(a, temp))
			{
				temp = rand() % 15 + 1;
			}
			a[i][j] = temp;
		}
	}
}

void ArrayProduct(int a1[][3], int a2[][3], int a3[][3])
{
	//multi elements of a1 by a2 and store in a3
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a3[i][j] = a1[i][j] * a2[i][j];
		}
	}
}

void SumArrays(int a1[][3], int a2[][3], int a3[][3])
{
	//store the sum of a1 and a2 in a3
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a3[i][j] = a1[i][j] + a2[i][j];
		}
	}
}\

void TransposeArray(int a[][3])
{
	int temp[3][3]; //an array which will become the transposed a[][]

	//populate temp
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = a[j][i];
		}
	}

	//print transposed a[][]
	PrintArray(temp);
}

void SumRow(int a[][3], int rowNum, bool &special, int sNum)
{
	int sum = 0; //summation of each element in row rowNum

	//find sum of row
	for (int i = 0; i < 3; i++)
	{
		sum += a[rowNum - 1][i];
	}

	//check if sum == special number
	if (sum == sNum)
	{
		special = true;
	}

	//display sum
	cout << "Sum of numbers in Row    # " << rowNum
		<< "   in Array1   =   " << sum << endl;
}

void SumColumn(int a[][3], int columnNum, bool &special, int sNum)
{
	int sum = 0; //summation of each element in colum columNum

	//find sum of column
	for (int i = 0; i < 3; i++)
	{
		sum += a[i][columnNum - 1];
	}

	//check if sum == special number
	if (sum == sNum)
	{
		special = true;
	}

	//display sum
	cout << "Sum of numbers in Column # " << columnNum
		<< "   in Array1   =   " << sum << endl;
}

void SumDiagonals(int a[][3], bool &special1, bool &special2, int sNum)
{
	int sum = 0; //integer of the sum of ints in each diagonal
	int j = 2; //integer used to itterate the second diagonal

	//calc the sum of first diagonal
	for (int i = 0; i < 3; i++)
	{
		sum += a[i][i];
	}

	//display sum
	cout << "Sum of numbers in first diagonal  in Array1   =   "
		<< sum << "\n";

	//check if sum == special number
	if (sum == sNum)
	{
		special1 = true;
	}

	//reset sum for second diag
	sum = 0;

	//calc sum of second diagonal
	for (int i = 0; i < 3; i++)
	{
		sum += a[i][j];
		j--;
	}

	//check if sum == special number
	if (sum == sNum)
	{
		special2 = true;
	}

	//display sum
	cout << "Sum of numbers in second diagonal in Array1   =   "
		<< sum << "\n\n\n";

}

bool isSpecial(bool sum1, bool sum2, bool sum3)
{
	//check if all rows/cols/diags == specail number
	if (sum1 && sum2 && sum3)
	{
		return true;
	}

	return false;
}

bool Contains(int a[][3], int current)
{
	//check if any element in a[][] == current
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[i][j] == current)
			{
				return true;
			}
		}
	}

	return false;
}