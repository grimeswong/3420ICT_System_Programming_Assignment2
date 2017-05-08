//  3420ICT System Programming
//  SID: S2193948
//  Author: Chun Hung Wong (Grimes)
//  Program: sema.h
//  Purpose: Header file for prototype of semaphore



#ifndef _sema_h
#define _sema_h

struct Semaphore
{
  int value;
  pthread_mutex_t mutex;
};

void procure(struct Semaphore *semaphore);
void vacate(struct Semaphore *semaphore);

#endif
