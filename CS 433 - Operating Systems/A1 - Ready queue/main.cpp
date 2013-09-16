/*Kevin Novak
September 15, 2013
CS 433, Assignment 1 

This program emulates an operating system's ready queue, which holds a list of processes ready to run, and then the most urgent one will be selected and be processed.

The main data structure used is a heap tree, within an array. A heap tree is a structure where every job has up to 2 children, which have a lower priority than the parent. That means that the very most urgent process will always be at the top. Since it is an array, that means element 0. 
An array is used because it is far more efficient than a linked list (the typical tree data structure), and we know there will be a limited size to the queue.

The heap tree's array holds PCB objects, which have three important attributes:
-id - This is completely unique and unchanging, and important so that the queue doesn't try to take duplicates of the same process.
-priority - This often will seem unique, but it will change every iteration that the process remains in the queue (so no job will be forever forgotten).
-state - In this program, NEW means the object was just created, READY means that it is in the queue, and RUNNING means that it has been removed from the queue.

There is also a PCB Table (array), which holds a list of all processes - not just the READY ones.

To run without makefile: g++ PCB.cpp readyqueue.cpp main.cpp -O2
and run the output.
 
*/
#include <iostream>
#include <stdlib.h> //stdlib and time used for the randomizer.
#include <time.h> 
#include <sys/time.h> //Used to track how long test 2 takes to run. 
using namespace std;
#include "PCB.h"
#include "readyqueue.h"

int main()
{

  cout << "Kevin Novak" << endl << endl;

  cout << "=============================================================" << endl;
  cout << "\nTEST 1:" << endl;
  cout << "=============================================================" << endl;


  PCB PCBTable[20]; //My PCB Table. Holds a list of all of the processes in the system.
  int returnval; //Used for removing highest process, returns the job ID that was removed, so that it can be found in the PCB table to change status back to READY. 
  
  //Initialize the values in the PCB Table
  for (int i = 0; i < 20; i++)
    {
      PCBTable[i].priority = i+1; 
      PCBTable[i].id = i+1;
      PCBTable[i].state = "NEW";
    }

  //Test 1: Create a ReadyQueue q1. Then do the following tests.
  readyqueue q1; //Holds a list of all of the READY processes in the system
  
  //(a) Add processes 5, 1, 8, and 11 to q1. Display q1.
  q1.insertProc(PCBTable[5]);
  q1.insertProc(PCBTable[1]);
  q1.insertProc(PCBTable[8]);
  q1.insertProc(PCBTable[11]);
  PCBTable[5].state = PCBTable[1].state = PCBTable[8].state = PCBTable[11].state = "READY";
  q1.displayQueue();

  //(b) Remove the process with the highest priority from q1 and display q1.
  q1.removeHighestProc(returnval);
  q1.displayQueue();
  PCBTable[returnval-1].state = "RUNNING"; //Removed from the READY queue means that it is now RUNNING.

  //(c) Remove the process with the highest priority from q1 and display q1.
  q1.removeHighestProc(returnval);
  q1.displayQueue();
  PCBTable[returnval-1].state = "RUNNING"; //Removed from the READY queue means that it is now RUNNING.

  //(d) Insert processes 3, 7, 2, 12, 9 to q1.
  q1.insertProc(PCBTable[3]);
  q1.insertProc(PCBTable[7]);
  q1.insertProc(PCBTable[2]);
  q1.insertProc(PCBTable[12]);
  q1.insertProc(PCBTable[9]);
  PCBTable[3].state = PCBTable[7].state = PCBTable[2].state = PCBTable[12].state = PCBTable[9].state = "READY";

  //(e) One by one remove the process with the highest priority from queue q1 and display it after each removal."
  for (int i = q1.size(); i > 0; i--)
    {
      q1.removeHighestProc(returnval);
      q1.displayQueue();
      PCBTable[returnval-1].state = "RUNNING"; //Removed from the READY queue means that it is now RUNNING.
    }
  





  cout << "=============================================================" << endl;
  cout << "TEST 2:" << endl;  
  cout << "=============================================================" << endl;
  /*Use q1 and PCBTable from test 1.
    Randomly select 10 processes from PCBTable, add into q1. But assign each process a random initial priority, 1 to 50.
    Repeat the following 1,000,000 times:
     a) Remove one process from q1. 
     b) Decrement priority of all processes still in q1. (Make sure priority >= 1)
     3) Randomly select a process which isn't yet in q1, and insert, with a random priority.

     Measure total time and print the final content. Use gettimeofday to measure time.
  */
 
  srand(time(NULL));//This is a seed for the random() function, which I use to randomly choose processes and randomly give priority levels
  int randomentry = 0; //This will be the random PCB Table entry.


  //This is for getting the time of day at the start of running test 2.
  struct timeval now;
  int rc=gettimeofday(&now, NULL);
  printf("Start time = %u.%06u\n", now.tv_sec, now.tv_usec);
  
  //Test 2: Use the readyqueue q1 and PCB Table from the first test. First, randomly select 10 processes from the PCB Table and add them into q1, but assign each process a random initial priority between 1 and 50.
  for (int i = 0; i < 10; i++)
    {
      randomentry = rand()%20; //Pick a random number for the table element
      while (PCBTable[randomentry].state == "READY") //If it is going to be a duplicate...
	{
	  randomentry = rand()%20; //...Then pick a different element
	}
      //Once there is a unique element, then continue. Change its state, get a random priority, and add it to the queue.
      PCBTable[randomentry].state = "READY";
      PCB newJob = PCBTable[randomentry]; //newJob is an intermediate step between a PCB table entry and the ready queue addition -- because the priority needs to be randomly generated, without disrupting the priority within the table.
      newJob.priority = rand()%50+1; //Random number between 1 and 50
      q1.insertProc(newJob);
    }

  //Repeat the following steps 1,000,000 times and measure the total time of running the loop
  //(a) remove the most urgen process
  //(b) age the remaining processes
  //(c) pick a random job from PCB table, give it a random priority, and insert into q1.
  
  for (int i = 0; i < 1000000; i++)
    {
      q1.removeHighestProc(returnval);
      PCBTable[returnval-1].state = "RUNNING"; //Once the job has finished excuting, it is now ready to be added to the queue eventually.
      
      q1.age();
      
      
      randomentry = rand()%20; //Pick a random number for the table element
      while (PCBTable[randomentry].state == "READY") //If it is going to be a duplicate...
        {
          randomentry = rand()%20; //...Then pick a different element
        }
      //Once there is a unique element, then continue. Change its state, get a random priority, and add it to the queue.
      PCBTable[randomentry].state = "READY";
      PCB newJob = PCBTable[randomentry]; //newJob is an intermediate step between a PCB table entry and the ready queue addition -- because the priority needs to be randomly generated, without disrupting the priority within the table.
      newJob.priority = rand()%50+1; //Random number between 1 and 50
      q1.insertProc(newJob);
    }

  //This prints the time after running test 2.
  rc=gettimeofday(&now, NULL);
  printf("Finish time= %u.%06u\n", now.tv_sec, now.tv_usec);

 
  //Print out the final content of readyqueue
  q1.displayQueue();
}
