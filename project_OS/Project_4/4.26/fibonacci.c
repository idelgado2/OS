#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int numOfvalues;
int *array;

void *fibon(void *param);

int main(int argc, char *argv[]){
    pthread_t tid;
    pthread_attr_t attr;
    
    if (argc == 1) {
        printf("Please provide atleast one integer when running program\n");
        return -1;
    }
    
    numOfvalues = atoi(argv[1]);
    array = (int *)malloc(sizeof(int)*numOfvalues);
    
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, fibon, NULL);
    pthread_join(tid, NULL);
    
    printf("Printing Fibonacci numbers from parent Thread...\n");
    
    int i = 0;
    while (i != numOfvalues) {
        printf("%d, ", array[i]);
        i++;
    }
    printf("\n");
    
    return 0;
}

void *fibon(void *param){
    array[0] = 0;
    array[1] = 1;
    int values = numOfvalues, pos = 2;
    while (values != 2) {
        array[pos] = (array[pos-1] + array[pos-2]);
        pos++;
        values--;
    }
    pthread_exit(0);
}