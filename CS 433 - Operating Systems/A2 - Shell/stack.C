/*---------------------------------------------------------
Authors: Jorge Torres & Kevin Novak
Date Written: 9-27-2013
Course Number: CS433
Assignment Number: Assignment #2

Program Description:
The program is a shell -- it will accept commands from a user and handle them.
Includes functionality for viewing previously-used functions and shortcuts to execute them.
Also uses ampersands at the end of a command to mean that it is to be run in the background.

This is the stack class, which holds a list of previously used commands, as well as a list of directories with the pushd, popd, and dirs commands.

*///--------------------------------------------------------
#ifndef stack_C
#define stack_C

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "stack.h"


// PURPOSE: constructor which initializes top                                       
stack::stack()
{
  top = -1;
}


// PURPOSE: destructor which does nothing                      
stack::~stack()
{
  clearIt();
}


// PURPOSE: allows client to add items to the stack                                 
// PARAMS:  passes an value to add to the stack                                     
// ALGORITHM: add value to vector increments 
// the number of items in the stack                                      
void stack::push( el_t n )
{
  top++;
  el.push_back(n);
}

// PURPOSE: allows client to remove items from the stack                            
// PARAMS: gives the value of the item being removed to the                         
// value passed by refrence                                                         
// ALGORITH: if not empty, assigns the value of the item being                      
// removed to the value passed, decrements top value by 1                           
void stack::pop()
{
  if(isEmpty())
      throw Underflow();

  el.pop_back();
  top--;
}


// PURPOSE: gives the value of the top item on the stack                            
// PARAMS: gives the value of the item on the top to the                            
// value passed by refrence                                                         
// ALGORITHM: if not empty, assigns the value of the top item                       
// on the stack the to value passed, but does not remove top item                   
void stack::topElem(el_t& n)
{
  if(isEmpty())
      throw Underflow();

  n = el[top];
}

// PURPOSE: checks that the stack is not empty                                      
// PARAMS: none                                                                     
// ALGORITHM: matches the value of top to -1                                        
bool stack::isEmpty()
{
  return (top == -1);
}

// PURPOSE: checks if the stack is full
// PARAMS: none
// ALGORITHM: will always return false
/*
bool stack::isFull()
{
  return false;
}
*/

// PURPOSE: displays all the values currently being held in the vector                                                                     
// PARAMS: none                                                                     
// ALGORITHM: if not empty, uses a for loop to display all                          
// values in stack from 0 to top;              
void stack::displayAll()
{
  if (isEmpty())
    throw Underflow();
  
  //KN: We only want the most recent ten commands, this will make sure that the most recent commands will be picked, and up to ten if possible.
  int min;
  if (top > 9)
    min = top-9;
  else
    min = 0;
  
  for (int i = top; i >= min; i--)
      cout << i << "\t" << el[i] << " " << endl;

  cout << endl;
}

//PURPOSE: Returns the nth element, without removing it from the stack
//PARMS: n, the element desired. If -1, then it will return top.
el_t stack::returnElem(int n)
{
  if (n == -1)
    return el[top];
  else if (n > top) //If what they want is beyond the biggest element in the stack, error
    throw Invalid();
  else
    return el[n];
}


// PURPOSE: empties the stack                                                       
// PARAMS: none                                                                     
// ALGORITHM: pop items from stack until it is empty                                
void stack::clearIt()
{
  while(!isEmpty())
    pop();
}

#endif

