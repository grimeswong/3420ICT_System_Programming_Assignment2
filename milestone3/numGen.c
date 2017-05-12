//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: numGen.c
//  Purpose: Header file for number generator

// Header files
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <stdio.h>    //Standard Input/Output library eg. getchar, gets, putchar, puts, sprintf
#include <unistd.h>   //eg. sleep(), execvp(), environ(), pipe()
#include <string.h>   //String handling library eg. strcpy, strcat, strcmp
#include <errno.h>    //Error number handling library eg. errno
#include <fcntl.h>    //Access file, file permission, eg. O_CREAT, O_RDONLY, O_WRONLY,
#include <stdint.h>

#include "numGen.h"

/*** Function prototype ***/
uint16_t numGenerator();

/*** Global variable ***/
uint16_t ranNum;
FILE *filePtr;      //file pointer



/*** Main function for testing only ***/
int main()
{
  numGenerator();
  
  return 0;
}

/*  numGenerator();
 *  Description: trim the '\n' of the line of a string
 *  Parameter: the pointer address of string
 *  Return: a random unsigned integer number
 */

 uint16_t numGenerator() {
   int fd = open("/dev/random", O_RDONLY);   //use file desciptor, stream to get random number
   if (fd != -1) {
     read(fd, &ranNum, sizeof(ranNum));
     while(1) {
       printf("Random number is = %d\n", ranNum);
       read(fd, &ranNum, sizeof(ranNum));
       sleep(1);
     }
     close(fd);
   }

   return ranNum;
 }
