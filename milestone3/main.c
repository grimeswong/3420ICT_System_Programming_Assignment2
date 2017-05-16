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
  printf("Main: indexIn : %d\n", b.indexIn);          // debugger:
  printf("Main: indexOut : %d\n", b.indexOut);            // debugger:
  printf("Main: curLevel : %d\n", b.curLevel);        // debugger:
  /*** end testing get_buffer ***/

  /*** testing the member of the array ***/
  for(int i=0; i<b.maxBuf; i++) {
    printf("Main: b.numPtr[%d] is %d, hex = %#06hx, address = %p\n", i, b.numPtr[i], b.numPtr[i], &b.numPtr[i]);
  }
  /*** end testing the member of the array ***/

  put_buffer();

  /*** testing the member of the array ***/
  for(int i=0; i<b.maxBuf; i++) {
    printf("Main: b.numPtr[%d] is %d, hex = %#06hx, address = %p\n", i, b.numPtr[i], b.numPtr[i], &b.numPtr[i]);
  }
  /*** end testing the member of the array ***/

  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: indexIn : %d\n", b.indexIn);          // debugger:
  printf("Main: indexOut : %d\n", b.indexOut);        // debugger:
  printf("Main: curLevel : %d\n", b.curLevel);        // debugger:

  /*** testing the member of the array ***/
  for(int i=0; i<b.maxBuf; i++) {
    printf("Main: b.numPtr[%d] is %d, hex = %#06hx, address = %p\n", i, b.numPtr[i], b.numPtr[i], &b.numPtr[i]);
  }
  /*** end testing the member of the array ***/

  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: get_buffer() = %u\n", get_buffer());
  printf("Main: indexIn : %d\n", b.indexIn);          // debugger:
  printf("Main: indexOut : %d\n", b.indexOut);        // debugger:
  printf("Main: curLevel : %d\n", b.curLevel);        // debugger:

  /*** testing the member of the array ***/
  for(int i=0; i<b.maxBuf; i++) {
    printf("Main: b.numPtr[%d] is %d, hex = %#06hx, address = %p\n", i, b.numPtr[i], b.numPtr[i], &b.numPtr[i]);
  }
  /*** end testing the member of the array ***/


  /*** note only ***/
  // printf("65261 in hex is 0x%04x\n", 65261);    // note: format of hex
  // printf("65261 in hex is %#06x\n", 65261);     // note: format of hex
  /*** end of note ***/



  numDestructor();       // destroy all the memory allocation

  return 0;
}
