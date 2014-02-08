/* Jorge Torres
Kevin Novak

10/26/2013
CS 433 - Assignment 3

This program provides discrete event simulation, to simulate a scheduler in a computer.

To run, type ./Assignment3.o X Y  where X is either 1 for First Come, First Serve, or 2 for Shortest Job First,
and where Y is the number of processes to simulate.*/

#include <iostream>
#include <queue>
#include <iomanip>
#include "random.h"
#include "myclasses.h"

using namespace std;

void simulation::executeSimulation(int numOfProcesses, int type)
{ 
  //Variables for keeping track of times
  int totalTime = 0;  
  int totalIO = 0;
  int totalCPU = 0;

  int finishedProcesses = 0;

  priority_queue<event> eventQueue;
  priority_queue<process> processQueue;
  CPU.idle = true;
  
  //Populate the event queue
  event newEvent;
  for (int i = 0; i < numOfProcesses; i++)
    {
      newEvent.TYPE = PROCESSARRIVAL;
      newEvent.proc.pID = i+1;
      newEvent.proc.startTime = rand() % 300000; //"randomly distributed over a five-minute time span"
      newEvent.triggertime = newEvent.proc.startTime;
      newEvent.proc.totalDuration = rand() % 59000 + 1000; //"between 1 second and 1 minute"
      newEvent.proc.remainingDuration = newEvent.proc.totalDuration;
      newEvent.proc.avgBurstLength = rand() % 95 + 5; //"between 5 ms to 100 ms"
      newEvent.proc.nextBurstLength = CPUBurstRandom(newEvent.proc.avgBurstLength);
      newEvent.proc.IOBurstTime = 0;
      newEvent.proc.timespentinIO = 0;
      if (type == 1) //If it is FCFS, then base priority off of the arrival time.
	newEvent.proc.priority = newEvent.proc.startTime;
      else//If it is SJF, then base priority off of the total duration
	newEvent.proc.priority =  newEvent.proc.totalDuration;
      
      //Push this event into the event queue
      eventQueue.push(newEvent);
    }

  //Temporary event and processes
  event tempEvent;
  process tempProcess;

  //Execute everything in the event queue
  while (!eventQueue.empty())
    {
      //Get the next event from the queue
      tempEvent = eventQueue.top();
      eventQueue.pop();
      totalTime = tempEvent.triggertime; //Update total time
      if (totalTime < 300000) //If there is still time to process, do so
	{
	  switch(tempEvent.TYPE)
	    {
	    case PROCESSARRIVAL:
	      processQueue.push(tempEvent.proc); 
	      if (CPU.idle) //If the CPU isn't busy, give it a job to do.
		{
		  tempProcess = processQueue.top();
		  processQueue.pop();
		  eventQueue.push(dispatch(tempProcess, totalTime));
		}
	      break;
	      
	    case CPUBURSTCOMPLETION:
	      CPU.idle = true;
	      //tempEvent.proc.remainingDuration -= tempEvent.proc.nextBurstLength; 
	      tempEvent.proc.remainingDuration = 0;
	      if (tempEvent.proc.remainingDuration > 0) //If there is time left for the process, make an IO burst
		{
		  
		  tempEvent.proc.IOBurstTime = (rand() % 70 + 30); //"between 30 to 100 ms"
		  tempEvent.TYPE = IOCOMPLETION;
		  tempEvent.triggertime = totalTime + tempEvent.proc.IOBurstTime;
		  eventQueue.push(tempEvent);
		}
	      //Else, the process has finished. So print its information
	      else 
		{
		  totalCPU += tempEvent.proc.totalDuration;
		  cout << "\nProcess " << tempEvent.proc.pID << ":"
		       << "\nArrival time: " << (tempEvent.proc.startTime)/1000 << " s"
		       << "\nFinish time: " << tempEvent.triggertime/1000 << " s"
		       << "\nService time: " << tempEvent.proc.totalDuration/1000 << " s"
		       << "\nI/O time: " << tempEvent.proc.timespentinIO/1000 << " s"
		       << "\nTurnaround time: " << (tempEvent.triggertime - tempEvent.proc.startTime)/1000 << " s"
		       << "\nWaiting time: " << (tempEvent.triggertime - (tempEvent.proc.totalDuration + tempEvent.proc.startTime))/1000 << " s"
		       << endl;
		  finishedProcesses++;
		}
	      break;

	    case IOCOMPLETION:
	      tempEvent.proc.nextBurstLength = CPUBurstRandom(tempEvent.proc.avgBurstLength); //Decide the next CPU burst
	      tempEvent.proc.timespentinIO += tempEvent.proc.IOBurstTime; //Save how much time has been spent in IO
	      processQueue.push(tempEvent.proc);
	      if (CPU.idle) //If the CPU isn't busy, give it a job to do.
		{
		  tempProcess = processQueue.top();
		  processQueue.pop();
		  eventQueue.push(dispatch(tempProcess, totalTime));
		}
	      break;
	    }//End event type switch
	}
      //Else, there is no more time left to process.
    }//End eventQueue loop

  //Now, print the completed jobs.
  if (finishedProcesses > 0)
    {
      cout << "\nCompleted " << finishedProcesses << " processes.";
      float decimalnumber = (float)totalCPU / (float)totalTime;
      cout << setprecision(0) <<"\nCPU Utilization is " << decimalnumber; //Time spent in CPU over total time
      decimalnumber = (float)finishedProcesses / (float)totalTime * 1000;
      cout << setprecision(2) << "\nThroughput is " << decimalnumber << " jobs / s"; //jobs completed over total time, over 1000 for seconds
      decimalnumber = (float)totalTime / (float)finishedProcesses / 1000;
      cout << "\nAverage turnaround time: " << decimalnumber << " s" << endl;
    }
  else
    cout << "\nNo jobs finished" << endl;
}//End executeSimulation

//This will make a dispatch a new job
event simulation::dispatch(process nextProcess, int currentTime)
{
  event newEvent;
  CPU.idle = false;
  newEvent.TYPE = CPUBURSTCOMPLETION;
  newEvent.triggertime = currentTime + nextProcess.totalDuration;
  newEvent.proc = nextProcess;
  return newEvent;
}
