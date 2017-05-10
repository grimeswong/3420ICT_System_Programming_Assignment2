//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sema.h
//  Purpose: Header file for prototype of semaphore

#ifndef _sema_h
#define _sema_h

typedef struct Semaphore
{
  int value;
  pthread_mutex_t mutex;
  pthread_cond_t condition;
  char *linePtr;
} Semaphore;

void procure(Semaphore *semaphore);
void vacate(Semaphore *semaphore);
int initialiser();
int destructor();

#endif
