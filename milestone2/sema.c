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

/*** Function declartion (Prototype) ***/
void procure(Semaphore *semaphore);
void vacate(Semaphore *semaphore);
int initialiser(Semaphore *semaphore);
int destructor(Semaphore *semaphore);

/*** Function declaration (prototype) ***/
void *printline(void *string);

/*** Global variables ***/
int rt;   // for debugging

/*** main function for testing only ***/
// int main ()
// {
//   initialiser(&sem);
//   return 0;
// }

/*
 *  Fucntion: initialiser
 *  Description: This function is for initialise the semaphore, mutex and the condition variable
 *  Parameter:  None
 *  Return: int 0 if success
 */
int initialiser(Semaphore *semaphore)
{

  /*** Intialize Pointer ***/
  // Semaphore *semPtr = malloc(sizeof(&sem));
  // semPtr = &sem;

  // printf("Initialiser: semaphore address: %x\n", (unsigned int) semaphore);                          // debugger: address

  /*** Initialize semaphore value ***/
  semaphore->value = 0;    // 1 binary(critical section), 0 for synchroniztion
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
 *  Parameter:  None
 *  Return: int 0 if success
 */
int destructor(Semaphore *semaphore)
{

  /*** destruct the mutex ***/
  rt = pthread_mutex_destroy(&semaphore->mutex);
  if(rt != 0) { perror("destructor: couldn't destruct a mutex\n"); }                         // error message:
  else { printf("destructor: Successfully destruct a mutex\n");}                             // debugger:

  /*** destruct the condition variable ***/
  rt = pthread_cond_destroy(&semaphore->condition);
  if(rt != 0) { perror("destructor: couldn't destruct a condition variable\n"); }            // error message:
  else { printf("destructor: Successfully destruct a condition variable\n");}                             // debugger:

  // free(semaphore);

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
    // printf("procure loop: locking\n");
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
