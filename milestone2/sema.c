//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sema.c
//  Purpose: Use the semaphores to create a thread for synchronisation

/*** Preprocessor ***/
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <unistd.h>   //eg. sleep
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
#include "sema.h"

#define BUFFERSIZE 128

/*** Function declartion (Prototype) ***/
void procure(Semaphore *semaphore);
void vacate(Semaphore *semaphore);
int initialiser();
int semDestructor();

/*** Function declaration (prototype) ***/
void *printline(void *string);

Semaphore sem, *semPtr;


int rt;   // for debugging

/*
 *  Fucntion: main()
 *  Description: This function is create threads to read string and print string by using semphore for controlling the sequence
 *  Parameter:  None
 *  Return: int 0 if success
 */
int main ()
{

    /*** Local variables ***/
    int rt; // for catching error
    char charMix[BUFFERSIZE];               // Create an array for maximum 128 characters

    pthread_t t_child;

    //Start: initialiser
    rt = initialiser();   //debugger:
    semPtr->linePtr = &charMix[0];

    if(rt != 0) { perror("Main: couldn't initailise the initaliser"); }          // error message:
    // else { printf("Main: Successfully create initialiser\n");}  // debugger:

    // printf("Main: Initialised semaphore value is: %d\n", semPtr->value);         // debugger: value
    printf("Main: sem address is: %x\n", (unsigned) semPtr);                        // debugger: address
    procure(semPtr);                                                              // lock the mutex
    printf("Main: locking the mutex now\n");

    /*** Create the child thread ***/
    rt = pthread_create(&t_child, NULL, printline, (void *) semPtr);               //create child thread
    if(rt != 0) { perror("Main: Couldn't create a thread!!!"); }                 // error message:

    // sleep(2);
    printf("Main: printing in the main thread\n");
    /*** Read and print line in the parent thread ***/
    fgets(semPtr->linePtr, BUFFERSIZE, stdin);      // Read the line
    // trimnewline(dataMutex1.linePtr);                   // Trim the newline character
    vacate(semPtr);


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
    //At the End: destructor
    rt = destructor();    //debugger:
    if(rt != 0) { perror("Main: couldn't use destructor"); }               // error message:
    else { printf("Main: Successfully destroy related stuffs\n"); }  // debugger:



    return 0;
}

/*
 *  Fucntion: initialiser
 *  Description: This function is for initialise the semaphore, mutex and the condition variable
 *  Parameter:  None
 *  Return: int 0 if success
 */
int initialiser()
{

  /*** Intialize Pointer ***/
  semPtr = malloc(sizeof(&sem));
  semPtr = &sem;
  // printf("Initialiser: sem address: %x\n", (unsigned int) semPtr);                          // debugger: address

  /*** Initialize semaphore value ***/
  semPtr->value = 1;    // 1 is correct, wait is 0
  // printf("sem->value is %d\n", semPtr->value);                                           //debugger: value

  /*** Initialize mutex ***/
  rt = pthread_mutex_init(&semPtr->mutex, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a mutex\n"); }                     // error message:
  // else { printf("initialiser: Successfully initialise a mutex\n");}                         // debugger: success

  /*** Initialize condition variable ***/
  rt = pthread_cond_init(&semPtr->condition, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a condition variable\n"); }        // error message:
  // else { printf("initialiser: Successfully initialise a condition variable\n");}            // debugger: success

  return 0; //return 0 if success
}

/*
 *  Fucntion: destructor
 *  Description: Cleans up semaphores, mutex, condition variable, and release memory allocation
 *  Parameter:  None
 *  Return: int 0 if success
 */
int destructor()
{

  /*** destruct the mutex ***/
  rt = pthread_mutex_destroy(&sem.mutex);
  if(rt != 0) { perror("destructor: couldn't destruct a mutex\n"); }                         // error message:
  // else { printf("destructor: Successfully destruct a mutex\n");}                             // debugger:

  /*** destruct the condition variable ***/
  rt = pthread_cond_destroy(&sem.condition);
  if(rt != 0) { perror("destructor: couldn't destruct a condition variable\n"); }            // error message:
  // else { printf("destructor: Successfully destruct a condition variable\n");}                             // debugger:

  return 0; //return 0 if success
}

/*
 *  Fucntion: procure (Same function as semWait())
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
void procure(Semaphore *semaphore)
{
  //   begin_critical_section(semaphore);  // make the following concurrency-safe
  //   while (semaphore->value <= 0)
	// wait_for_vacate(semaphore);     // wait for signal from vacate()
  //   semaphore->value--;                 // claim the Semaphore
  //   end_critical_section(semaphore);


  // printf("procure: sem address is %x\n", (unsigned int) semaphore);             // debugger: address
  rt = pthread_mutex_lock (&semaphore->mutex);
  if (rt != 0) { printf("procure: Can't not get the lock\n"); }
  // else { printf("procure: get the lock\n"); }                                      // debugger: success
  // printf("procure: sem address is %x\n", (unsigned int) semaphore);             // debugger: address
  // printf("procure: locking\n");                                                    //debugger:
  // printf("procure: pre value is: %d\n", semaphore->value);

  while(semaphore->value <= 0) {
    // printf("procure loop: locking\n");                                             // debugger:
    pthread_cond_wait(&semaphore->condition, &semaphore->mutex);
  }
  semaphore->value--;

  rt = pthread_mutex_unlock(&semaphore->mutex);
  // printf("procure: post value is: %d\n", semaphore->value);

}


/*
 *  Fucntion: vacate (Same function as semSignal())
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
void vacate(Semaphore *semaphore)
{
//     begin_critical_section(semaphore);  // make the following concurrency-safe
//     semaphore->value++;                 // release the Semaphore
//     signal_vacate(semaphore);           // signal anyone waiting on this
//     end_critical_section(semaphore);

  // printf("vacate: pre value is: %d\n", semaphore->value);   //debugger:
  // pthread_mutex_lock(&semaphore->mutex);
  semaphore->value++;
  pthread_cond_signal(&semaphore->condition);
  pthread_mutex_unlock(&semaphore->mutex);
  // printf("vacate: post value is: %d\n", semaphore->value);    //debugger:

}



 void *printline (void *sem)
 {
   // int rt;
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
