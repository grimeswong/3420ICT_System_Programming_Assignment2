//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sema.c
//  Purpose: Use the semaphores to create a thread for synchronisation

/*** Preprocessor ***/
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
// #include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
// #include <string.h>   //String handling library eg. strcpy, strcat, strcmp
// #include <unistd.h>   //eg. sleep
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
#include "sema.h"//For using semaphore


/*** Function declartion (Prototype) ***/
void procure(Semaphore *semaphore);
void vacate(Semaphore *semaphore);
int initialiser();
int semDestructor();

struct Semaphore sem;
int rt;   // for debugging

/*
 *  Fucntion: initialiser
 *  Description: This function is for initialise the semaphore, mutex and the condition variable
 *  Parameter:  None
 *  Return: int 0 if success
 */
int initialiser()
{

  // malloc
  /*** Initialize semaphore value ***/
  sem.value = 1;            //

  /*** Initialize mutex ***/
  rt = pthread_mutex_init(&sem.mutex, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a mutex\n"); }                     // error message:
  else { printf("initialiser: Successfully initialise a mutex\n");}                         // debugger:

  /*** Initialize condition variable ***/
  rt = pthread_cond_init(&sem.condition, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a condition variable\n"); }        // error message:
  else { printf("initialiser: Successfully initialise a condition variable\n");}            // debugger:

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
  else { printf("destructor: Successfully destruct a mutex\n");}                             // debugger:

  /*** destruct the condition variable ***/
  rt = pthread_cond_destroy(&sem.condition);
  if(rt != 0) { perror("destructor: couldn't destruct a condition variable\n"); }            // error message:
  else { printf("destructor: Successfully destruct a condition variable\n");}                             // debugger:

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


  rt = pthread_mutex_lock(&semaphore->mutex);
  pthread_cond_wait(&semaphore->condition, &semaphore->mutex);
  printf("procure: locking\n");
  while(&semaphore->value <= 0) {
      // do nothing
      printf("procure loop: locking\n");
    }
    semaphore->value--;
    pthread_cond_signal(&semaphore->condition);
  rt = pthread_mutex_unlock(&semaphore->mutex);
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
  pthread_mutex_lock(&semaphore->mutex);
  pthread_cond_wait(&semaphore->condition, &semaphore->mutex);
  semaphore->value++;
  pthread_cond_signal(&semaphore->condition);
  pthread_mutex_unlock(&semaphore->mutex);

}
