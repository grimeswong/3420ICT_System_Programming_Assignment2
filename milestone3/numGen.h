//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.c
//  Purpose: Generate Uint 16 bit numbers by the /dev/random

// #include <stdint.h>

/*** Function prototype ***/
uint16_t numGenerator();

/*** Global variable ***/
uint16_t ranNum ;
FILE *filePtr;      //file pointer
