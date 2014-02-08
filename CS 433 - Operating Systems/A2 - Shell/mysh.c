/*---------------------------------------------------------
Authors: Jorge Torres & Kevin Novak
Date Written: 9-27-2013
Course Number: CS433
Assignment Number: Assignment #2

Program Description:
The program is a shell -- it will accept commands from a user and handle them.
Includes functionality for viewing previously-used functions and shortcuts to execute them.
Also uses ampersands at the end of a command to mean that it is to be run in the background.

This file is the shell class, which handles those things.
*///--------------------------------------------------------


#ifndef mysh_C
#define mysh_C

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "mysh.h"

//---------------------------------------------------
//sets cont to true and instantiates the object
mysh::mysh()
{ 
  cont = true;
}

//----------------------------------------------------
//gets user input and parses the input for command and arguments
//using the string tokenizer to break up the arguments
//KN: Also adds the string to history.
void mysh::getArguments(char * arg[])
{
  memset(&arg[0], '\0', sizeof(arg));//fills array with null-string, clearing it
  int index = 0; 
  cin.getline(str, 254); //KN: str is where the characters will be stored, 254 is max size.
  
  //KN: Check if they sent a blank command (just pressed enter). This would segfault otherwise.
  if (strcmp(str, "") == 0)
    {
      cout << "Error: Can't send blank commands. Try again." << endl;
      getArguments(arg);
    }  

  //KN: Otherwise, we're going to take the input and turn it into tokens that can be individually processed.
  char * token = strtok(str, " ");//used to holds the different arguments //KN: strtok splits str into separate strings, delimited by space in this case.
  string mystring = ""; //KN: String to be put into history.
  
  //KN: This while loop will put an argument token into the argument array, then go to the next token and the next array element, until it reaches a null token.
  while(token != NULL)
    {
      arg[index] = token;
      token = strtok(NULL, " ");
      mystring = mystring + std::string(arg[index]) + " ";
      index++;	
    }

  //KN: We don't want to have any "history" or "!n" calls within the history listing. Push into history otherwise
  if (strcmp(arg[0], "history") != 0 && arg[0][0] != '!')
    history.push(mystring);

  arg[index] = '\0'; //KN: Make sure the argument array is null-terminated.
}

//----------------------------------------------------
//determines the command invoked by the user based on the first argument entered.
void mysh::executeCommand(char * arglist[])
{
  //KN: strcmp is string compare. 0 value means the strings are the same. [0] is the first TOKEN. We already made sure this is not all null.
  if(strcmp(arglist[0], "exit") == 0)	
    performExit();
  else if(strcmp(arglist[0], "cd") == 0)
    performChangeDir(arglist);
  else if(strcmp(arglist[0], "pushd") == 0)
    performPushd(arglist);
  else if(strcmp(arglist[0], "popd") == 0)
    performPopd(arglist);
  else if (strcmp(arglist[0], "history") == 0)
    showHistory();
  else if(strcmp(arglist[0], "dirs") == 0)
    performDirs();
  else if (arglist[0][0] == '!')	//KN: Command starting with ! means they want to repeat something from history
    performPrevious(arglist);
  else //KN: If the string does not match some predefined commands, then execute normally.
    performExecFile(arglist);
}

//-----------------------------------------------------
//sets the cont variable to false, signaling an exit command
void mysh::performExit()
{
  cont = false;
  exit(1);
}

//------------------------------------------------------
//performs a previously-executed command, by reading from the history.
void mysh::performPrevious(char * arglist[])
{
  //KN: Make a substring from the input.
  char substr[2];
  memcpy(substr, &arglist[0][1], 2);
  substr[2] = '\0';

  //Figure out what element to grab
  int elem = 0;           //KN: Elem is what gets passed to find history. 
  if (substr[0] == '!')   //KN: !! means they want to repeat the very latest command.
      elem = -1;
  else if (substr[0] >= '0' && substr[0] <= '9') //KN: Else, they want to get the nth command
      elem = atoi(substr);
  else  //Invalid command
      return;

  //Now that we have the element number, return the element to a character array.
  char *command;
  try { command = (char*)history.returnElem(elem).c_str(); } 
  catch(stack::Invalid) //If the element does not exist in history, then exit.
    {
      cout << "No such command in history" << endl;
      return;
    }

  //KN: Turn the command into tokens, and store them into the arglist array
  char * token = strtok(command, " ");
  memset (&arglist[0], '\0', sizeof(arglist)); //KN: Clear what was previously in the array
  int index = 0;
  while (token != NULL) 
    {
      arglist[index] = token;
      token = strtok(NULL, " ");
      index++;
    }
  arglist[index] = '\0'; //KN: Terminate the arglist with a null character.

  //KN: And then execute from that arglist array.
  executeCommand(arglist);
}

//-----------------------------------------------------
//changes the directory to the second argument passed
void mysh::performChangeDir(char * arglist[])
{
  int changeDir = chdir(arglist[1]);//used to determine valid directory
  if(changeDir == -1)//checks that it is a valid directory
    {
      perror("Failed");
      return;
    }
}

//-----------------------------------------------------
//pops the current directory into the stack and moves to that
//directory
void mysh::performPushd(char * arglist[])
{
  string currentdir = getcwd(NULL, 0);
  int changeDir = chdir(arglist[1]);//used to determine valid directory
  if(changeDir == -1)//checks that it is a valid directory
    {
      perror("Failed");
      return;
    }
  dirStack.push(currentdir);
}

//-----------------------------------------------------
//pops the top directory from the stack
void mysh::performPopd(char * arglist[])
{
  if(dirStack.isEmpty())
    {
      cout << "mysh push: stack is empty" << endl;
      return;
    }
  int changedir = chdir("..");//moves back the previous direcoty
  if(changedir == -1)
    {
      perror("Failed");
      return;
    }
  dirStack.pop();
}

//-----------------------------------------------------
//KN: Displays most recently used commands -- up to 10.
void mysh::showHistory()
{
  if (history.isEmpty())
    {
      cout << "No recent commands." << endl;
      return;
    }
  history.displayAll();
}

//-----------------------------------------------------
//displays all the directories currently in the stack
void mysh::performDirs()
{
  if(dirStack.isEmpty())
    {
      cout << "Stack is empty" << endl;
      return;
    }
  dirStack.displayAll();
}

//-----------------------------------------------------
//creates a child process, if the command is valid invokes the file needed. Else returns an error.
//KN: If there is an & in the command, then the parent will not wait for the child to finish. 
void mysh::performExecFile(char * arglist[])
{
  //KN: Find the end of the arg list. Important for the processes to be run in background -- 
  //KN: If the last character is an ampersand, remove that token (or it messes with the execvp).
  int index = 0;
  while (arglist[index] != NULL)
    index++;
  if (std::string(arglist[index-1]) == "&")
      arglist[index-1] = '\0';


  //Create the child and execute it.
  child_process = fork();
  if(child_process == 0) //KN: This is the section processed by the child.
    {
      execvp(arglist[0], arglist);	//KN: excute(filename, list of arguments)
      perror("Failed");
      exit(0);  //exits child process, 0 represents success.
    }
  else if(child_process == -1)	//KN: -1 is an error case.
    {
      printf("ERROR\n");
      return;
    }

  //KN: If the very last element was an ampersand, we set it to a null at the start of this function.
  //KN: So if there is NOT a null at the last element, then we DO want to wait.
  if (arglist[index-1] != '\0')
      wait(&status); //KN: Parent waits till child has exited to continue, if there is no &.
}

//-----------------------------------------------------
//returns the value of cont -- for determining whether or not to exit
bool mysh::getCont()
{
  return cont;
}

//-----------------------------------------------------
//returns only the name of the directory, not the full path
string mysh::displayCurrentDir(string path)
{
  return path.substr(path.find_last_of('/') + 1);
}
#endif
