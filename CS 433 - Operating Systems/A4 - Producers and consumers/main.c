/*
Jorge Torres & Kevin Novak
November 10, 2013
CS 433 - Assignment 4
Assignment: Producer and Consumer problem on a bounded buffer. Given a set number of spaces, have some (user-defined) number of threads creating content and putting it in those spaces, and some (user-defined) number of threads consuming that content and removing it from those spaces.
	A mutex lock is used to ensure only one thread (of either kind) may access the buffer contents at a time, and two semaphores are used to keep track of how many spaces in the buffer are empty or full.


This file is main.c - Accept inputs, creating threads and sleep time based off of them.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "buffer.h"

void *producer(void *param);
void *consumer(void *param);

//Main takes in the user's commands (How long to sleep, how many Producer threads, how many consumer threads), validates them, creates the proper number of threads, and then sleeps for the specified amount of time.
int main(int argc, char* argv[])
{
  /*
Get command line arguments
Initialize buffer
create producer threads
create consumer threads
sleep
exit
   */
  srand(time(NULL));//seed the rand time

  if(argc != 4)
    {
      printf("Invalid input. Proper usage: %s <sleep time> <#producers> <#consumers>\n", argv[0]);
      return -1;
    }

  int sleep_time = atoi(argv[1]);//time main should sleep
  if(sleep_time < 1)
    {
      printf("Invalid sleep time (must be an integer greater than 0)\n");
      return -1;
    }
 
  int number_producer = atoi(argv[2]);//number of producer threads
  if(number_producer < 1)
    {
      printf("Invalid number of producers (must be an integer greater than 0)\n");
      return -1;
    }

  int number_consumer = atoi(argv[3]);//number of consumer threads
  if(number_consumer < 1)
    {
      printf("Invalid number of consumers (must be an integer greater than 0)\n");
      return -1;
    }

  char *var1 = "Producer", *var2 = "Consumer";
  pthread_t con[number_consumer], pro[number_producer];//Array of the threads
  //initialize semaphores
  sem_init(&empty, 0, BUFFER_SIZE); //How many slots are empty, initialized to be all of them.
  sem_init(&full, 0, 0);			//How many slots are full, initialized to be 0.
  pthread_mutex_init(&mutex, NULL);//Mutex lock

//Create threads
  int i;
  for(i = 0; i < number_producer; i++)
    {
      pthread_create(&pro[i], NULL, producer, var1); 
    }
  for(i = 0; i < number_consumer; i++)
    {
      pthread_create(&con[i], NULL, consumer, var2);
    }

  sleep(sleep_time);
  return 0;
}
