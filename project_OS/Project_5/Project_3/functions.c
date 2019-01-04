#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib.h"
#include "globalVar.h"

void initStruct(){
	if (pthread_mutex_init(&work_mutex, NULL) != 0) { //creating mutex lock
		perror("Mutex initialization failed");
		exit(1);
	}
	
	if (sem_init(&empty, 0, BUFFER_SIZE) != 0) { //creating semaphore
		perror("Semaphore initialization failed: empty\n");
		exit(1);
	}
	
	if (sem_init(&full, 0, 0) != 0) {	//creating semaphore
		perror("Semaphore initialization failed: full\n");
		exit(1);
	}
}
void *producer(void *param){
	buffer_item item;
	while(true){
		sleep(2);
		item = rand(); //produce an item
		if(insert_item(item) == -1)
			perror("report error condition (producer)");
		else
			printf("producer produced %d\n", item);
	}
}
void *consumer(void *param){
	buffer_item item;
	while(true){
		sleep(2);
		if(remove_item(&item) == -1)
			perror("report error condition (consumer)");
		else
			printf("consumer consumed %d\n", item);
	}
}
int insert_item(buffer_item item){
	pthread_mutex_lock(&work_mutex);
	sem_wait(&empty);
	
	buffer[counter] = item;
	
	if((buffer[counter] != item)){	//add item to buffer
		return -1;
	}
	
	counter++; //counter follows along the value of semaphore 'full'
	pthread_mutex_unlock(&work_mutex);
	sem_post(&full);
	
	return 0;
}
int remove_item(buffer_item *item){
	pthread_mutex_lock(&work_mutex);
	sem_wait(&full);
	counter--; //counter follows along the value of semaphore 'full'
	
	*item = buffer[counter];
	if(*item != buffer[counter]){	//remove from buffer into item
		return -1;
	}
	
	pthread_mutex_unlock(&work_mutex);
	sem_post(&empty);
	
	return 0;
}
void cancelThreads(int value, pthread_t *tid){
	int n;
	for(n = 0; n < value; n++){
		pthread_cancel(tid[n]);
	}
}
void printBuffer(){
	printf("Printing out Buffer...\n");
	int i;
	for(i = 0; i < BUFFER_SIZE; i++){
		printf("%d, ", buffer[i]);
	}
	printf("\n");
}
