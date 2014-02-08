/*
Jorge Torres & Kevin Novak
November 10, 2013
CS 433 - Assignment 4
Assignment: Producer and Consumer problem on a bounded buffer. Given a set number of spaces, have some (user-defined) number of threads creating content and putting it in those spaces, and some (user-defined) number of threads consuming that content and removing it from those spaces.
	A mutex lock is used to ensure only one thread (of either kind) may access the buffer contents at a time, and two semaphores are used to keep track of how many spaces in the buffer are empty or full.


This file is buffer.h - Define a buffer, and set up the locks.
*/
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

typedef int buffer_item;
#define BUFFER_SIZE 5

sem_t full;//keeps track of the resource consumed
sem_t empty;//keeps track of the resource available

pthread_mutex_t mutex;//used to protect critical section
