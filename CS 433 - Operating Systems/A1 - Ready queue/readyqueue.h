/* This is the ready queue class. It holds all of the READY processes and executes them according to a priority level.

*/
#include <iostream>
using namespace std;


class readyqueue {

 protected:
  PCB theQueue[10]; //The actual queue of jobs ready to run. In this case, we will never exceed 10 jobs. Can be increased as needed.
  int end;
  
 public:
  //Error handling classes
  class Underflow{};//Ran out of tasks to process
  class Overflow{};//Too many tasks, can't add new ones
  class Illegal{}; //Invalid job priority
  
  readyqueue();
  ~readyqueue();
  void insertProc(PCB newProcess); //Adds a process into the ready queue. This means it is READY
  void removeHighestProc(int &returnval); //Remove and return the PCB with the highest priority from the queue. This means it is RUNNING
  void reheapify(); //Used after removing a process, to find what is now the most urgent job, and reorder appropriately.
  void age(); //Used for test 2. "ages" processes, meaning they gradually become more important as they stay in the queue longer. 
  int size(); //Return the number of elements in the queue
  void displayQueue(); //Display the IDs and priorities of processes in the queue
  bool isEven(int slot); //Checks if a number is even or odd. Used for rearranging processes.
};
