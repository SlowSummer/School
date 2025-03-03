#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <cmath>

using namespace std;

const int USER_AGE = 18;

double uniform();

double exponential(double);


int main()
{
	srand(time(0));

	int processes = 1000;
	double arrivalRate = 2.0; // 2 processes per second
	double serviceRate = 1.0; // average service time
	double arrivalTime = 0.0; // Tracks elapsed time

	// Use to calculate actual average
	double totalIntArrTime = 0.0; 
	double totalServiceTime = 0.0;

	vector<tuple<int, double, double>> processList; // Stores tuples dynamically


	for (int i = 1; i <= processes; i++)
	{
		double interArrivalTime = exponential(arrivalRate); // Generates random inter arrival time
		arrivalTime += interArrivalTime; // Tracks total elapsed time
		totalIntArrTime += interArrivalTime;

		double serviceTime = exponential(serviceRate); // Generate random service time
		totalServiceTime += serviceTime;

		processList.emplace_back(i, arrivalTime, serviceTime); // Store tuple
	}

	double averageIntArrTime = totalIntArrTime / processes;
	double averageArrRate = 1.0 / averageIntArrTime; // Inverse of the average int-arr time
	double averageServiceTime = totalServiceTime / processes;

	
	cout << "Average Arrival Rate: " << averageArrRate << " processes per second\n";
	cout << "Average Service Time: " << averageServiceTime << " seconds\n\n\n";

	cout << "ID:\tArrival Time:\tService Time:\n";

	for (auto& process : processList)
	{
		int id;
		double arrival;
		double service;

		tie(id, arrival, service) = process;
		cout << id << "\t" << arrival << "\t\t" << service << endl;
	}

	return 0;
}

// Generates random number following an exponential distribution
//* Input lambda: process arrival time or service time
//* Returns double: time between each procceses arrival time
double exponential(double lambda)
{
	double uniformNum = uniform();
	return -log(1 - uniformNum) / lambda;
}


// Generate uniform random num between 0 and 1
//* Input: N/A
//* Return double
double uniform()
{
	return rand() / static_cast<double>(RAND_MAX);
}