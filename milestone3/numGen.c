//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.c
//  Purpose: Generate unsigned int 16 bit numbers by the /dev/random, include functions of number generator, constructor, 
//    destructor, put and get buffer

/*** Header files ***/
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <unistd.h>   //eg. sleep(), execvp(), environ(), pipe()
#include <fcntl.h>    //Access file, file permission, eg. O_CREAT, O_RDONLY, O_WRONLY,
#include <stdint.h>   //For using uint16_t

#include "numGen.h"   //customised header file
#include "sema.h"     //Customised semaphore

/*** Global variable ***/
uint16_t ranNum ;         // random number
FILE *filePtr;            // file pointer
int rt;                   // for error debugging (generic)
uint16_t reserve[65535];  // array that store the temp random number for later use
uint16_t *reservePtr;
uint16_t *oriPtr;         // the original position of the pointer which point to

/*
*  Function: numConstructor
*  Description: initialise the structure of buffer
*  Parameters:  int maxium buffer size (default = 5), int minimum fill (default = 0)
*  Return: None
*/
void numConstructor(minFill, maxBuf) {
  b.minFill = minFill;   // default value = 0
  b.maxBuf = maxBuf;    // default value = 5
  b.curLevel = 0;  // default value = 0
  b.numPtr = calloc(b.maxBuf, sizeof(uint16_t));    // assign the memory by the maximum buffer (Allocates space for an array element, initalizes to zero and then retuuns a pointer to memeory)
  //  b.numPtr = malloc(maxBuf * sizeof(uint16_t));    // assign the memory by the maximum buffer (Allocates requested size of bytes and returns a pointer first byte of allocated space)
  oriPtr = &b.numPtr[0];
  reservePtr = reserve;  // equal = &reserve[0]
  // printf("numConstructor: &b.numPtr[0] (original) address is %p\n", &b.numPtr[0]);      // debugger:

  semPtr = &sem; // assign semaphore pointer
  // printf("numConstructor: size of b.numPtr is %lu\n", sizeof(b.numPtr));      // 8 bytes for the b.numPtr
  // printf("numConstructor: minfill : %d\n", b.minFill);                        // debugger: minimum fill
  // printf("numConstructor: maxBuf : %d\n", b.maxBuf);                          // debugger: maximum buffer
  // printf("numConstructor: curLevel = %d\n", b.curLevel);                      // debugger: current level
  initialiser(&semPtr->numMain);                // initial value = 1
  initialiser(&semPtr->numFull);                // initial value = 1
  initialiser(&semPtr->numEmpty);               // initial value = 1
  semPtr->numFull.value = 0;                    // change initial value = 0
  semPtr->numEmpty.value = 0;                   // change initial value = 0
}


/*  Function: numGenerator();
 *  Description: Generate the unsigned integer number by the /dev/random
 *  Parameter: None
 *  Return: random unsigned integer numbers
 */
 void numGenerator() {
   int counter = 0;
   uint16_t *ranPtr = 0;
   ranPtr = &reserve[counter];
   int fd = open("/dev/random", O_RDONLY);                                       //use file desciptor, stream to get random number
   if (fd != -1) {
    //  printf("Successfully create file desciptor\n");                          // debugger: Successfully message
     while(counter < 65533) {                                                    // 100000 in two seconds, 1000000 in ten seconds, 10000000 in 1 minute
       read(fd, ranPtr, sizeof(ranPtr));
      //  printf("numGenerator: Random number is = %d, counter = %d\n", *ranPtr, counter);        // debugger: get the value of the pointer
      //  printf("numGenerator: reserve[%d] is = %d, counter = %d\n", counter, reserve[counter], counter);
       counter++;
       ranPtr++;
      }
     close(fd);
   } else {
     perror("Could not open file to get random number");
     exit(-1);  // error message: exit with failure
   }
 }


 /*
  *  Function: numDestructor
  *  Description: clean up the memory allocation, (mutex, semaphore if applicated)
  *  Parameter:  None
  *  Return: None
  */
 void numDestructor() {
   /*** deep clean up the array (set value to 0) ***/
  //  for(int i=0; i < b.maxBuf; i++) {
  //    *(b.numPtr+i) = 0;
  //  }
   /*** end clean up ***/
   destructor(&semPtr->numMain);
   destructor(&semPtr->numFull);
   destructor(&semPtr->numEmpty);

   b.numPtr = oriPtr; // the pointer point back to the original position
   free(b.numPtr);    // free the allocated memory (uint16_t)
   free(semPtr);      // free the allocated memory (numSem_t)
 }


 /*
  *  Function: put_buffer()
  *  Description: store the random number in the uint16_t pointer (memory allocation)
  *  Parameter:  None
  *  Return: None
  */
  void put_buffer() {
      b.numPtr[b.indexIn] = *reservePtr;
      // printf("put_buffer: b.numPtr[b.indexIn = %d] value is %d, address is %p\n",  b.indexIn, b.numPtr[b.indexIn], &b.numPtr[b.indexIn]); // debugger:
      reservePtr++;
      b.indexIn++;
      if(b.indexIn == b.maxBuf) { // if indexIn reach maximum buffer index, reset
        b.indexIn = 0;  // reset to the beginning of an array
      }
      b.curLevel++;
  }


 /*
  *  Function: get_buffer()
  *  Description: get the random number from the numGenerator
  *  Parameter:  None
  *  Return: a unsiged integer 16 bit random number
  */

  uint16_t get_buffer() {                                                       // get the value from the numGenerator
        ranNum = b.numPtr[b.indexOut];                                           // get the oldest number
        // printf("get_buffer: b.numPtr[b.indexOut = %d] value is %d    ",  b.indexOut, b.numPtr[b.indexOut]); // debugger:
        b.numPtr[b.indexOut] = 0; /*** clean up the value ***/
        b.indexOut++;
        if(b.indexOut == b.maxBuf) {
          b.indexOut = 0; /*** reset to index of the begining of an array ***/
        }
        b.curLevel--;
    return ranNum;
  }
