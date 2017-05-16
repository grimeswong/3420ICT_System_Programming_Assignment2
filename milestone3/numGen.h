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
void numGenerator();                        // For generate uint16 number
void constructor();  // initalise the values
void destructor();                          // destroy the memory allocation
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

// /*** Global variable ***/
buffer b;           // buffer structure

#endif
