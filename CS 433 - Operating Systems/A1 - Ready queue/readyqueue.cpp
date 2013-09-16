/* This is the ready queue class. It holds all of the READY processes and executes them according to a priority level. Every time a process is run, the next-most-urgent process will be moved to the front of the queue.

The structure is a heap tree, meaning that every job has up to 2 children, which are both of lower (or equal) importance than itself. Also characteristic of the heap tree is that it gets reordered every time the first job is removed, ensuring that element 0 is always the most important one.
*/

using namespace std;
#include "PCB.h"
#include "readyqueue.h"

//Initialize end, which will represent the point at which a new job will be added.
//Initialize the rest of the array, so that junk values <0 don't creep into the queue (1-50 are valid)
readyqueue::readyqueue()
{
  end = 0;
  for (int i = 0; i < 10; i++)
    {
      theQueue[i].id = 99;
      theQueue[i].priority = 99;
    }
}

readyqueue::~readyqueue()
{
}


//This function is for adding a process to the queue. It checks to make sure there is room, and the process has a valid priority level (1-50). It adds the process to the end of the queue, and trickles it up the tree until the new process is less urgent than its parent.
//In a real world scenario, this is what adds processes to a list of processes which are ready to be run, and prioritizes them.
void readyqueue::insertProc(PCB newProcess)
{
  //Make sure there is room in the queue, and that the priority is valid.
  if (end >= 100)
    throw Overflow();
  if (newProcess.priority > 50 || newProcess.priority < 1)
    throw Illegal();

  //Add the new job
  theQueue[end] = newProcess;
  
  //If this was the first element, nothing needs to be reordered. So just increment "end" and leave the function
  if (end == 0)
    {
      end++;
      return;
    }
 
  //Otherwise, trickle the new job up to its proper tier.
  int Child = end;
  int Parent = (isEven(Child)? (Child-2)/2 : (Child-1)/2);
  
  //If the new job is more urgent than its parent, then swap them. And repeat this until the new child no longer has a parent more urgent than it.
  while (theQueue[Parent].priority > theQueue[Child].priority && Child > 0)
    {
  
      //This is the swap, using a temp variable to juggle the PCB entities
      PCB temp = theQueue[Parent];
      theQueue[Parent] = theQueue[Child];
      theQueue[Child] = temp;

      //Change what the Child and Parent variables refer to (what element number), for the next loop iteration
      Child = Parent;
      Parent = (isEven(Child)? (Child-2)/2 : (Child-1)/2);
    }
  end++; //Increment end, finally

}

//This removes the first process from the ready queue. Then it calls reheapify which reorders the queue to make element 0 have the new most urgent job.
//In a real world scenario, this is what would take a READY process and actually RUN it, as well as reordering the ready jobs.
void readyqueue::removeHighestProc(int &returnval)
{
  if (end == 0)
    throw Underflow();//If there is no process to be run, then say so.

  returnval = theQueue[0].id; //Return the id of the executed job, so that the PCB Table can be updated
  
  //Since this is a static data structure, we just have to give it values we know aren't valid. And let it sink to the bottom with reheapify.
  theQueue[0].priority = 99;
  theQueue[0].id = 99;

  reheapify();
}

//This is called by removeHighestProc, which will recorder the list of jobs so that the most urgent one is in theQueue[0].
//In a real world scenario, this is part of removing jobs from the READY queue.
void readyqueue::reheapify()
{  
  end--; //Decrement end. It will now point to the last job in the queue (which will soon be moved up, and then end will point to a junk value which will be replaced by the next new job)
  //Take the very last process, and copy it to the very beginning (where we just executed a process)
  theQueue[0] = theQueue[end];
  theQueue[end].priority = theQueue[end].id = 99;

  //Parent and Child represent the element number of the process that just got moved up, and it's smaller child, respectively
  int Parent = 0; //This is the node that just got moved to the top from the bottom

  //LChild and RChild are used just to make the comparison for picking the correct child seem less daunting
  int LChild = 2*Parent+1; //Left child, odd
  int RChild = 2*Parent+2; //Right child, even
  int Child (theQueue[LChild].priority <= theQueue[RChild].priority? LChild : RChild); //This is the more urgent of the Parent's children (or the left one, if they are equal). 

  //Then, we repeat the process of trickling the Parent (what got moved to the top) downwards, swapping with its more urgent child every time.
  while (theQueue[Parent].priority > theQueue[Child].priority && Child < end) //If the process which we originally moved up is less urgent than it's child, then swap places.
    {
      //Here is the swap of PCB entries.
      PCB temp = theQueue[Parent];
      theQueue[Parent] = theQueue[Child];
      theQueue[Child] = temp;

      //Then, we have to change what slot the Parent and Child ints represent, now that Parent has been moved down and has new children
      Parent = Child;
      LChild = 2*Parent+1;
      RChild = 2*Parent+2;
      Child = (theQueue[LChild].priority <= theQueue[RChild].priority)? LChild : RChild;
    }
}


//This "ages" a process, making it more important every time that it is not executed. So eventually, even a job with a priority of 50 will get done.
//In a real world scenario, this is part of the ready queue which ensures that every job will eventually get run.
void readyqueue::age()
{
  for (int i = 0; i < end; i++)
    theQueue[i].priority--;
}

//This returns the size of the ready queue. (How many elements are in it, not just the index number.)
int readyqueue::size()
{
  return end; 
}

//This prints out a list of jobs which are READY to be run.
void readyqueue::displayQueue()
{
  if (end == 0)  //If there aren't any jobs ready to run, then say so.
    {
      cout << "Warning: Attempted to display ready queue, but it is empty." << endl;
    }

  else 
    {
      cout << "\nDisplaying all processes ready to execute:" << endl;
      cout << " ID\t| Priority" << endl;
      for (int i = 0; i < end; i++)
	{
	  cout << " " << theQueue[i].id << "\t| " << theQueue[i].priority << endl;
	}
    }
}

//This function is used by insertProc and removeHighestProc, checking if a number is even or odd.
//This is important because the heap tree is still just an array structure, it does not use pointers or anything. So to find an element's children, or it's parent, it is necessary to figure out if an element is even or odd.
bool readyqueue::isEven(int slot)
{
  return (slot%2 == 0)? true : false;
}
