#include <fstream>
#include <stack>
using namespace std; 



int main()
{
	ifstream inFile;
	ofstream outFile;

	stack <char> inStack; 
	int length;

	inFile.open("input.txt");
	outFile.open("output_reverse.txt");

	//Get file length
	inFile.seekg(0, ios::end);
	length = inFile.tellg();
	inFile.seekg(0, ios::beg);

	//Fill stack
	for (int i = 0; i < length; i++)
	{
		inStack.push(inFile.get());
	}

	//Output and empty stack
	while (!inStack.empty())
	{
		outFile.put(inStack.top());

		inStack.pop();
	}

	inFile.close();
	outFile.close();

	return 0;
}