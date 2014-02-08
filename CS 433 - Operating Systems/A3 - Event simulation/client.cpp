/* Jorge Torres
Kevin Novak

10/26/2013
CS 433 - Assignment 3

This program provides discrete event simulation, to simulate a scheduler in a computer.

To run, type ./Assignment3.o X Y  where X is either 1 for First Come, First Serve, or 2 for Shortest Job First, 
and where Y is the number of processes to simulate.*/


#include <iostream>
#include <string>
#include "myclasses.h"

using namespace std;

int main(int argc, char *argv[]){

  simulation d; // declare object type simulation

  int choice; // variable to hold user input for menu selection
  int num; // variable to hold user input for number of processes

  if (argc == 3)
    {
      choice = atoi(argv[1]);
      if (choice != 1 && choice != 2)
	cout << "\nInvalid entry. Usage: ./Assignment3.o [1 for FCFS, 2 for SJF] [Number of processes]" << endl;
      else
	{
	  num = atoi(argv[2]);
	  d.executeSimulation(num, choice);
	}
    }
  else if (argc == 1)
    {  
      while(1) // will loop until user enters '0'
	{ // menu is printed to screen
	  cout << "\n==========================\n";
	  cout << "Choose:\t1. FCFS\t2. SJF\n";
	  cout << "Enter \"0\" to quit.\n";
	  cout << "==========================\n: ";
	  cin >> choice; // user enters selection
	  if(choice == 0)  // if '0' is entered, program ends
	    return 0;
	  else if (choice < 3 && choice > 0)
	    {
	      cout << "How many processes?: "; 
	      cin >> num; 
	      if (num > 1 && num < 1000)
		{  
		  d.executeSimulation(num, choice);
		}
	    }//end of else
	}//end of while
    }
  else
    cout << "\nInvalid entry. Either enter just ./assignment3.o to be guided through the process, or enter ./assignment3.o [1 for FCFS, 2 for SJF] [Number of processes]" << endl;
  return 0;
}//end of main
