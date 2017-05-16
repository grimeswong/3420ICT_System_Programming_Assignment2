//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sematest.c
//  Purpose: Create threads for synchronisation by using semaphore, firstly, wait for user to type some string, then print out on the screen,
//           after that, prompt the user to press enter key that wait for the child thread to join and exit the program

#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp
#include <unistd.h>   //eg. sleep
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
#include "sema.h"     // using the file sema.c  // the rest of code will be used here

#define BUFFERSIZE 128

/*** Function declaration (prototype) ***/
void *printline(void *string);

/*** Global variables ***/
int rt = 0;   // for catching error

/*** Structure to store semaphore and string (input) ***/
struct DataSem {
  char *linePtr;
  Semaphore sem1, sem2;
} DataSem; // must put semicolon after this structure

/*
 *  Fucntion: main()
 *  Description: This function is create threads to read string and print string by using semphore for controlling sequence
 *  Parameter:  None
 *  Return: int 0 if success
 */
int main ()
{
    /*** Local variables ***/
    char charMix[BUFFERSIZE];               // Create an array for maximum 128 characters
    pthread_t t_child;                      // Declare pthread
    struct DataSem data, *dataPtr;          // Declare DataSem
    dataPtr = &data;                        // Assign pointer

    // semPtr = (Semaphore *) malloc(sizeof(Semaphore *));
    // semPtr = &sem;

    /*** Start: initialiser ***/
    rt = initialiser(&dataPtr->sem1);
    if(rt != 0) { perror("Main: couldn't initailise the initaliser"); }           // error message:
    // else { printf("Main: Successfully create initialiser\n");}  // debugger:
    rt = initialiser(&dataPtr->sem2);
    if(rt != 0) { perror("Main: couldn't initailise the initaliser"); }           // error message:
    // else { printf("Main: Successfully create initialiser\n");}  // debugger:

    dataPtr->linePtr = &charMix[0];  //assign ptr to character array

    // printf("Main: Initialised semaphore value is: %d\n", semPtr->value);       // debugger: value
    // printf("Main: sem address is: %x\n", (unsigned) dataPtr->sem1);            // debugger: address
    // printf("Main: locking the mutex now\n");                                      //debugger:

    procure(&dataPtr->sem1);       // notify child thread:   sem1: 1 to 0

    /*** Create the child thread ***/
    rt = pthread_create(&t_child, NULL, printline, (void *) dataPtr);              // create child thread
    if(rt != 0) { perror("Main: Couldn't create a thread!!!"); }                  // error message:

    // printf("Main: printing in the main thread\n");                                // debugger:

    /*** Read and print line in the parent thread ***/
    fgets(dataPtr->linePtr, BUFFERSIZE, stdin);       // Read the line
    vacate(&dataPtr->sem1);                           // notify child thread:   sem1: -1 to 0

    procure(&dataPtr->sem2);                          // sem2: -1 // wait for signal from child thread
    printf("Please press enter to exit\n");           // Prompt:
    while(strcmp(fgets(dataPtr->linePtr, BUFFERSIZE, stdin), "\n")) {
      printf("Please press enter to exit\n");         // Prompt:
    }

    vacate(&dataPtr->sem1);       // notify child thread    sem1: -1 to 0


    /*** Wait the child thread to join ***/
    rt = pthread_join(t_child, NULL);    //  wait to other thread to join
    if (rt != 0) {
      perror("Child thread(s) couldn't joint the main thread\n");                 // error message:
    } else {
      printf("Child thread is gone\n");                                           // Prompt:  Confirm the child thread is actually exit
    }

    /*** At the End: destructor ***/
    rt = destructor(&dataPtr->sem1);    //debugger:
    if(rt != 0) { perror("Main: couldn't use destructor"); }                      // error message:
    // else { printf("Main: Successfully destroy related stuffs\n"); }            // debugger: success

    pthread_exit(NULL);       // The last thing the main should do

    return 0;
}

/*
 *  Description: print out the line of user entered
 *  Parameter: the pointer of struct DataSem
 *             type casting back to strcture DataSem for access its members (linePtr, Semaphore)
 *  Return: NULL
 */
 void *printline (void *data)
 {
  //  sleep(10);   // for testing
   struct DataSem *dPtr = data;                                                  // type casting: void * back to correct type of Semaphore (aka struct Semaphore)
  //  printf("Child: sPtr address is %x\n", (unsigned int) &dPtr->sem1);         // debugger: address
  //  printf("Child: value is %d\n", sPtr->value);                               // debugger: value
   procure(&dPtr->sem2);                                  // lock sem2           //sem2 1 to 0
   procure(&dPtr->sem1);                                  // sem1 -1
  //  printf("Child: printing in the child thread\n");                              // debugger: message
   printf("%s", dPtr->linePtr);

   vacate(&dPtr->sem2);     // notify main thread        // notify main thread sem2 0 to 1

   procure(&dPtr->sem1);    // wait to main thread signal // -1
  //  sleep(3);                                                                    // debugger:
   printf("Child is exiting...\n");

   return NULL;
 }
