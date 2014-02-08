/*
 Jorge Torres & Kevin Novak
 November 10, 2013
 CS 433 - Assignment 4
Assignment: Producer and Consumer problem on a bounded buffer. Given a set number of spaces, have some (user-defined) number of threads creating content and putting it in those spaces, and some (user-defined) number of threads consuming that content and removing it from those spaces.
	A mutex lock is used to ensure only one thread (of either kind) may access the buffer contents at a time, and two semaphores are used to keep track of how many spaces in the buffer are empty or full.

 This file is buffer.c - inserts and removes items, and prints the buffer
 */
#include <stdlib.h>
#include <stdio.h>

#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
int count;	//Count how many objects are in the buffer
int start;	//Where the starting point is
int end;	//Where the ending point is

//Inserts an item into the buffer. Returns 0 for success, or -1 for failure.
int insert_item(buffer_item item)
{
  if(count != BUFFER_SIZE)
    {
      buffer[end] = item;
      printf("Produced: %d ", item);
      end = (end + 1) % BUFFER_SIZE; //Modulus because the contents of this buffer wraps around
      count++;
      return 0;
    }
  return -1;
}

//Removes an item from buffer. Returns 0 for success, or -1 for failure.
int remove_item(buffer_item *item)
{

  if(count > 0)
    {
      item = &buffer[start];
      printf("Consumed %d ", buffer[start]);
      start = (start + 1) % BUFFER_SIZE;	//Modulus because the contents of this buffer wraps around
      count--;
      return 0;
    }
  return -1;
}

//prints the contents of the buffer, taking into consideration the possibility that the buffer contents have wrapped around the array.
void print_buffer()
{
  int i;
  printf("Current buffer - [");
  if(count == 0)
    {
      printf(" Empty ");
    }
  else
    {
	//Figure out where end and start are in relation to each other, because of the wrapping buffer, to properly print all elements.
      if(end > start)
	{
	  i = start;
	  for(i = start; i < end; i++)
	    {
	      printf(" %i ", buffer[i]);
	    }
	}
      if(end <= start)
	{
	  for(i = start; i < BUFFER_SIZE; i++)
	    {
	      printf(" %i ", buffer[i]);
	    }
	  for(i = 0; i < end; i++)
	    {
	      printf(" %i ", buffer[i]);
	    }
	}
    }
  printf("]\n");
}
