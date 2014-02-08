/* Jorge Torres
Kevin Novak

10/26/2013
CS 433 - Assignment 3

This program provides discrete event simulation, to simulate a scheduler in a computer.

To run, type ./Assignment3.o X Y  where X is either 1 for First Come, First Serve, or 2 for Shortest Job First,
and where Y is the number of processes to simulate.*/


#ifndef MYCLASSES_H
#define MYCLASSES_H

#include <string>
using namespace std;

enum type {PROCESSARRIVAL, CPUBURSTCOMPLETION, IOCOMPLETION}; //Type of events

//This is for a process, an actual task to be done by the processor.
class process
{
 public:
  int pID;
  int startTime;
  int totalDuration;
  int remainingDuration;
  int avgBurstLength;
  int nextBurstLength;
  int IOBurstTime;
  int timespentinIO; //Sums the duration of IO bursts this process has experienced
  int priority;
  bool operator<(const process& p)const// To be used for comparisons, for picking jobs.
  {
    return (this->priority > p.priority);
  };
};

//This is for an event, some kind of thing that interrupts the processor and makes it do something else.
class event
{
 public:
  event(){};
  ~event(){};
  type TYPE; //Process arrival, CPU burst completion, IO burst completion
  int triggertime;//When the event will trigger
  process proc;//Process associated to the event
  bool operator<(const event& e)const // To be used for comparisons, for picking jobs.
  {
    return (this->triggertime > e.triggertime);
  }; 
};

//This is our processor itself. It has a current process, and a status.
struct processor{
  process curr;
  bool idle;
};

//This is our simulation. It has a processor attached to it, and does all of the simulating of things.
class simulation
{
 public:
  processor CPU;
  simulation(){};
  ~simulation(){};
  void executeSimulation(int numOfProcesses, int type); //type 1 is FCFS, type 2 is SJF
  event dispatch(process nextProcess, int currentTime);
};

#endif
