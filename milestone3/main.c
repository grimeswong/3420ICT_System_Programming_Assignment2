//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: main.c
//  Purpose: For execute the entire producer/consumer program


#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
// #include <unistd.h>   //eg. sleep(), execvp(), environ(), pipe()
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
#include "numGen.h"
#include "sema.h"

#define DEFAULT_MINFILL 0
#define DEFAULT_MAXBUFFER 5

/*** Function declaration (prototype) ***/
void *producer(void *arg);
void *consumer(void *arg);

/*** Global variable ***/
int rt = 0;  // for error debugging
int n = 0;
int printNum = 0;

/*
 *  Function: main
 *  Description: created main thread, producer and consumer threads which generate 16bit random integer number
 *  Parameters:  minimum fill, maximum buffer
 *  Return: EXIT_SUCCESS
 */

int main(int argc, char *argv[])
{
  /*** Local variable ***/
  pthread_t producerT, consumerT;
  char readLine[31];
  char *linePtr;
  int arg1;
  int arg2;


  /*** two situations, only one argument or two argument, if one which is the maximum buffer, otherwise Default settings are applied ***/
  if(argc == 2) {
    printf("One argument, argument[1] is %s\n", argv[1]);
    arg1 = DEFAULT_MINFILL;
    arg2 = atoi(argv[1]);
  } else if (argc == 3) {
    printf("Two arguments, argument[1] is %s, argument[2] is %s\n", argv[1], argv[2]);
    arg1 = atoi(argv[1]);
    arg2 = atoi(argv[2]);
  } else {
    printf("Default setting applied\n");
    arg1 = DEFAULT_MINFILL;
    arg2 = DEFAULT_MAXBUFFER;
  }

  numConstructor(arg1, arg2);                // numConstructor (maxBuf, minFill)


  /*** Create the producer child thread ***/
  rt = pthread_create(&producerT, NULL, producer, (void *) semPtr);              // create producer thread
  if(rt != 0) { perror("Main: Couldn't create the producer thread!!!"); }                  // error message:

  /*** Create the consumer thread ***/
  rt = pthread_create(&consumerT, NULL, consumer, (void *) semPtr);              // create consumer thread
  if(rt != 0) { perror("Main: Couldn't create the consumer thread!!!"); }                  // error message:


  /*** while loop  for the user input a number for printing out random numbers ***/
  linePtr = fgets(readLine, 30, stdin);
  if(strcmp(linePtr, "exit\n") == 0) {
    exit(EXIT_SUCCESS);
    numDestructor();       // destroy all the memory allocation
    pthread_exit(NULL);    // The last thing the main should do
  }
  while(strcmp(linePtr,"exit\n") != 0) {
    printNum = atoi(linePtr);
    printf("Number of print is : %d\n", printNum);
    linePtr = fgets(readLine, 30, stdin);
    if(strcmp(linePtr, "exit\n") == 0) {
      exit(EXIT_SUCCESS);
      numDestructor();       // destroy all the memory allocation
      pthread_exit(NULL);    // The last thing the main should do
    }
  }

  /*** Shouldn't use pthread_join this time ***/
  /*** Wait the child thread to join ***/
  // rt = pthread_join(producerT, NULL);    //  wait to other thread to join
  // if (rt != 0) {
  //   perror("Producer thread(s) couldn't join the main thread\n");                 // error message:
  // }
  //
  // rt = pthread_join(consumerT, NULL);    //  wait to other thread to join
  // if (rt != 0) {
  //   perror("Consumer thread(s) couldn't join the main thread\n");                 // error message:
  // }

  return 0;
}

/*  Function: producer(void *arg);
 *  Description: Generate the random number until maximum buffer is reached
 *  Parameter: pointer of data structure of Semaphore
 *  Return: None
 */
void *producer(void *arg) {
  numGenerator();                    // generate number and store in reserve array
  vacate(&semPtr->numEmpty);         // 0 to 1 notify start to fill the array

  while(1) {
    procure(&semPtr->numEmpty);      // lock empty
    procure(&semPtr->numMain);       // lock critical section
    while (b.curLevel < b.maxBuf) {     // if current level reach the maximum buffer, signal consumer
      printf("producer: put_buffer = refill\n");      /*** debugger: ***/
      put_buffer();
    }
    vacate(&semPtr->numMain);      // unlock critical section
    vacate(&semPtr->numFull);      // notify consumer the array has filled

  } //end while

  return NULL;
} // producer end


/*  Function: numGenerator();
 *  Description: get the ranom number until minimum buffer is reached
 *  Parameter: pointer of data structure of Semaphore
 *  Return: None
 */
void *consumer(void *arg) {

  while(1) {
    procure(&semPtr->numFull);        // waiting for the producer filled the array  // 0 to -1
    procure(&semPtr->numMain);        // lock critical section
    while(b.minFill < b.curLevel) {
      // printf("consumer: in minFill loop\n");
      if(printNum > 0) {
        printf("consumer: random number is %#06hx\n", get_buffer());  /*** debugger: output *///
        printNum--;
      }
      if(b.minFill == b.curLevel) {                        // if reach the minFill
        vacate(&semPtr->numEmpty);      // notify producer to filled number in array
      }
    }
    vacate(&semPtr->numMain);         // unlock critical section
  } // while end

  return NULL;
} // consumer end


/*** testing get_buffer ***/
// printf("Main: get_buffer() = %u\n", get_buffer());
// printf("Main: get_buffer() = %u\n", get_buffer());
// printf("Main: get_buffer() = %u\n", get_buffer());
// printf("Main: get_buffer() = %u\n", get_buffer());
// printf("Main: indexIn : %d\n", b.indexIn);          // debugger:
// printf("Main: indexOut : %d\n", b.indexOut);        // debugger:
// printf("Main: curLevel : %d\n", b.curLevel);        // debugger:
/*** end testing get_buffer ***/

/*** testing the member of the array ***/
// for(int i=0; i<b.maxBuf; i++) {
//   printf("Main: b.numPtr[%d] is %d, hex = %#06hx, address = %p\n", i, b.numPtr[i], b.numPtr[i], &b.numPtr[i]);
// }
/*** end testing the member of the array ***/


/*** note only ***/
// printf("65261 in hex is 0x%04x\n", 65261);    // note: format of hex
// printf("65261 in hex is %#06x\n", 65261);     // note: format of hex
/*** end of note ***/
