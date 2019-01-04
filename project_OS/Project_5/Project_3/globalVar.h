#ifndef globalVar_h
#define globalVar_h

#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t work_mutex;
sem_t empty;
sem_t full;
extern int counter; //to remove and add to buffer



#endif