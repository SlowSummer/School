#include "Simulator.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

Simulator::Simulator(double lambda, double avgServiceTime)
  : lambda(lambda), 
    avgServiceTime(avgServiceTime), 
    clock(0), 
    completedProcesses(0), 
    totalTurnaroundTime(0), 
    totalCPUTime(0),
    readyQueueSize(0), 
    busyTime(0), 
    totalReadyQueueTime(0),
    lastEventTime(0)
{
        generateArrival(); // first arrival 
}

void Simulator::run()
{
    // 10,000 processes
    while (completedProcesses < 10000)
    {
        Event currentEvent = eventQueue.top();
        eventQueue.pop();
        clock = currentEvent.time;
        processEvent(currentEvent);
    }

    reportMetrics();
}

void Simulator::generateArrival()
{
    double interArrivalTime = generateExponential(lambda);
    eventQueue.push(Event(EventType::ARRIVAL, clock + interArrivalTime)); // Ensure event after current time

    arrivalTimesQueue.push(clock); // Store arrival times
}

void Simulator::generateDeparture(double serviceTime)
{
    eventQueue.push(Event(EventType::DEPARTURE, clock + serviceTime));  // Ensure event after current time
}

void Simulator::processEvent(Event event)
{
    totalReadyQueueTime += readyQueueSize * (clock - lastEventTime);
    lastEventTime = clock; // update to current time

    if (event.type == EventType::ARRIVAL) // Handle arrival
    {
        generateArrival(); // generate the next arrival

        if (readyQueueSize == 0) // CPU is idle
        {
            // Start service
            double serviceTime = generateExponential(1 / avgServiceTime); // gen service time
            generateDeparture(serviceTime); // gen departure
            busyTime += serviceTime;
        }
        readyQueueSize++; // new proccess in ready queue
    }
    else if (event.type == EventType::DEPARTURE) // Handle departure
    {
        completedProcesses++; // Completed
        readyQueueSize--; // Process leaves system

        // Calculate turnaround time
        double arrivalTime = arrivalTimesQueue.front();
        arrivalTimesQueue.pop();
        double turnaroundTime = clock - arrivalTime;
        totalTurnaroundTime += turnaroundTime;

        if (readyQueueSize > 0) // Processes still in queue
        {
            // Start service
            double serviceTime = generateExponential(1 / avgServiceTime); // gen service time
            generateDeparture(serviceTime); // gen departure
            busyTime += serviceTime;
        }
    }
}

void Simulator::reportMetrics()
{
    double avgTurnaroundTime = totalTurnaroundTime / completedProcesses;
    double throughput = completedProcesses / clock;
    double cpuUtilization = busyTime / clock;
    double avgQueueSize = totalReadyQueueTime / clock;

    cout << "Lambda: " << lambda << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Throughput: " << throughput << endl;
    cout << "CPU Utilization : " << cpuUtilization << endl;
    cout << "Average Ready Queue Size: " << avgQueueSize << "\n\n";
}

double Simulator::generateExponential(double rate)
{
    double u = (double)rand() / (RAND_MAX + 1.0); // Ensure u != 1
    return -log(1 - u) / rate;
}


