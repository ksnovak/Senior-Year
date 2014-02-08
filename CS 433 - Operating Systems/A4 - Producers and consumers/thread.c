/*
Jorge Torres & Kevin Novak
November 15, 2013
CS 433 - Assignment 4
Assignment: Producer and Consumer problem on a bounded buffer. Given a set number of spaces, have some (user-defined) number of threads creating content and putting it in those spaces, and some (user-defined) number of threads consuming that content and removing it from those spaces.
	A mutex lock is used to ensure only one thread (of either kind) may access the buffer contents at a time, and two semaphores are used to keep track of how many spaces in the buffer are empty or full.


This file is  thread.c - produce or consumes from buffer
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#include "buffer.h"

int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void print_buffer();

//Wait a random amount of time, pick a random integer, and wait until it can store that number in the buffer, and then store it.
void *producer(void *param)
{
  buffer_item item;

  while(1)
    {
      sleep(rand() % 5 + 1);
      item = rand() % 50 + 1;
      sem_wait(&empty);				//Wait for an empty slot
      pthread_mutex_lock(&mutex);	//Take the permission to access the critical section
      if(insert_item(item) == -1)	//Insert content into the slot
	;
      else
	{
	  print_buffer();
	}
      pthread_mutex_unlock(&mutex);	//Free up permission to access the critical section
      sem_post(&full);				//Note for the consumers that another slot is filled up
    }
}

//Wait a random amount of time, and wait until it can remove an element from the buffer, and then remove it.
void *consumer(void *param)
{
  buffer_item item;
  while(1)
    {
      sleep(rand() % 5 +1);
      sem_wait(&full);				//Wait for some content to exist
      pthread_mutex_lock(&mutex);	//Take the permission to access the critical section
      if(remove_item(&item))		//Take content from the slot
	;
      else
	{
	  print_buffer();
	}
      pthread_mutex_unlock(&mutex);	//Free up permission to access the critical section	
      sem_post(&empty);				//Note for the producers that another slot is emptied.
    }
}
