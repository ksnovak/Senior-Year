#include <iostream>
using namespace std;
#include "PCB.h"
#include "readyqueue.h"

int main()
{
  //TEST: Can I make objects? Can I set attribs? Can I overload = properly? Can I print?
  /*  cout << "Making an object with priority 5, id 3." << endl;
  PCB myTask;
  myTask.id = 3;
  myTask.priority = 5;
  cout << "Printing..." << endl;
  myTask.printInfo();

  cout << "Making another task... " << endl;
  PCB anotherTask = myTask;
 
  cout << "PRinting... " << endl;
  anotherTask.printInfo();
  */

  //TEST: Can I make an array with these objects?
  /* 
  cout << "Making a PCB table" << endl;
  PCB myTable[20];
  cout << "Setting values equal to order of adding" << endl;
  for (int i = 0; i < 20; i++)
    {
      myTable[i].id = myTable[i].priority = i;
    }

  cout << "Printing values: " << endl;
  for (int i = 0; i < 20; i++)
    {
      cout <<myTable[i].id << "\t" << myTable[i].priority << endl;
    }
  cout << "Swapping some values" << endl;

  PCB newObj;
  newObj.id = 75;
  newObj.priority = 33;
  myTable[3] = newObj;
  myTable[2] = myTable[19];
  cout << endl << newObj.id << "\t" << myTable[3].id << endl;
  cout << endl << myTable[2].id << endl;
  */
  
  //TEST: Starting out the queue. Can I create one? Can I add a job? Can I print a list?
  /*  readyqueue myQueue;
  PCB newObj;
  newObj.id = 55;
  newObj.priority = 7;
  cout << "Inserting new job with id=55, priority=7" << endl;
  myQueue.insertProc(newObj);
  cout << "Calling .size: " << myQueue.size() << endl;
  cout << "Displaying" << endl;
  myQueue.displayQueue();
  */

  //TEST: Can we add multiple jobs? Will they order properly?
  readyqueue myQueue;
  cout << "Making 3 jobs, adding to rqueue" << endl;
  PCB job1;
  job1.priority = 8;
  job1.id = 77;
  PCB job2;
  job2.priority = 12;
  job2.id = 78;
  PCB job3;
  job3.priority = 4;
  job3.id = 79;
  
  myQueue.insertProc(job1);
  myQueue.insertProc(job2);
  myQueue.insertProc(job3);
  myQueue.displayQueue();


  //TEST: Can we remove jobs now? Will the right one trickle up?
  myQueue.removeHighestProc();
  cout << "Displaying new list" << endl;
  myQueue.displayQueue();
  myQueue.removeHighestProc();
  myQueue.displayQueue();
  myQueue.removeHighestProc();
  myQueue.displayQueue();
  cout << "All jobs are gone now. What if we try to run another?" << endl;
  try {myQueue.removeHighestProc();}
  catch (readyqueue::Underflow)
  {
    cout << "\n\tWARNING: There are no more processes ready to be run yet" << endl;
  }
  myQueue.displayQueue();

}

