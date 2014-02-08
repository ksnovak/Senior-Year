#ifndef main_C
#define main_C
/*---------------------------------------------------------
Authors: Jorge Torres & Kevin Novak
Date Written: 9-27-2013
Course Number: CS433
Assignment Number: Assignment #2

Program Description:
The program is a shell -- it will accept commands from a user and handle them.
Includes functionality for viewing previously-used functions and shortcuts to execute them.
Also uses ampersands at the end of a command to mean that it is to be run in the background.

This file is the client file, which will start accepting user input.

 *///--------------------------------------------------------
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#include "mysh.h"

int main()
{
  char * arguments[15];//holds the argument and its commands, max limit is 15
  mysh newShell;//creates an instance of the shell object used to execute the shell
  while(newShell.getCont())
    {
      cout << "osh " << newShell.displayCurrentDir(getcwd(NULL, 0)) << ">> " << flush;
      newShell.getArguments(arguments); 	//KN: Splits up input arguments and stores them in an array
      newShell.executeCommand(arguments);	//KN: Reads input arguments and determines what to do.
    }
  exit(1);
}

#endif
