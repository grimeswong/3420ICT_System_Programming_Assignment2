//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.h
//  Purpose: Generate Uint 16 bit numbers by the /dev/random

#ifndef _numGen_h
#define _numGen_h

#include <stdint.h>
#include <stdio.h>
#include "sema.h"

/*** Function prototype ***/
void numGenerator();                        // For generate uint16 number
void numConstructor(int minFill, int maxBuf);  // initalise the values
void numDestructor();                          // destroy the memory allocation
void put_buffer();                          // store value of generated number
uint16_t get_buffer();                          // get the value from the numGenerator

typedef struct buffer_t {
  int minFill;      // store the minimum fill number
  int maxBuf;       // store the maximum buffer
  int curLevel;     // store the current buffer status
  int indexIn;     // record the index of last in (Testing)
  int indexOut;    // record the index of last out (Testing)
  uint16_t *numPtr; // pointer point to the array of uint16 number
} buffer;

typedef struct numSem {
  Semaphore numMain, numFull, numEmpty;
} numSem_t; // must put semicolon after this structure


/*** Global variable ***/
buffer b;           // buffer structure
numSem_t sem, *semPtr;       // Semaphore

#endif
