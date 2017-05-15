//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: main.c
//  Purpose: For execute the entire producer/consumer program

#include "numGen.h"

int main()
{

  constructor();                // constructor (maxBuf, minFill)
  b.maxBuf = 100;

  uint16_t printNum = numGenerator();   // function in numGen.c
  printf("Main: Random number is %d\n", printNum);

  put_buffer();

  /*** testing struct buffer's member ***/
  // *b.numPtr = 12345;
  // *(b.numPtr + 1) = 56789;
  // *(b.numPtr + 2) = 12389;
  // *(b.numPtr + 99) = 53548;
  /*** testing end ***/


  /*** testint the elements in the array ***/
  for (int i=0; i < b.maxBuf; i ++) {
    --b.curLevel;
    printf("Main: element in numArray[%d] = %u, current level = %d\n",i, *(b.numPtr + i), b.curLevel);  // %u for unsigned short  remember put type conversion first
    printf("Main: element in numArray[%d] in hex = %#06hx\n", i, *(b.numPtr +i));
    printf("Main: element in numArray[%d] address = %p\n", i, (b.numPtr +i));
  }

  // printf("Main: b.indexOut is: %d\n", *(b.indexOut));

  // printf("Testing only: element in numArray[100] = %u\n", *(b.numPtr+100));  // %u for unsigned short  remember put type conversion first
  // printf("65261 in hex is 0x%04x\n", 65261);
  // printf("65261 in hex is %#06x\n", 65261);     // debugger; format of hex


  destructor();       // destroy all the memory allocation


  /*** testing the elements still in the array memory ***/
  // constructor();
  // put_buffer();
  // for (int i=0; i < 100; i ++) {
  //   printf("Main: element in numArray[%d] = %u\n",i, *(b.numPtr + i));  // %u for unsigned short  remember put type conversion first
  // }
  // destructor();
  /*** end of testing ***/

  return 0;
}
