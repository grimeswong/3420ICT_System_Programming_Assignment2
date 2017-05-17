//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sema.c
//  Purpose: Use the semaphores to create a thread for synchronisation

/*** Preprocessor ***/
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
// #include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <unistd.h>   //eg. sleep
// #include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
#include "sema.h"

/*** Function declartion (Prototype) ***/
void procure(Semaphore *semaphore);
void vacate(Semaphore *semaphore);
int initialiser(Semaphore *semaphore);
int destructor(Semaphore *semaphore);

/*** Global variables ***/
int rt;   // for catching error

/*
 *  Fucntion: initialiser
 *  Description: This function is for initialise the semaphore, mutex and the condition variable
 *  Parameter:  Semaphore
 *  Return: int 0 if success
 */
int initialiser(Semaphore *semaphore)
{

  // printf("Initialiser: semaphore address: %x\n", (unsigned int) semaphore);               // debugger: address

  /*** Initialize semaphore value ***/
  semaphore->value = 1;    // 1 binary(critical section), 0 for synchroniztion
  // printf("sem->value is %d\n", semPtr->value);                                           //debugger: value

  /*** Initialize mutex ***/
  rt = pthread_mutex_init(&semaphore->mutex, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a mutex\n"); }                     // error message:
  // else { printf("initialiser: Successfully initialise a mutex\n");}                         // debugger: success

  /*** Initialize condition variable ***/
  rt = pthread_cond_init(&semaphore->condition, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a condition variable\n"); }        // error message:
  // else { printf("initialiser: Successfully initialise a condition variable\n");}            // debugger: success

  return 0; //return 0 if success
}

/*
 *  Fucntion: destructor
 *  Description: Cleans up semaphores, mutex, condition variable, and release memory allocation
 *  Parameter:  Semaphore
 *  Return: int 0 if success
 */
int destructor(Semaphore *semaphore)
{

  /*** destruct the mutex ***/
  rt = pthread_mutex_destroy(&semaphore->mutex);
  if(rt != 0) { perror("destructor: couldn't destruct a mutex\n"); }                         // error message:
  // else { printf("destructor: Successfully destruct a mutex\n");}                             // debugger:

  /*** destruct the condition variable ***/
  rt = pthread_cond_destroy(&semaphore->condition);
  if(rt != 0) { perror("destructor: couldn't destruct a condition variable\n"); }            // error message:
  // else { printf("destructor: Successfully destruct a condition variable\n");}                // debugger:

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
  rt = pthread_mutex_lock (&semaphore->mutex);
  if (rt != 0) { printf("procure: Cannot get the lock\n"); }                   //error message:
  // else { printf("procure: get the lock\n"); }                                      // debugger: success
  // printf("procure: locking\n");                                                    //debugger:
  // printf("procure: pre value is: %d\n", semaphore->value);

  while(semaphore->value <= 0) {
    // printf("procure loop: locking\n");                                         //debugger:
    pthread_cond_wait(&semaphore->condition, &semaphore->mutex);
  }
  semaphore->value--;
  rt = pthread_mutex_unlock(&semaphore->mutex);
  if (rt != 0) { printf("procure: Cannot unlock mutex\n"); }                   //error message: 
  // printf("procure: post value is: %d\n", semaphore->value);                    //debugger:

}

/*
 *  Fucntion: vacate (Same function as semSignal())
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
void vacate(Semaphore *semaphore)
{
  // printf("vacate: pre value is: %d\n", semaphore->value);                      //debugger:
  pthread_mutex_lock(&semaphore->mutex);
  semaphore->value++;
  pthread_cond_signal(&semaphore->condition);
  pthread_mutex_unlock(&semaphore->mutex);
  // printf("vacate: post value is: %d\n", semaphore->value);                     //debugger:

}
