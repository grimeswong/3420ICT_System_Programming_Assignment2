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

  numConstructor(DEFAULT_MINFILL, DEFAULT_MAXBUFFER);                // numConstructor (maxBuf, minFill)

  numGenerator();               // numConstructor

  put_buffer();

  /*** testing get_buffer ***/
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  /*** end testing get_buffer ***/

  /*** testing the member of the array ***/
  for(int i=0; i<b.maxBuf; i++) {
    printf("\nMain: b.numPtr[%d] is %d\n", i, b.numPtr[i]);
  }
  /*** end testing the member of the array ***/

  put_buffer();

  /*** testing the member of the array ***/
  for(int i=0; i<b.maxBuf; i++) {
    printf("\nMain: b.numPtr[%d] is %d\n", i, b.numPtr[i]);
  }
  /*** end testing the member of the array ***/

  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());

  /*** testing the member of the array ***/
  for(int i=0; i<b.maxBuf; i++) {
    printf("\nMain: b.numPtr[%d] is %d\n", i, b.numPtr[i]);
  }
  /*** end testing the member of the array ***/

  /*** testing the elements in the array ***/
  // for (int i=0; i <b.maxBuf; i ++) {
  //   printf("Main: element in b.numPtr[%d] = %u, current level = %d   ",i, b.numPtr[i], b.curLevel);  // get the value in decimal,  %u for unsigned short  remember put type conversion first
  //   printf("Main: element in b.numPtr[%d] in hex = %#06hx   ", i, b.numPtr[i]);         /*** get the value in hex ***/
  //   printf("Main: element in b.numPtr[%d] address = %p\n", i, &b.numPtr[i]);             // get the address
  //   printf("current indexIn = %d   ", b.indexIn);
  //   printf("current indexOut = %d   ", b.indexOut);
  //   printf("current curLevel = %d\n", b.curLevel);
    // printf("Main: get_buffer() = %u\n", get_buffer());
  // }

  // printf("Main: b.indexOut is: %d\n", *(b.indexOut));

  // printf("Testing only: element in b.numPtr[100] = %u\n", *(b.numPtr+100));  // %u for unsigned short  remember put type conversion first
  // printf("65261 in hex is 0x%04x\n", 65261);
  // printf("65261 in hex is %#06x\n", 65261);     // debugger; format of hex
  /*** testing the elements end ***/




  numDestructor();       // destroy all the memory allocation

  return 0;
}
