//-----------------------------------------------------
//
// Lab 11, Exercise 1
//
// Operating system task scheduling simulation
// 
//------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include <time.h>

#include "PriorityQueue.h"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
	int getPriority() const
	{
		return priority;
	}     // Returns the priority. Needed by the heap.

	int priority,                // Task's priority
		arrived;                 // Time when task was enqueued

};

int main()
{
	PriorityQueue<TaskData> taskPQ;   // Priority queue of tasks
	TaskData task;               // Task
	int simLength,               // Length of simulation (minutes)
		minute,                  // Current minute
		numPtyLevels = 2,            // Number of priority levels
		numArrivals = 0,             // Number of new tasks arriving
		j;                     // Loop counter

	// Seed the random number generator
	srand((unsigned int)time(NULL));

//	cout << endl << "Enter the number of priority levels : ";
//	cin >> numPtyLevels;

	cout << "Enter the length of time to run the simulator : ";
	cin >> simLength;

	time_t timer;

	for (minute = 0; minute < simLength; minute++)
	{
		// Dequeue the first task in the queue (if any).
		if (taskPQ.isEmpty() == false)
		{
			task=taskPQ.dequeue();
			cout << "Priority " << task.priority << " task arrived at " << task.arrived << " & completed at " << minute << endl;
		}

		numArrivals = rand() % 4;
		switch (numArrivals)
		{
		case 2:
			task.arrived = minute;
			task.priority = rand() % numPtyLevels;
			//task.priority = rand() % numPtyLevels - (task.arrived / simLength);
			taskPQ.enqueue(task);
		case 1:
			task.arrived = minute;
			task.priority = rand() % numPtyLevels;
			taskPQ.enqueue(task);
		default:
			break;
		}


	}

	return 0;


}
