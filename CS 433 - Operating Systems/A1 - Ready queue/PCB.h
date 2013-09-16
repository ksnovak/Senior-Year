/* This is the process control block class. Every process within the system is of this class.

*/
#include <iostream>
using namespace std;

class PCB {

 public:
  int id; //Every process will have a unique ID.
  string state; //NEW, READY, RUNNING, WAITING, TERMINATED
  int priority; //How important the task is. 1-50 (1 is most important). Gets decremented every time that a task is ignored.
  
  PCB();
  ~PCB();
  PCB& operator= (PCB& source); //Overload the = operator, used for swapping entries in the ready queue with a simple command.

};
