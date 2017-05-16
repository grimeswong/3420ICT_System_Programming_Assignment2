//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: main.c
//  Purpose: For execute the entire producer/consumer program

#include "numGen.h"

#define DEFAULT_MINFILL 0
#define DEFAULT_MAXBUFFER 10

int main()
{

  constructor(DEFAULT_MINFILL, DEFAULT_MAXBUFFER);                // constructor (maxBuf, minFill)

  numGenerator();               // constructor

  put_buffer();

  /*** testing struct buffer's member ***/
  // *b.numPtr = 12345;
  // *(b.numPtr + 1) = 56789;
  // *(b.numPtr + 2) = 12389;
  // *(b.numPtr + 99) = 53548;
  /*** testing end ***/

  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());



  /*** testing the elements in the array ***/
  for (int i=0; i <b.maxBuf; i ++) {
    printf("Main: element in numArray[%d] = %u, current level = %d\n",i, b.array[i], b.curLevel);  // get the value in decimal,  %u for unsigned short  remember put type conversion first
    printf("Main: element in numArray[%d] in hex = %#06hx\n", i, b.array[i]);         // get the value in hex
    printf("Main: element in numArray[%d] address = %p\n", i, &b.array[i]);             // get the address
    printf("current indexIn = %d", b.indexIn);
    printf("current indexOut = %d", b.indexOut);
    printf("current curLevel = %d\n", b.curLevel);
    // printf("Main: get_buffer() = %u\n", get_buffer());
  }

  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());



  // printf("Main: b.indexOut is: %d\n", *(b.indexOut));

  // printf("Testing only: element in numArray[100] = %u\n", *(b.numPtr+100));  // %u for unsigned short  remember put type conversion first
  // printf("65261 in hex is 0x%04x\n", 65261);
  // printf("65261 in hex is %#06x\n", 65261);     // debugger; format of hex
  /*** testing the elements end ***/

   put_buffer();
   for (int i=0; i <b.maxBuf; i ++) {
     printf("Main: element in numArray[%d] = %u, current level = %d\n",i, b.array[i], b.curLevel);  // get the value in decimal,  %u for unsigned short  remember put type conversion first
     printf("Main: element in numArray[%d] in hex = %#06hx\n", i, b.array[i]);         // get the value in hex
     printf("Main: element in numArray[%d] address = %p\n", i, &b.array[i]);             // get the address
     printf("current indexIn = %d", b.indexIn);
     printf("current indexOut = %d", b.indexOut);
     printf("current curLevel = %d\n", b.curLevel);
     // printf("Main: get_buffer() = %u\n", get_buffer());
   }


  destructor();       // destroy all the memory allocation

  return 0;
}
