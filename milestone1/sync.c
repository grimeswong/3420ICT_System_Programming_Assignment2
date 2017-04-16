//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sync.c
//  Purpose: Use to create a thread for synchronisation

/*** Preprocessor ***/
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdlib.h>   //General Utilities library eg. atoi, atof, malloc, realloc
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp

#include <pthread.h>  //pthread_create, pthread_join, pthread_exit

#define BUFFERSIZE 128

/*** function declartion ***/
void trimnewline(char *string);

int main() {
  char charMix[128];
  char *charPtr = &charMix[0];            // assign pointer point to the first element of the charMix

  fgets(charPtr, BUFFERSIZE, stdin);
  while(charPtr != NULL) {
    trimnewline(charPtr);
    

    printf("%s\n", charPtr);



    fgets(charPtr, BUFFERSIZE, stdin);
  }

  return 0;
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
