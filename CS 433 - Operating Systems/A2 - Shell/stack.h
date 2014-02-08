/*---------------------------------------------------------
Authors: Jorge Torres & Kevin Novak
Date Written: 9-27-2013
Course Number: CS433
Assignment Number: Assignment #2

Program Description:
The program is a shell -- it will accept commands from a user and handle them.
Includes functionality for viewing previously-used functions and shortcuts to execute them.
Also uses ampersands at the end of a command to mean that it is to be run in the background.

This file is the stack class header.

*///--------------------------------------------------------
#ifndef stack_H
#define stack_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//typedef char * el_t;    // the el_t type is integer for now                            
                     // el_t is unknown to the client                               
typedef string el_t;

class stack
{

 private: // to be hidden from the client                                           

  vector<el_t> el;         // el is  an vecotr of el_t's                              
  int      top;           // top is index to the top of stack                       

 public: // prototypes to be used by the client                                     

  // exception handling
  //class Overflow{};//thrown when the stack is full
  class Underflow{};//thrown when stack is empty                                    
  class Incomplete{};//thrown when more than one item is left on stack              
  class Invalid{};//thrown when invalid char inputed                                             

  stack();   // constructor                                                    
  ~stack();  // destructor                                                     

  // HOW TO CALL: provide an element to be added                                    
  // PURPOSE: enters an element at the top                                                                  
  void push(el_t n);

  // HOW TO CALL: provide an element to act as a refrence                           
  // PURPOSE: if not empty, removes and gives back the top element     
  void pop(/*el_t& n*/);

  // HOW TO CALL: provide an element to act as a refrence                           
  // PURPOSE: if not empty, gives the top element without removing it               
  void topElem(el_t&);

  // HOW TO CALL: nothing needed to call                                            
  // PURPOSE: if not empty false, else true                                         
  bool isEmpty();

  // HOW TO CALL: nothing needed to call
  // PURPOSE: if not full false, else true
  //bool isFull();

  // HOW TO CALL: nothing needed to call                                            
  // PURPOSE: displays all the values in the stack top to bottom                    
  void displayAll();

  //HOW TO CALL: pass the element number
  // PURPOSE: return the nth element, without removing it from the stack.
  el_t returnElem(int n);

  // HOW TO CALL: nothign needed to call                                            
  // PURPOSE: clears the stack                                                      
  void clearIt();

};

#endif

//end
