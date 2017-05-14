//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: main.c
//  Purpose: For execute the entire producer/consumer program

#include "numGen.h"

int main()
{

  constructor(5, 100);
  // uint16_t printNum = numGenerator();   // function in numGen.c
  // printf("Random number is %d\n", printNum);

  /*** testing struct buffer's member ***/
  *b.numPtr = 12345;
  *(b.numPtr + 1) = 56789;
  *(b.numPtr + 2) = 12389;
  /*** testing end ***/



  printf("minFill is %d\n", b.minFill);
  printf("maxBuf = %d\n", b.maxBuf);
  printf("curLevel = %d\n", b.curLevel);
  printf("first element in numArray = %u\n", *(b.numPtr));  // %u for unsigned short  remember put type conversion first
  printf("second element in numArray = %u\n", *(b.numPtr + 1));  // %u for unsigned short  remember put type conversion first
  printf("third element in numArray = %u\n", *(b.numPtr + 2));  // %u for unsigned short  remember put type conversion first


  destructor();

  return 0;
}
