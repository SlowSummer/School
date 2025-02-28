#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

double uniform();
double exponential(double);
bool overlaps(double, double, double);

int main()
{
	srand(time(0)); // Seed Rand

	int years = 20;
	int totalHours = years * 365 * 24; // Total hours in n years

	double mtbf = 500.0; // Mean time between failures (hours)
	double restorationTime = 10.0;
	double time = 0.0; // Eleapsed time in hours
	double lambda = 1.0 / mtbf;
	
	bool systemFailure = false; // Used for total failure logic
	double systemFailureTime = -1; // Tracks time at which total failure occurs
	
	vector<double> server1Failures;
	vector<double> server2Failures;


	while (time < totalHours) // Simulate server1 failures
	{
		double uptime = exponential(lambda); // Generate time until next failure
		time += uptime;

		if (time < totalHours)
		{
			server1Failures.push_back(time); // Tracks failure time
		}

		time += restorationTime; // Add time to restore server
	}

	time = 0.0; // Reset for server 2

	while (time < totalHours) // Simulate server2 failures
	{
		double uptime = exponential(lambda); // Generate time until next failure
		time += uptime;

		if (time < totalHours)
		{
			server2Failures.push_back(time); // Tracks failure time
		}

		time += restorationTime; // Add time to restore server
	}


	for (double failTime1 : server1Failures)
	{
		for (double failTime2 : server2Failures)
		{
			if (overlaps(failTime1, failTime2, restorationTime)) // Check if both server are down
			{
				systemFailure = true;
				systemFailureTime = max(failTime1, failTime2); // Time when overlap occurs

				cout << "System-wide failure detected at: " << systemFailureTime << endl;
				cout << "Server 1 failed at: " << failTime1 << endl;
				cout << "Server 2 failed at: " << failTime2 << "\n\n";
				break;
			}
		}

		if (systemFailure) // Exit when first error is detected
		{
			break;
		}
	}

	if (!systemFailure)
	{
		cout << "No system-wide failures detected.\n\n";
	}

	// Print server failure and restore times
	cout << "Server 1 Failure:\tRestored:\n ";
	
	for (double failTime : server1Failures)
	{
		cout << failTime << "\t\t\t" << failTime + 10 << endl;
	}

	cout << "\nServer 2 Failure:\tRestored:\n ";

	for (double failTime : server2Failures)
	{
		cout << failTime << "\t\t\t" << failTime + 10 << endl;
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

// Checks if the servers are simultaneously down
//* Input failTime1: time when server 1 is down
//*	Input failTime2: time when server 2 is down
//* Returns bool: true if the two down time are within restorationTime hours of each other
bool overlaps(double failTime1, double failTime2, double restorationTime)
{
	return abs(failTime1 - failTime2) <= restorationTime;
}

// Generate uniform random num between 0 and 1
//* Input: N/A
//* Return double
double uniform()
{
	return rand() / static_cast<double>(RAND_MAX);
}
















