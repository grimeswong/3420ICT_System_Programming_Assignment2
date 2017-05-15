//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.h
//  Purpose: Generate Uint 16 bit numbers by the /dev/random

#ifndef _numGen_h
#define _numGen_h

#include <stdint.h>
#include <stdio.h>

#define DEFAULT_MINFILL 0
#define DEFAULT_MAXBUFFER 5

/*** Function prototype ***/
uint16_t numGenerator();                    // For generate uint16 number
void constructor();  // initalise the values
void destructor();                          // destroy the memory allocation
void put_buffer();                          // store value of generated number


typedef struct buffer_t {
  int minFill;      // store the minimum fill number
  int maxBuf;       // store the maximum buffer
  int curLevel;     // store the current buffer status
  uint16_t *indexIn;     // record the index of last in (Testing)
  uint16_t *indexOut;    // record the index of last out (Testing)
  uint16_t *numPtr; // pointer point to the array of uint16 number
} buffer;

/*** Global variable ***/
uint16_t ranNum ;   // random number
FILE *filePtr;      // file pointer
buffer b;           // buffer structure
int rt;             // for error debugging (generic)
int fd;             // for error debugging (file descriptor)

#endif
