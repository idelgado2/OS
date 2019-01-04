/*************************************************************************
 * Programming project 5
 * Isaac Delgado
 * COSC_3346
 * 7/18/2016
 * Purpose: This program will solve the producer-consumer porblem utilizing
 *			multiple threads with a mutex lock and two semaphores(empty & full)
 *			to avoid any race conditions
 *
 * Input:   The input of the program will three command line arguments as
 *			follows (in order), How long to sleep before terminating, number
 *			of producer threads, and number of consumer threads.
 *			 (ex: ./pro-con 5 5 5)
 *
 * Output:  The output of this program will the producer producing the amount
 *			of integers specified and same for consumer, once the program is
 *			terminating the program will print out the remainng list.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "lib.h"
#include "globalVar.h"

int counter = 0;

int main(int argc, char *argv[]){
	/*Getting command line variables*/
	int sleepTime = atoi(argv[1]);
	int numOfProducers = atoi(argv[2]);
	int numOfConsumers = atoi(argv[3]);
	
	pthread_t p_tid[numOfProducers];
	pthread_t c_tid[numOfConsumers];
    pthread_attr_t attr;
    pthread_attr_init(&attr);


	initStruct(); /*Initialize mutex(work_mutex) and semaphores(empty, full)*/
	
	printf("Creating Producer & Consumer Threads...\n");
	int n, res;
	for(n = 0; n < numOfProducers; n++){	/*create producer threads*/
	res = pthread_create(&p_tid[n],&attr, producer, NULL);
	  	if (res!= 0) {
			perror("Thread creation failed (Producer)");
			exit(-1); 
		}
	} //creating producer threads
	for(n = 0; n < numOfConsumers; n++){	/*create consumer threads*/
			res = pthread_create(&c_tid[n],&attr, consumer, NULL);
	  	if (res != 0) {
			perror("Thread creation failed (Consumer)");
			exit(-1); 
		}
	}		//creating consumer threads
    
    printf("Main thread is going to sleep for %d seconds ...\n", sleepTime);
    
    sleep(sleepTime);
    
    printf("Canceling threads now...\n");

    cancelThreads(numOfProducers, p_tid);	//canceling threads
    cancelThreads(numOfConsumers, c_tid);
    
   	for(n = numOfProducers - 1; n >= 0; n--) { //joining threads
   		res = pthread_join(p_tid[n], NULL);
		if (res == 0) {
			printf("Picked up a thread\n");
		}
		else {
			perror("pthread_join failed");
		} 
	}	//joining producer threads
    for(n = numOfConsumers - 1; n >= 0; n--) { //joining consumer threads
   		res = pthread_join(c_tid[n], NULL);
		if (res == 0) {
			printf("Picked up a thread\n");
		}
		else {
			perror("pthread_join failed");
		} 
	}	//joining consumer threads
  	printf("DONE\n");
  	
  	printBuffer();
  
	pthread_mutex_destroy(&work_mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	
return 0;
}

