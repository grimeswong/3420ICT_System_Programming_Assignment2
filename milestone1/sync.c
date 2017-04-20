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
// pthread_mutex_t main_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t child_mutex = PTHREAD_MUTEX_INITIALIZER;

/*** Structure to store state of mutex the line of string ***/
struct dataMutex {
  // int mutexState; // 0 for unlock, 1 for lock
  char *linePtr;
  pthread_mutex_t main_mutex;    //main mutex
  pthread_mutex_t child_mutex;   //child mutex
  pthread_mutex_t third_mutex;   //third mutex
}; // must put semicolon after this structure


int main() {
  /*** Local variables ***/
  char charMix[BUFFERSIZE];               // Create an array for maximum 128 characters
  int rt;                                 // return 0 = successful, -1 = fail (to check error return)

  struct dataMutex dataMutex1, *dataMutexPtr;            // Declare of the dataMutex, and a pointer
  dataMutex1.linePtr = &charMix[0];         // Assign the pointer point to the first element of the charMix
  dataMutexPtr = &dataMutex1;

  /**** Initialise main mutex ***/
  rt = pthread_mutex_init(&dataMutex1.main_mutex, NULL);
  if(rt != 0) {
    perror("Couldn't make main mutex init");
  } else {
    printf("Main thread: Main mutex initialize successfully\n");
  }

  /**** Initialise third mutex ***/
  rt = pthread_mutex_init(&dataMutex1.third_mutex, NULL);
  if(rt != 0) {
    perror("Couldn't make third mutex init");
  } else {
    printf("Main thread: Third mutex initialize successfully\n");
  }



  // Thread ID:
  pthread_t tid;                     // pthread data structure

  /*** Create pthread attributes ***/
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  /*** Lock main thread ***/
  rt = pthread_mutex_lock(&dataMutex1.main_mutex);
  if(rt != 0) {
    perror("Main: Couldn't make lock main thread");
  } else {
    printf("Main thread: make pthread lock successfully\n");
  }

  /*** Create the child thread ***/
  rt = pthread_create(&tid, NULL, printline, (void *) dataMutexPtr);    //create child thread
  if(rt != 0) {
    perror("Couldn't create a thread!!!");
  }

  /*** read and print line in the parent thread ***/
  fgets(dataMutex1.linePtr, BUFFERSIZE, stdin);      // Read the line
  trimnewline(dataMutex1.linePtr);
  // sleep(2); // debugger:
  printf("Parent thread: dataMutex1linePtr is %s\n", dataMutexPtr->linePtr);      // debugger:
  pthread_mutex_lock(&dataMutex1.third_mutex);    // lock it before the child mutex run after printing
  pthread_mutex_unlock(&dataMutex1.main_mutex);     // release lock that main thread has read the string


  pthread_mutex_lock(&dataMutex1.child_mutex);      // test the child mutex; Main blocked until child thread has print out the string and release the mutex
  pthread_mutex_unlock(&dataMutex1.child_mutex);    // child_mutex: release to destroy mutex

  printf("Please press enter to exit\n");
  while(strcmp(fgets(dataMutex1.linePtr, BUFFERSIZE, stdin), "\n")) {
    printf("Please press enter to exit\n");
  }

  printf("Enter is pressed\n");
  pthread_mutex_unlock(&dataMutex1.third_mutex);     // release lock that main thread can exit


  printf("Waiting for child to exit\n");
  pthread_mutex_lock(&dataMutex1.main_mutex);     // release lock that main thread has read the string
  pthread_mutex_unlock(&dataMutex1.main_mutex);     // main_mutex: release to destroy mutex

  /*** Wait the child thread to join ***/
  rt = pthread_join(tid, NULL);    //  wait to other thread to join
  if (rt != 0) {
    perror("Child thread(s) couldn't joint the main thread\n");
  } else {
    printf("Child thread join back to main, child thread is gone\n");
  }


  /*** end: read and print line thread ***/

  // Destroy everthing(mutex, cond & attr) and confirm all threads are exit correctly (otherwise error 16 for mutex is being used(busy))
  rt = pthread_mutex_destroy(&dataMutex1.main_mutex);
  printf("Destroy main_mutex code: %d\n", rt);
  rt = pthread_mutex_destroy(&dataMutex1.child_mutex);
  printf("Destroy child_mutex code: %d\n", rt);
  rt = pthread_mutex_destroy(&dataMutex1.third_mutex);
  printf("Destroy third_mutex code: %d\n", rt);

  pthread_exit(NULL);       // The last thing the main should do

  return 0;
}


/*  function: print out the line of user entered
*  parameter: the pointer address of string
*  return: nil
*/

void *printline(void *dataMutexPtr) {
  // int rt;
  struct dataMutex *mydataMutex = dataMutexPtr;               // type casting: void * back to correct type of struct
  pthread_mutex_init(&(mydataMutex)->child_mutex, NULL);
  pthread_mutex_lock(&(mydataMutex)->child_mutex);            // Child lock the child mutex
  pthread_mutex_lock(&(mydataMutex)->main_mutex);             // test the main mutex; child blocked until main read to the and release the mutex

  printf("Child thread: %s\n", mydataMutex->linePtr);         // debugger: test the content of structure
  printf("%s\n", mydataMutex->linePtr);                         // print the string of line read
  pthread_mutex_unlock(&(mydataMutex)->child_mutex);            // Child unlock the child mutex
  printf("Child thread: Waiting for parent signal\n");
  pthread_mutex_lock(&(mydataMutex)->third_mutex);              // test the main thread that whether user has pressed "enter", last use of thrid_mutex
  pthread_mutex_unlock(&(mydataMutex)->third_mutex);            // third_mutex: release to destroy mutex

  sleep(2);
  printf("Child has received main thread signal, child is exiting\n");
  sleep(2);
  pthread_mutex_unlock(&(mydataMutex)->main_mutex);             // Child release lock and child thread exiting





  // printf("Child thread is exiting...\n");

  return NULL;  // to silence the non-void function // or pthread_exit Child thread call to exit
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
