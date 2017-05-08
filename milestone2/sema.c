//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sema.c
//  Purpose: Use the semaphores to create a thread for synchronisation

/*** Preprocessor ***/
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp
#include <unistd.h>   //eg. sleep
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
// #include <semaphore.h>//For using semaphore


/*** Function declartion (Prototype) ***/
void procure(Semaphore *semaphore);
void vacate(Semaphore *semaphore);
void semInitialiser(Semaphore *semaphore, int value);
void semDestructor(Semaphore *semaphore);

/*** Structure to store Semahpore and string (input) ***/
struct semaphore {

  char *linePtr;
  int value;    // like count


}; // must put semicolon after this structure


/*
 *  Main function
 *  Description:  Create child thread and read the line of string, then print out the string.
 *                Child thread wait until main thread prompt user to press enter, then child thread exit the program.
 *                Main thread wait for all child thread to exit, then exit the entire program
 *                Need to use main and child threads, and use semaphores
 *  Parameter:  None.
 *  Return: exit success
 */
int main ()
{

}


/*
 *  Fucntion: semInitialiser
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
void semInitialiser(Semaphore *semaphore, int value)
{

}

/*
 *  Fucntion: semDestructor
 *  Description: Cleans up semaphores, mutex, condition variable, and release memory allocation
 *  Parameter:  Semaphore.
 *  Return: None
 */
void semDestructor(Semaphore *semaphore)
{

}

/*
 *  Fucntion: procure (Same function as semWait())
 *  Description:
 *  Parameter:  Semaphore.
 *  Return: None
 */
// void procure(Semaphore *semaphore)
// {
//     begin_critical_section(semaphore);  // make the following concurrency-safe
//     while (semaphore->value <= 0)
// 	wait_for_vacate(semaphore);     // wait for signal from vacate()
//     semaphore->value--;                 // claim the Semaphore
//     end_critical_section(semaphore);
// }
//

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
