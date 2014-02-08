/*Kevin Novak and Jorge Torres
CS 433 - Assignment 5, "Page Replacement"
12/5/2013

This program simulates a computer's page table, with a page replacement algorithm. It accepts 3 inputs: Page size (must be a power of 2), total memory size (power of 2, too), and algorithm(FIFO or LRU).
From there, it creates a page table, with the appropriate size, and starts simulating a process (references.txt) requesting resources at addresses (the values in references.txt). If the value isn't in memory yet, it will bring that value into memory in accordance with the algorithm. From there, if the address is odd, it will write to the address at n-1. If it is even, it will just read from that address.

The FIFO algorithm just replaces items in order of when they were added, like a standard queue.
The LRU algorithm will replace based on when the item was last needed; the one which has been referenced least-recently gets replaced.

Statistics are kept also on time to complete, how many page references are made, how many flushes are done (replacing a modified file), and how many page faults there were.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>

#define FIFO 0
#define LRU 1

struct page
{
  bool valid;	
  bool dirty;	//If the location has been written to
  int address;	
  int lastused;	//In which iteration (starting at 1) of the process that the page was most recently used
};

//Search for an address in the page table. Returns -1 if not found, or the element number if found.
int searchTable(struct page *pageTable, int numOfPages, int value);

int main(int argc, char* argv[])
{
  clock_t start, end;
  start = clock();

  if(argc < 4)
    {
      printf("Usage: %s <page size> <physical size> <algorithm>\n", argv[0]);
      exit(1);
    }

  int pageSize = atoi(argv[1]);
  int physicalSize = atoi(argv[2]);
  int numOfPages = physicalSize/pageSize;	

  //Pages must be 256-8192 (inclusive)
  if(pageSize < 256 || pageSize > 8192)
    {
      printf("ERROR: Valid page sizes are powers of two, between 256 and 8192\n");
      exit(1);
    }

  //Pages must be a power of 2. This does it on the bit level. n^2 will have a most-significant bit of 1, and all the rest 0. n^2-1 will have the opposite. A logical "&" will result in all 0s. Doesn't work for any other number
  //e.g. 4 = 100. 3 = 011. 100 & 011 = 000. On the other hand, 7 = 111. 6 = 110. 111 & 110 = 110. 
  if ((pageSize & (pageSize - 1)) != 0)
  {
    printf("ERROR: Page size must be a power of 2, between 256 and 8192\n");
    exit(1);
  }
  if((physicalSize & (physicalSize -1)) != 0)
    {
      printf("ERROR: Physical size must be a power of two\n");
      exit(1);
    }
	
  int algorithm;
  if (strcmp(argv[3], "LRU") == 0)
    algorithm = LRU;
  else if (strcmp(argv[3], "FIFO") == 0)
    algorithm = FIFO;
  else
    {
      printf("ERROR: Valid algorithms are LRU or FIFO\n");
      exit(1);
    }
  
  printf("Jorge Torres and Kevin Novak\n");
 
  int memoryReferences = 0; //Incremented every time that a process has to look in the memory (done either by looking at the page table, or at the page itself.
  int pageFaults = 0; //Incremented every time that a page is not found in memory
  int flushes = 0; //Incremented every time that a dirty page is victim to page replacement


  //mini has 100 lines, micro has 15 lines. Easier for early testing.
  FILE *file = fopen("references.txt", "r");
  //  FILE *file = fopen("minireference.txt", "r");
  //FILE *file = fopen("microreference.txt", "r");
  if(file == NULL)
    {
      printf("Could not open file\n");
      exit(1);
    }
  
//Create the page table and initialize the relevant values.
  struct page pageTable[numOfPages];
  int i = 0;
  for (i = 0; i < numOfPages; i++)
    {
      pageTable[i].valid = false;
      pageTable[i].dirty = false;
      pageTable[i].lastused = 0;
      pageTable[i].address = 0;
    }


  char line[100];
  int countLine = 0; //For FIFO, this just cycles through the table to pick the victim. For LRU, this is only used in the initial demand paging.
  int iteration = 0;//Iteration of the entire process. Used primarily for finding LRU.

//Read from the file. Try to find the address in memory. If it isn't there, pick a victim and replace it with this address. Then, make the address dirty if needed.
  while (fgets(line, sizeof line, file) != NULL)
    {
      iteration++; 
      int value = atoi(line);

//Check if the address is already in the page table
      bool dirty = value%2; //If the last value is odd, then it will be a dirty bit. Note that if the value is odd, it means to modify the file in address n-1.
      int location = searchTable(pageTable, numOfPages, value-dirty); //Search for the address. Returns -1 if not found, or the address if found.
      memoryReferences++; //Add to memory references, since we just referenced the page table.

//If the value was found
      if (location >= 0)
	{
	  pageTable[location].dirty = dirty; //If the request was dirty, make the location dirty 
	  pageTable[location].lastused = iteration; //Since we just used the page, update this, for the LRU algorithm.
	  memoryReferences++; //Add to memoryReferences, since we just referenced the page in memory
	  continue;
	}

//Otherwise, the page was not in the table, so make a new one and insert it
      else
	{
	  pageFaults++;

	  //Make the page
	  struct page newPage;
	  newPage.valid = true;
	  newPage.dirty = dirty;
	  newPage.address = value-dirty;
	  newPage.lastused = iteration;

	  //Insert. 
	  int victim; //The page to be targetted for replacement
	  //For FIFO, we just add to the next address and wrap around when it gets full
	  if (algorithm == FIFO)
	    {
	      victim = countLine;
	      countLine++;
	      countLine = countLine % numOfPages;
	    }
	  //For LRU, we need to find what page has been used least recently.
	  else if (algorithm == LRU)
	    {
	      //Check if the next page in order has been used. If not, just use that.
	      if (!pageTable[countLine].valid)
		{
		  victim = countLine;
		  countLine++;
		  countLine = countLine % numOfPages;
		}
	      //If it has been used, then we find the most unused page.
	      else
		{
		  int lowestNum = iteration;  //Will be the lowest iteration in which a page was used.
		  int lowestLoc = countLine; //Will be the array element number of that page.
		  for (i = 0; i < numOfPages; i++)
		    {
		      if (pageTable[i].lastused < lowestNum)
			{
			  lowestLoc = i;
			  lowestNum = pageTable[i].lastused;
			}
		    }
		  victim = lowestLoc;
		}
	    }
	  flushes += pageTable[victim].dirty; //If the victim was modified, add to flushes.
	  pageTable[victim] = newPage; //Do the replacement
	  memoryReferences++; //Add to memoryReferences, since we just referenced the page in memory
	}

      //VERBOSE MODE - Prints the value in every page, after every page reference.
      /* printf ("\n");
      for (i = 0; i < numOfPages; i++)
	{
	  if (pageTable[i].address != 0)
	    printf("[%d]\t", pageTable[i].address);
	}*/
      //END VERBOSE MODE

    }//End of the file reading loop

  printf("\nPrinting the page table:\n");
  i = 0;
  for (i = 0; i < numOfPages; i++)
      printf("%d\n", pageTable[i].address);

//Print statistics of the execution
  printf("\nPrinting statistics:\n");
  printf("Memory references:\t%d\n", memoryReferences);
  printf("Page faults:\t\t%d\n", pageFaults);
  printf("Flushes:\t\t%d\n", flushes);
  
  end = clock();
  int elapsed = end - start;
  printf("Elapsed time:\t\t%d\n", elapsed);
}

//Search through the table for a value. If found, return the location. If not found, return -1.
int searchTable(struct page *pageTable, int numOfPages, int value)
{
  int i = 0;
  for (i = 0; i < numOfPages; i++)
    if (pageTable[i].address == value)
      return i;
  
  return -1;
}

