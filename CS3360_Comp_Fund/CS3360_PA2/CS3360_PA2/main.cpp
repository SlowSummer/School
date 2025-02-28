#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Simulator.h"


using namespace std;

int main(int argc, char* argv[])
{
	// Error check command line arguments
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " <lambda> <avgServiceTime>" << endl;
		return 1;
	}

	srand(static_cast<unsigned int> (time(0))); // Seed rand
	//srand(1);

	// Handle command line arguments
	double lambda = atof(argv[1]);
	double avgServiceTime = atof(argv[2]);

	for (lambda; lambda <= 30; lambda++)
	{
		// Initialize and run Simulation
		Simulator sim(lambda, avgServiceTime);
		sim.run();
	}

	return 0;
}