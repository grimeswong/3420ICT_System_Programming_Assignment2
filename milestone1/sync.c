//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sync.c
//  Purpose: Use to create a thread for synchronisation

/*** Preprocessor ***/
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp
#include <unistd.h>   //eg. sleep
#include <pthread.h>  //eg. pthread_create, pthread_join, pthread_exit

#define BUFFERSIZE 128

/*** function declartion ***/
void trimnewline(char *string);
void *printline(void *string);

/*** Structure to store mutex and string (input) ***/
struct dataMutex {
  // int mutexState; // 0 for unlock, 1 for lock
  char *linePtr;
  pthread_mutex_t mutex1;   //mutex 1
  pthread_mutex_t mutex2;   //mutex 2
  pthread_mutex_t mutex3;   //mutex 3
}; // must put semicolon after this structure

/*
 *  Main function
 *  Description:  Create child thread and read the line of string, then print out the string.
 *                After that prompt user to press enter, exit the program.
 *                Need to use main and child threads
 *  Parameter:  None.
 *  Return: exit success
 */
int main() {
  /*** Local variables ***/
  char charMix[BUFFERSIZE];               // Create an array for maximum 128 characters
  int rt;                                 // return 0 = successful, -1 = fail (to check error return)

  struct dataMutex dataMutex1, *dataMutexPtr;            // Declare of the dataMutex, and a pointer
  dataMutex1.linePtr = &charMix[0];         // Assign the pointer point to the first element of the charMix
  dataMutexPtr = &dataMutex1;

  /**** Initialise mutex1 ***/
  rt = pthread_mutex_init(&dataMutex1.mutex1, NULL);
  if(rt != 0) {
    perror("Couldn't initialise main mutex\n");                         // error message:
  } else {
    // printf("Main thread: mutex1 initialize successfully\n");     // debugger:
  }

  /**** Initialise mutex2 ***/
  rt = pthread_mutex_init(&dataMutex1.mutex3, NULL);
  if(rt != 0) {
    perror("Couldn't initialise third mutex\n");                        // error message:
  } else {
    // printf("Main thread: mutex3 initialize successfully\n");    // debugger:
  }

  /*** Create thread id ***/
  pthread_t tid;                     // pthread data structure

  /*** Create pthread attributes ***/
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  /*** Lock Main mutex ***/
  rt = pthread_mutex_lock(&dataMutex1.mutex1);                       // Main lock mutex1
  if(rt != 0) { perror("Main: Couldn't make lock main thread"); }               // error message:

  /*** Create the child thread ***/
  rt = pthread_create(&tid, NULL, printline, (void *) dataMutexPtr);            //create child thread
  if(rt != 0) { perror("Main: Couldn't create a thread!!!"); }                  // error message:

  /*** Read and print line in the parent thread ***/
  fgets(dataMutex1.linePtr, BUFFERSIZE, stdin);      // Read the line
  trimnewline(dataMutex1.linePtr);                   // Trim the newline character
  // sleep(2); // debugger:
  // printf("Parent thread: dataMutex1linePtr is %s\n", dataMutexPtr->linePtr);      // debugger:
  pthread_mutex_unlock(&dataMutex1.mutex1);    // release lock that main thread has read the string
  pthread_mutex_lock(&dataMutex1.mutex3);      // Main thread lock the mutex3 for avoing child thread continuously run after printing
  // lock it that avoiding main thread run after printing
  pthread_mutex_lock(&dataMutex1.mutex2);      // test the child mutex; Main blocked until child thread has print out the string and release the mutex
  pthread_mutex_unlock(&dataMutex1.mutex2);    // unlock for destroy mutex


  printf("Please press enter to exit\n");           // Prompt:
  while(strcmp(fgets(dataMutex1.linePtr, BUFFERSIZE, stdin), "\n")) {
    printf("Please press enter to exit\n");         // Prompt:
  }

  // printf("Enter is pressed\n");                     // debugger:
  pthread_mutex_unlock(&dataMutex1.mutex3);     // release lock that main thread can exit
  printf("Child thread is exiting\n");              // Prompt:


  /*** Wait the child thread to join ***/
  rt = pthread_join(tid, NULL);    //  wait to other thread to join
  if (rt != 0) {
    perror("Child thread(s) couldn't joint the main thread\n");     // error message:
  } else {
    printf("Child thread is gone\n");                               // Prompt:  Confirm the child thread is actually exit
  }
  /*** end: read and print line thread ***/

  /*** Destroy everthing(mutex, cond & attr) and confirm all threads are exit correctly
  (otherwise error 16 for mutex is being used(busy)) ***/
  rt = pthread_mutex_destroy(&dataMutex1.mutex1);
  if (rt != 0) { printf("Destroy mutex1 code: %d\n", rt); }          // debugger:
  rt = pthread_mutex_destroy(&dataMutex1.mutex2);
  if (rt != 0) { printf("Destroy mutex2 code: %d\n", rt); }          // debugger:
  rt = pthread_mutex_destroy(&dataMutex1.mutex3);
  if (rt != 0) { printf("Destroy mutex3 code: %d\n", rt); }          // debugger:

  pthread_exit(NULL);       // The last thing the main should do

  return 0;
}

/*
 *  Description: print out the line of user entered
 *  Parameter: the pointer address of structure
 *             type casting back to structure form for access its members(mutex)
 *  Return: NULL
 */

void *printline(void *dataMutexPtr) {
  int rt;
  struct dataMutex *mydataMutex = dataMutexPtr;               // type casting: void * back to correct type of struct

  /*** Initialise mutex2 ***/
  rt = pthread_mutex_init(&(mydataMutex)->mutex2, NULL);
  if(rt != 0) {
    perror("Couldn't initialise third mutex\n");                    // error message:
  } else {
    // printf("Child thread: mutex2 initialize successfully\n");   // debugger:
  }

  pthread_mutex_lock(&(mydataMutex)->mutex2);               // Child lock the mutex2
  pthread_mutex_lock(&(mydataMutex)->mutex1);               // Test the main mutex1; child blocked until main read to the and release the mutex1


  printf("%s\n", mydataMutex->linePtr);                    // Prompt: print the string of line read
  pthread_mutex_unlock(&(mydataMutex)->mutex2);            // Child unlock the mutex2
  // printf("Child thread: Waiting for parent signal\n");     // debugger: test the child thread is waiting the parent signal of user has pressed enter

  // Waiting for main thread signal for user has press enter
  pthread_mutex_lock(&(mydataMutex)->mutex3);              // test the main thread that whether user has pressed "enter", last use of thrid_mutex
  pthread_mutex_unlock(&(mydataMutex)->mutex3);            // mutex3: release to destroy mutex

  // sleep(2);  //debugger:
  // printf("Child has received main thread signal, child is exiting\n");  // debugger:
  // sleep(2 ); // debugger:
  pthread_mutex_unlock(&(mydataMutex)->mutex1);             // Child release mutex1 and child thread exiting

  return NULL;  // to silence the non-void function // or pthread_exit Child thread call to exit
}

/*
 *  Description: trim the '\n' of the line of a string
 *  Parameter: the pointer address of string
 *  Return: none
 */
void trimnewline(char *string) {
  int pos = strlen(string) - 1;                                 //second last of the string array
  if(string != NULL) {
    string[pos] = '\0';
  }
}
