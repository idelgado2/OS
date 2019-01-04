/*************************************************************************
 * Programming project 5
 * Isaac Delgado
 * COSC_3346
 * 7/18/2016
 * Purpose: This program will solve execute 8 different threads utilizing 
 *			a semaphore to dictate dependencies -> (b can onlu execute if 
 *			A has executed, e can only execute it both b and C have
 *			executed, f can only execute if D has executed, and H can only
 *			execute if E, F, and G have all executed).
 *
 * Input:   The input of the program will no input simply implementation of
 *			semaphores and threads
 *
 * Output:  The output of this program will the different threads printing
 *			thread letter. A randome waiting time will be used to try and 
 *			get different orders of thread executions.
 **************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *param); 
void create_sems(sem_t sem_bin);
sem_t A_sem, B_sem, C_sem, D_sem, E_sem, F_sem, G_sem; //all emaphores

int main(){
	pthread_t tid[8];
	pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    int n, res;	//for for-loops
    
    create_sems(A_sem); /*Creating all needed binary_semaphores*/
    create_sems(B_sem);
    create_sems(C_sem);
    create_sems(D_sem);
    create_sems(E_sem);
    create_sems(F_sem);
    create_sems(G_sem);
	
	for(n = 0; n < 8; n++){	/*create threads*/
			res = pthread_create(&tid[n], &attr, thread_function, (void*) (intptr_t) n);
	  	if (res != 0) {
			perror("Thread creation failed (Consumer)");
			exit(-1); 
		}
	} //creating 8 threads
	
	for(n = 0; n < 8; n++) { //joining threads
   		res = pthread_join(tid[n], NULL);
		if (res != 0) {
			perror("pthread_join failed");
		}
	}	//joining 8 threads	
		
    sem_destroy(&A_sem);
    sem_destroy(&B_sem);
    sem_destroy(&C_sem);
    sem_destroy(&D_sem);
    sem_destroy(&E_sem);
    sem_destroy(&F_sem);
    sem_destroy(&G_sem);

}

void create_sems(sem_t bin_sem){
	int n;
	for(n = 0; n < 7; n++){
		int res;
		res = sem_init(&bin_sem, 0, 0); 
		if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
		}
	}
}

void *thread_function(void *param) {
	int value = (intptr_t)param;
	int randSleepTime = (rand() % (3 - 1)) + 1; //random sleep time between 1 to 3 seconds
	sleep(randSleepTime);
	switch(value){
		case 0: //thread A
					sleep(randSleepTime);
			printf("Thread A\n");
					sleep(randSleepTime);
			sem_post(&A_sem);
					sleep(randSleepTime);
			break;
		case 1:	//thread B
					sleep(randSleepTime);
			sem_wait(&A_sem);
			printf("Thread B\n");
					sleep(randSleepTime);
			sem_post(&B_sem);
					sleep(randSleepTime);
			break;
		case 2:	//thread C
					sleep(randSleepTime);
			printf("Thread C\n");
					sleep(randSleepTime);
			sem_post(&C_sem);
					sleep(randSleepTime);
			break;
		case 3:	//thread D
					sleep(randSleepTime);
			printf("Thread D\n");
					sleep(randSleepTime);
			sem_post(&D_sem);
					sleep(randSleepTime);
			break;
		case 4:	//thread E
					sleep(randSleepTime);
			sem_wait(&B_sem);
					sleep(randSleepTime);
			sem_wait(&C_sem);
			printf("Thread E\n");
					sleep(randSleepTime);
			sem_post(&E_sem);
					sleep(randSleepTime);
			break;
		case 5:	//thread F
					sleep(randSleepTime);
			sem_wait(&D_sem);
			printf("Thread F\n");
					sleep(randSleepTime);
			sem_post(&F_sem);
					sleep(randSleepTime);
			break;
		case 6:	//thread G
					sleep(randSleepTime);
			printf("Thread G\n");
					sleep(randSleepTime);
			sem_post(&G_sem);
					sleep(randSleepTime);
			break;
		case 7:	//Thread H
			sem_wait(&E_sem);
			sem_wait(&F_sem);
			sem_wait(&G_sem);
				printf("Thread H\n");
			break;
		default:
			perror("error occured in switch case\n");
			exit(-1);
	}
	pthread_exit(NULL);
}