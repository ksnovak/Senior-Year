/* This is the process control block class. Every process within the system is of this class.

*/
#include <iostream>
using namespace std;
#include "PCB.h"


PCB::PCB()
{
  priority = 99;
  id = 99;
  state = "READY";
}

PCB::~PCB()
{
}

//This overloads the = operator, so that we can set one PCB object equal to another, which is important for the insertion and removal process.
PCB& PCB::operator=(PCB& source)
{
  this->priority = source.priority;
  this->id = source.id;
  this->state = source.state;
}
