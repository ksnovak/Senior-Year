/*---------------------------------------------------------
Authors: Jorge Torres & Kevin Novak
Date Written: 9-27-2013
Course Number: CS433
Assignment Number: Assignment #2

Program Description:
The program is a shell -- it will accept commands from a user and handle them.
Includes functionality for viewing previously-used functions and shortcuts to execute them.
Also uses ampersands at the end of a command to mean that it is to be run in the background.

This file is the shell class header.
*///--------------------------------------------------------


#ifndef mysh_H
#define mysh_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "stack.h"

class mysh
{
 private:
  stack dirStack;//the stack used to hold directories
  stack history; //KN: History of the last-used commands.
  int status; //used to hold the status of a child process
  pid_t child_process; //holds the PID of the child process
  char str[254];//will hold the user input
  bool cont;//will determine if exit command has been called

 public:
  //sets cont to true
  mysh();

  //display the current accessed directory
  string displayCurrentDir(string path);

  //KN: Execute a previous command, by reading from the history.
  void performPrevious(char * arglist[]);

  //retrieves the command and arguments for the command from user
  void getArguments(char * arg[]);

  //determines the command requested by the user
  void executeCommand( char * arglist[]);

  //exits the shell
  void performExit();

  //chages the accessed directory
  void performChangeDir(char * arglist[]);

  //pushes a directory into the stack
  void performPushd(char * arglist[]);

  //pops a directory from the stack
  void performPopd(char * arglist[]);
  
  //KN: Show history of commands recently used.
  void showHistory();

  //displays all the directories currently in the stack
  void performDirs();

  //executes built in commands in UNIX
  void performExecFile(char * arglist[]);

  //returns the status of the cont variable
  bool getCont();
};

#endif
