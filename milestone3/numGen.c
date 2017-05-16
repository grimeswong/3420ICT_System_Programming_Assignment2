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
#include <stdint.h>   //For using uint16_t

#include "numGen.h"   //customised header file
#include "sema.h"     //Customised semaphore

typedef struct Sem {
  Semaphore numSem1, numSem2;
} Sem_t; // must put semicolon after this structure


/*** Global variable ***/
uint16_t ranNum ;         // random number
FILE *filePtr;            // file pointer
int rt;                   // for error debugging (generic)
uint16_t reserve[65535];  // array that store the temp random number for later use
uint16_t *oriPtr;         // the original position of the pointer which pointer to
struct Sem sem, *semPtr;


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
 void numGenerator() {
   int counter = 0;
   uint16_t *ranPtr = 0;
   ranPtr = &reserve[counter];
   int fd = open("/dev/random", O_RDONLY);                                      //use file desciptor, stream to get random number
   if (fd != -1) {
    //  printf("Successfully create file desciptor\n");                        // debugger: Successfully message
     while(counter < 10) {   //set it back to 65535                                             // 100000 in two seconds, 1000000 in ten seconds, 10000000 in 1 minute
       read(fd, ranPtr, sizeof(ranPtr));
      //  printf("numGenerator: Random number is = %d, counter = %d\n", *ranPtr, counter);        // debugger: get the value of the pointer
      //  printf("numGenerator: reserve[%d] is = %d, counter = %d\n", counter, reserve[counter], counter);
       counter++;
       ranPtr++;
      }
     close(fd);
   } else { perror("Could not open file to get random number"); }           // error message
 }


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
   printf("numConstructor: &b.numPtr[0] (original) address is %p\n", &b.numPtr[0]);

   semPtr = &sem; // assign semaphore pointer
  //  printf("numConstructor: size of b.numPtr is %lu\n", sizeof(b.numPtr));          // 8 bytes for the b.numPtr
   printf("numConstructor: minfill : %d\n", b.minFill);                             // debugger: minimum fill
   printf("numConstructor: maxBuf : %d\n", b.maxBuf);                               // debugger: maximum buffer
   printf("numConstructor: curLevel = %d\n", b.curLevel);                          // debugger: current level
 }


 /*
  *  Function: numDestructor
  *  Description: clean up the memory allocation, (mutex, semaphore if applicated)
  *  Parameter:  None
  *  Return: None
  */
 void numDestructor() {

   /*** clean up the array (set value to 0) ***/
  //  for(int i=0; i < b.maxBuf; i++) {
  //    *(b.numPtr+i) = 0;
  //  }
   /*** end clean up ***/

   b.numPtr = oriPtr; // the pointer point back to the original position
   free(b.numPtr);    // free the allocated memory
   printf("numDestructor: minfill : %d\n", b.minFill);          // debugger:
   printf("numDestructor: maxBuf : %d\n", b.maxBuf);            // debugger:
   printf("numDestructor: curLevel : %d\n", b.curLevel);        // debugger:
 }


 /*
  *  Function: put_buffer()
  *  Description: store the random number in the uint16_t pointer (memory)
  *  Parameter:  None
  *  Return: None
  */
  void put_buffer() {
    for(int i=0; b.curLevel<b.maxBuf; i++) {
      b.numPtr[b.indexIn] = reserve[i];
      printf("put_buffer: b.numPtr[b.indexIn = %d] value is %u    ",  b.indexIn, b.numPtr[b.indexIn]); // debugger:
      printf("put_buffer: b.indexIn is %d   ", b.indexIn); // debugger:
      printf("put_buffer: b.indexOut is %d", b.indexIn); // debugger:
      printf("put_buffer: b.curLevel is %d\n", b.curLevel); // debugger:

      b.indexIn++;
      if(b.indexIn == b.maxBuf) {
        b.indexIn = 0;  // reset to the beginning of an array
      }
      b.curLevel++;
    }
  }

 /*
  *  Function: get_buffer()
  *  Description: get the random number from the numGenerator
  *  Parameter:  None
  *  Return: a unsiged integer 16 bit random number
  */

  uint16_t get_buffer() {                          // get the value from the numGenerator
    ranNum = b.numPtr[b.indexOut];                            //
    b.numPtr[b.indexOut] = 0;                       // clean up the value
    printf("get_buffer: b.numPtr[b.indexOut = %d] value is %u    ",  b.indexOut, b.numPtr[b.indexOut]); // debugger:
    printf("get_buffer: b.indexIn is %d   ", b.indexIn); // debugger:
    printf("get_buffer: b.indexOut is %d   ", b.indexOut); // debugger:
    printf("get_buffer: b.curLevel is %d\n", b.curLevel); // debugger:
    b.indexOut++;
    if(b.indexOut == b.maxBuf) {
      b.indexOut = 0;                             // reset to the begining of an array
    }
    b.curLevel--;
    return ranNum;
  }
