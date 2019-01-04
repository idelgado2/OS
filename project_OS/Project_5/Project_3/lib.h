#ifndef lib_h
#define lib_h

#include <pthread.h>
#include "globalVar.h"

void initStruct();
void *producer(void *param);
void *consumer(void *param);
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void cancelThreads(int value, pthread_t *tid);
void printBuffer();

#endif /* lib_h */
