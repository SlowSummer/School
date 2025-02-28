#include <queue>
#include <vector>
#include "Event.h"

using namespace std;

class Simulator
{
public:
	Simulator(double lambda, double avgServiceTime);
	void run();
	void generateArrival();
	void generateDeparture(double serviceTime);
	void processEvent(Event event);
	void reportMetrics();

private:
	double lambda;
	double avgServiceTime;
	double clock;
	double totalTurnaroundTime;
	double totalCPUTime;
	double totalReadyQueueTime;
	double lastEventTime;
	double busyTime;

	int completedProcesses;
	int readyQueueSize;

	priority_queue <Event> eventQueue;
	queue<double> arrivalTimesQueue;

	double generateExponential(double rate);
};