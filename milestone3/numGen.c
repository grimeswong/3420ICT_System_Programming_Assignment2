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

/*** Main function for testing only ***/
// int main()
// {
//   numGenerator();
//
//   return 0;
// }


/*  Function: numGenerator();
 *  Description: Generate the unsigned integer number by the /dev/random
 *  Parameter: None
 *  Return: random unsigned integer numbers
 */


 /*** Store in static array ??? ***/


 uint16_t numGenerator() {
   int fd = open("/dev/random", O_RDONLY);                                      //use file desciptor, stream to get random number
   if (fd != -1) {
     read(fd, &ranNum, sizeof(ranNum));
     while(b.curLevel < b.maxBuf) {                                             // 100000 in two seconds, 1000000 in ten seconds, 10000000 in 1 minute
      //  printf("numGenerator: Random number is = %d\n", ranNum);                            // debugger: print number generated
       read(fd, &ranNum, sizeof(ranNum));
       b.curLevel++;
      //  printf("numGenerator: current level: %d\n", b.curLevel);                 // debugger: curLevel
      }
     close(fd);
   } else { perror("Could not open file to get random number"); }           // error message

   return ranNum;
 }


 /*
  *  Function: constructor
  *  Description: initialise the structure of buffer
  *  Parameters:  int maxium buffer size (default = 5), int minimum fill (default = 0)
  *  Return: None
  */
 void constructor() {
   b.minFill = DEFAULT_MINFILL;   // default value = 0
   b.maxBuf = DEFAULT_MAXBUFFER;    // default value = 5
   b.curLevel = 0;  // default value = 0
   b.numPtr = calloc(b.maxBuf, sizeof(uint16_t));    // assign the memory by the maximum buffer (Allocates space for an array element, initalizes to zero and then retuuns a pointer to memeory)
  //  b.numPtr = malloc(maxBuf * sizeof(uint16_t));    // assign the memory by the maximum buffer (Allocates requested size of bytes and returns a pointer first byte of allocated space)

   printf("constructor: size of b.numPtr is %lu\n", sizeof(b.numPtr));          // 8 bytes for the b.numPtr
   printf("constructor: minfill :%d\n", b.minFill);                             // debugger: minimum fill
   printf("constructor: maxBuf :%d\n", b.maxBuf);                               // debugger: maximum buffer
   printf("constructor: curLevel = %d\n", b.curLevel);                          // debugger: current level

 }


 /*
  *  Function: destructor
  *  Description: clean up the memory allocation, (mutex, semaphore if applicated)
  *  Parameter:  None
  *  Return: None
  */
 void destructor() {

   /*** clean up the array (set value to 0) ***/
  //  for(int i=0; i < b.maxBuf; i++) {
  //    *(b.numPtr+i) = 0;
  //  }
   /*** end clean up ***/

   free(b.numPtr);    // free the allocated memory
   //  if (rt != 0) {perror("Couldn't free the memory\n");}   // error message: memory allocation
   //  else {("Successfully free the pointer memory\n"); }
   printf("destructor: minfill :%d\n", b.minFill);
   printf("destructor: maxBuf :%d\n", b.maxBuf);
   printf("destructor: curLevel :%d\n", b.curLevel);
 }


 /*
  *  Function: put_buffer()
  *  Description: store the random number in the uint16_t pointer (memory)
  *  Parameter:  None
  *  Return: None
  */
  void put_buffer() {
    int i = 0;
    for(i=0; i<b.maxBuf; i++) {
      b.numPtr[i] = numGenerator();
    }
    b.indexOut = &b.numPtr[i-1];
    printf("put_buffer: b.numPtr value is: %d\n", *(b.indexOut));   // get the value for the pointer
    printf("put_buffer: b.numPtr address is :%p\n", b.indexOut);    // get the address for the pointer

  }
