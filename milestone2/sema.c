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
void semInitialiser(struct Semaphore *semaphore);
// void semDestructor(Semaphore *semaphore);

struct Semaphore sem;
pthread_cond_t cond;

int main ()
{

    int rt;
    /*** condition variables ***/
    rt = pthread_cond_init(&cond, NULL); //condition variable Initialize

    semInitialiser(&sem);
    printf("Semaphore value is: %d\n", sem.value);
    return 0;
}

/*
 *  Fucntion: semInitialiser
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
void semInitialiser(struct Semaphore *semaphore)
{
  /*** Initialize semaphore value ***/
  semaphore->value = 1;
  /*** Initialize mutex ***/
  pthread_mutex_init(&semaphore->mutex, NULL);
}

/*
 *  Fucntion: semDestructor
 *  Description: Cleans up semaphores, mutex, condition variable, and release memory allocation
 *  Parameter:  Semaphore.
 *  Return: None
 */
// void semDestructor(Semaphore *semaphore)
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

  pthread_cond_wait(&cond, &sem.mutex);
  while(&sem.value <= 0) {
    // do nothing
  }
  sem.value--;
  pthread_cond_signal(&cond);

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
