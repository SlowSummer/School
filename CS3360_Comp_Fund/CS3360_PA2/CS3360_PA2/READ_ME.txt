After transfering to a new directory on zeus.cs.txstate.edu:

Compile the program with: g++ -o main main.cpp Simulator.cpp Simulator.h Event.h

To run the code, use command ./main followed by two command line arguments.
The first argument is the starting lambda value and the second is the average 
service time.

Example: ./main 10 0.04

With these command line arguments, the program will run a simulation from lambda = 10
to lambda = 30, each with an average service time of 0.04.