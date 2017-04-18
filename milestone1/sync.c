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

/*** Mutex intialization ***/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*** Structure to store state of mutex the line of string ***/
struct dataMutex {
  int mutexState; // 0 for unlock, 1 for lock
  char *linePtr;

}; // must put semicolon after this structure




int main() {
  /*** Local variables ***/
  char charMix[BUFFERSIZE];               // Create an array for maximum 128 characters
  // char *charPtr = &charMix[0];            // Assign pointer point to the first element of the charMix
  int rt;                                 // return 0 = successful, -1 = fail

  struct dataMutex dataMutex1, *dataMutexPtr;            // Declare of the dataMutex
  dataMutex1.mutexState = 0;              // 0 for unlock, 1 for lock
  dataMutex1.linePtr = &charMix[0];       // Assign the pointer point to the first element of the charMix
  dataMutexPtr = &dataMutex1;


  // Thread ID:
  pthread_t tid;                     // pthread data structure

  // Create pthread attributes
  pthread_attr_t attr;
  pthread_attr_init(&attr);


  /*** to do list ***/
  // create thread first than read the line

  /*** Create the child thread ***/
  rt = pthread_create(&tid, &attr, printline, (void *) dataMutexPtr);    //create thread
  if(rt != 0) {
    perror("Couldn't create a thread!!!");
  }

  /*** read and print line in the parent thread ***/
  pthread_mutex_lock(&mutex);
  // dataMutex1.mutexState = 1;  // 1 = locked
  fgets(dataMutex1.linePtr, BUFFERSIZE, stdin);      // Read the line
  sleep(2); // debugger:
  printf("Parent thread: dataMutex1linePtr is %s\n", dataMutexPtr->linePtr);      // debugger:
  printf("Parent thread: dataMutex1.mutexState is %d\n", (int)dataMutexPtr->mutexState);      // debugger:
  pthread_mutex_unlock(&mutex);
  dataMutex1.mutexState = 0; // 0 = unlocked

  // rt = pthread_create(&tid, &attr, printline, (void *) dataMutexPtr);    //create thread

  pthread_join(tid, NULL);    //  wait to other thread to join

  /*** end: read and print line thread ***/

  // Destroy everthing(mutex, cond & attr) and confirm all threads are exit
  // pthread_mutex_destroy()
  pthread_exit(NULL);       // The last thing the main should do

  return 0;
}


/*  function: print out the line of user entered
*  parameter: the pointer address of string
*  return: nil
*/

void *printline(void *dataMutexPtr) {

  sleep(2);  //debugger
  struct dataMutex *mydataMutex = (struct dataMutex*) dataMutexPtr; //type casting:
  if((*mydataMutex->linePtr) == 1) {
    // do nothing
    printf("Child thread: parent thread is locked\n");
  } else {
    pthread_mutex_lock(&mutex);
    printf("Child thread: printline: %s\n", (*mydataMutex).linePtr);    // debugger:
    printf("%s", (*mydataMutex).linePtr);
  }
  return NULL;  // to silence the non-void function
  // or pthread_exit Child thread call to exit
}

/*  function: trim the '\n' of the line of a string
 *  parameter: the pointer address of string
 *  return: nil
 */
void trimnewline(char *string) {
  int pos = strlen(string) - 1;                                 //second last of the string array
  if(string != NULL) {
    string[pos] = '\0';
  }
}
