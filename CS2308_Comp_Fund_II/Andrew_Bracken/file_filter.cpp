#include <fstream>
#include <queue>
#include <cctype>
using namespace std;

int main()
{
	ifstream inFile;
	ofstream outFile;

	queue <char> inQueue; 
	int length;

	inFile.open("input.txt");
	outFile.open("output_filter.txt");

	//Get length of file
	inFile.seekg(0, ios::end);
	length = inFile.tellg();
	inFile.seekg(0, ios::beg);

	//Convert toupper and fill queue
	for (int i = 0; i < length; i++)
	{
		inQueue.push(toupper(inFile.get()));
	}

	//Output and empty queue
	while (!inQueue.empty())
	{
		outFile.put(inQueue.front());

		inQueue.pop();
	}

	inFile.close();
	outFile.close();

	return 0;
}