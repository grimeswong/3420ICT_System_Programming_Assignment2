//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sema.c
//  Purpose: Create threads for synchronisation by using semaphore, firstly, wait for user to type some string, then print out on the screen,
//           after that, prompt the user to press enter key that exit the program

#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <unistd.h>   //eg. sleep
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit
#include "sema.h"     // using the file sema.c  // the rest of code will be used here


int rt;


/*
 *  Fucntion: main()
 *  Description: This function is create threads to read string and print string by using semphore for controlling the sequence
 *  Parameter:  None
 *  Return: int 0 if success
 */
int main ()
{

    struct Semaphore sem;
    //Start: initialiser
    rt = initialiser();   //debugger:

    /*** Create thread ***/
    // pthread_create


    if(rt != 0) { perror("Main: couldn't initailise the initaliser"); }               // error message:
    else { printf("Main: Successfully create initialiser\n");}  // debugger:
    // printf("Semaphore value is: %d\n", sem->value);


    /*** Testing ***/

    procure(&sem);
    printf("sematest: locking now\n");
    vacate(&sem);

    procure(&sem);
    printf("sematest2: locking now\n");
    vacate(&sem);
    /*** Testing end ***/


    //At the End: destructor
    rt = destructor();    //debugger:
    if(rt != 0) { perror("Main: couldn't use destructor"); }               // error message:
    else { printf("Main: Successfully destroy related stuffs\n");}  // debugger:


    return 0;
}
