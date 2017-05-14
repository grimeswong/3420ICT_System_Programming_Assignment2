//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.c
//  Purpose: Header file for number generator

// Header files
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <unistd.h>   //eg. sleep(), execvp(), environ(), pipe()
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp
#include <errno.h>    //Error number handling library eg. errno
#include <fcntl.h>    //Access file, file permission, eg. O_CREAT, O_RDONLY, O_WRONLY,
#include <stdint.h>

#include "numGen.h"

/*** Function prototype ***/
uint16_t numGenerator();
void constructor(int maxBuf, int minFill);
void destructor();

/*** Global variable ***/
int rt;   // for error debugging

/*** Main function for testing only ***/
// int main()
// {
//   numGenerator();
//
//   return 0;
// }

/*  numGenerator();
 *  Description: Generate the unsigned integer number by the /dev/random
 *  Parameter: None
 *  Return: random unsigned integer numbers
 */
 uint16_t numGenerator() {
   int counter = 1;    // debugger: testing the speed

   int fd = open("/dev/random", O_RDONLY);   //use file desciptor, stream to get random number
   if (fd != -1) {
     read(fd, &ranNum, sizeof(ranNum));
     while(counter<1000) { // 100000 in two seconds, 1000000 in ten seconds, 10000000 in 1 minute
      //  printf("Random number is = %d\n", ranNum);     //debuger: print number generated
       read(fd, &ranNum, sizeof(ranNum));
       counter++;         // debugger: testing the speed
      //  sleep(1);
     }
     close(fd);
   }

   return ranNum;
 }

 /*
  *  Fucntion: constructor
  *  Description: initialise the structure of buffer
  *  Parameters:  int maxium buffer size, int minimum fill
  *  Return: None
  */
 void constructor(int maxBuf, int minFill)
 {
   b.minFill = minFill;
   b.maxBuf = maxBuf;
   b.curLevel = 0;
  //  b.numPtr = malloc(maxBuf * sizeof(uint16_t));    // assign the memory by the maximum buffer (Allocates requested size of bytes and returns a pointer first byte of allocated space)
   b.numPtr = calloc(maxBuf, sizeof(uint16_t));    // assign the memory by the maximum buffer (Allocates space for an array element, initalizes to zero and then retuuns a pointer to memeory)
 }

 /*
  *  Fucntion: destructor
  *  Description: clean up the mutex, semaphore, memory allocation
  *  Parameter:  None
  *  Return: None
  */
 void destructor()
 {


   free(b.numPtr);
  //  if (rt != 0) {perror("Couldn't free the memory\n");}   // error message: memory allocation
  //  else {("Successfully free the pointer memory\n"); }
 }
