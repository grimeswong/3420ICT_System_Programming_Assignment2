//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.h
//  Purpose: Header file for number generator

#ifndef _numGen_h
#define _numGen_h

/*** Header files ***/
#include <stdint.h>
#include <stdio.h>
#include "sema.h"

/*** Function prototype ***/
void numGenerator();                            // For generate uint16 number
void numConstructor(int minFill, int maxBuf);   // initalise the values
void numDestructor();                           // destroy the memory allocation
void put_buffer();                              // store value of generated number
uint16_t get_buffer();                          // get the value from the numGenerator

/*** Global variable ***/
typedef struct buffer {
  int minFill;      // store the minimum fill number
  int maxBuf;       // store the maximum buffer
  int curLevel;     // store the current buffer status
  int indexIn;      // record the index of last in (Testing)
  int indexOut;     // record the index of last out (Testing)
  uint16_t *numPtr; // pointer point to the array of uint16 number
} buffer_t;

typedef struct numSem {
  Semaphore numMain, numFull, numEmpty;
} numSem_t;         // must put semicolon after this structure

buffer_t b;                   // buffer structure
numSem_t sem, *semPtr;        // Semaphore

#endif
