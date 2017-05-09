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

/*** Structure to store Semahpore and string (input) ***/
// struct Semaphore {
//   int value;    // like counter
//
//
// }; // must put semicolon after this structure

/*** Function declartion (Prototype) ***/
void procure(struct Semaphore *semaphore);
void vacate(struct Semaphore *semaphore);
void initialiser();
// void semDestructor(Semaphore *semaphore);

struct Semaphore sem;
int rt;   // for debugging


int main ()
{


    rt = initialiser(&sem);   //debugger
    if(rt != 0) { perror("Main: couldn't initailise the initaliser"); }               // error message:
    printf("Semaphore value is: %d\n", sem.value);
    return 0;
}

/*
 *  Fucntion: initialiser
 *  Description: This function is for initialise the semaphore, mutex and the condition variable
 *  Parameter:  None
 *  Return: None
 */
void initialiser()
{
  /*** Initialize semaphore value ***/
  sem.value = 1;            // use the

  /*** Initialize mutex ***/
  rt = pthread_mutex_init(&sem.mutex, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a mutex\n"); }               // error message:

  /*** Initialize condition variable ***/
  rt = pthread_cond_init(&sem.condition, NULL);
  if(rt != 0) { perror("Initialiser: couldn't initialise a condition variable\n"); }               // error message:

}

/*
 *  Fucntion: destructor
 *  Description: Cleans up semaphores, mutex, condition variable, and release memory allocation
 *  Parameter:  None
 *  Return: None
 */
// void destructor(Semaphore *semaphore)
// {
//
// }

/*
 *  Fucntion: procure (Same function as semWait())
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
void procure(struct Semaphore *semaphore)
{
  //   begin_critical_section(semaphore);  // make the following concurrency-safe
  //   while (semaphore->value <= 0)
	// wait_for_vacate(semaphore);     // wait for signal from vacate()
  //   semaphore->value--;                 // claim the Semaphore
  //   end_critical_section(semaphore);

  pthread_cond_wait(&sem.condition, &sem.mutex);
  while(&sem.value <= 0) {
    // do nothing
  }
  sem.value--;
  pthread_cond_signal(&sem.condition);

}


/*
 *  Fucntion: vacate (Same function as semSignal())
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
// void vacate(Semaphore *semaphore)
// {
//     begin_critical_section(semaphore);  // make the following concurrency-safe
//     semaphore->value++;                 // release the Semaphore
//     signal_vacate(semaphore);           // signal anyone waiting on this
//     end_critical_section(semaphore);
// }
