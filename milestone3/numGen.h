//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.h
//  Purpose: Generate Uint 16 bit numbers by the /dev/random

#ifndef _numGen_h
#define _numGen_h

#include <stdint.h>
#include <stdio.h>


/*** Function prototype ***/
uint16_t numGenerator();
void constructor(int maxBuf, int minFill);
void destructor();

typedef struct buffer_t {
  int minFill;      // store the minimum fill number
  int maxBuf;       // store the maximum buffer
  int curLevel;     // store the current buffer status
  uint16_t *numPtr; // pointer point to the array of uint16 number
} buffer;

/*** Global variable ***/
uint16_t ranNum ;
FILE *filePtr;      //file pointer
buffer b;

#endif
