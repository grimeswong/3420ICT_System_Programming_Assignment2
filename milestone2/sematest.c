//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sematest.c
//  Purpose: Create threads for synchronisation by using semaphore, firstly, wait for user to type some string, then print out on the screen,
//           after that, prompt the user to press enter key that exit the program

#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <unistd.h>   //eg. sleep
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
#include "sema.h"     // using the file sema.c  // the rest of code will be used here

#define BUFFERSIZE 128

/*** Function declaration (prototype) ***/
void *printline(void *string);

/*** Global variables ***/
int rt = 0;   // catching error


/*
 *  Fucntion: main()
 *  Description: This function is create threads to read string and print string by using semphore for controlling the sequence
 *  Parameter:  None
 *  Return: int 0 if success
 */
int main ()
{

    /*** Local variables ***/
    char charMix[BUFFERSIZE];               // Create an array for maximum 128 characters
    pthread_t t_child;                      // Declare pthread
    Semaphore sem, *semPtr;
    semPtr = &sem;

    /*** Start: initialiser ***/
    rt = initialiser(semPtr);
    if(rt != 0) { perror("Main: couldn't initailise the initaliser"); }           // error message:
    else { printf("Main: Successfully create initialiser\n");}  // debugger:

    semPtr->linePtr = &charMix[0];  //assign ptr to character array

    // printf("Main: Initialised semaphore value is: %d\n", semPtr->value);       // debugger: value
    printf("Main: sem address is: %x\n", (unsigned) semPtr);                      // debugger: address
    procure(semPtr);                                                              // lock the mutex
    printf("Main: locking the mutex now\n");

    /*** Create the child thread ***/
    rt = pthread_create(&t_child, NULL, printline, (void *) semPtr);              // create child thread
    if(rt != 0) { perror("Main: Couldn't create a thread!!!"); }                  // error message:

    // sleep(2);
    printf("Main: printing in the main thread\n");
    /*** Read and print line in the parent thread ***/
    fgets(semPtr->linePtr, BUFFERSIZE, stdin);      // Read the line

    vacate(semPtr);                                                               // notify semaphore


    sleep(3);         // Need to lock it here


    procure(semPtr);
    printf("Main: user has pressed enter\n");
    vacate(semPtr);

    /*** Wait the child thread to join ***/
    rt = pthread_join(t_child, NULL);    //  wait to other thread to join
    if (rt != 0) {
      perror("Child thread(s) couldn't joint the main thread\n");     // error message:
    } else {
      printf("Child thread is gone\n");                               // Prompt:  Confirm the child thread is actually exit
    }

    /*** At the End: destructor ***/
    rt = destructor(semPtr);    //debugger:
    if(rt != 0) { perror("Main: couldn't use destructor"); }               // error message:
    else { printf("Main: Successfully destroy related stuffs\n"); }        // debugger: success

    pthread_exit(NULL);       // The last thing the main should do

    return 0;
}

/*
 *  Description: print out the line of user entered
 *  Parameter: the pointer address of Semaphore
 *             type casting back to strcture Semaphore for access its members (value, linePtr, mutex, condition)
 *  Return: NULL
 */
 void *printline (void *sem)
 {
   procure(sem);
   Semaphore *sPtr = sem;                                                     // type casting: void * back to correct type of Semaphore (aka struct Semaphore)
   printf("Child: sPtr address is %x\n", (unsigned int) sPtr);                // debugger: address
  //  printf("Child: value is %d\n", sPtr->value);                               // debugger: value
   printf("Child: printing in the child thread\n");
   printf("%s", sPtr->linePtr);
   vacate(sem);

   sleep(3);
   procure(sem);
   printf("Child is exiting...\n");
   vacate(sem);
   return NULL;
 }
