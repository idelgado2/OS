#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct listnode{
    int number;
    struct listnode *nextNode;
};

int sum;
float average;
int maximum;
int minimum;

struct listnode *head = NULL;
struct listnode *current = NULL;

int init(int num){
    struct listnode *temp = (struct listnode*)malloc(sizeof(struct listnode));
    if (temp == NULL) {
        perror("failed initializing list\n");
        return -1;
    }
    temp -> number = num;
    temp -> nextNode = NULL;
    head = current = temp;
    return 0;
}

int addToList(int num){
    struct listnode * temp = (struct listnode*)malloc(sizeof(struct listnode));
    if (temp == NULL) {
        perror("failed initializing list\n");
        return -1;
    }
    temp -> number = num;
    temp -> nextNode = NULL;
    current -> nextNode = temp;
    current = temp;
    return 0;
}

void printList(){
    struct listnode *temp = head;
    while (temp != NULL) {
        printf("%d ", temp -> number);
        temp = temp -> nextNode;
    }
}

void *aver(void *param){ //going to pass the head of the list
    float sum = 0;
    int values = 0;
    struct listnode * temp = (struct listnode*)malloc(sizeof(struct listnode));
    temp = head;
    while (temp != NULL) {
        sum += temp -> number;
        temp = temp -> nextNode;
        values++;
    }
    average = sum / values;
    
    pthread_exit(0);
 
 }

void *max(void *param){
    int max = *((int *)param);
    struct listnode * temp = (struct listnode*)malloc(sizeof(struct listnode));
    temp = head;
    while (temp != NULL) {
        if (temp -> number > max) {
            max = temp -> number;
        }
        temp = temp -> nextNode;
    }
    maximum = max;
    
    pthread_exit(0);
}

void *min(void *param){
    int min = *((int*)param);
    struct listnode * temp = (struct listnode*)malloc(sizeof(struct listnode));
    temp = head;
    while (temp != NULL) {
        if (temp -> number < min) {
            min = temp -> number;
        }
        temp = temp -> nextNode;
    }
    minimum = min;
    
    pthread_exit(0);
}



int main(int argc, char *argv[]){
    pthread_t tid[3];
    pthread_attr_t atrr;
    
    if (argc == 1) {
        printf("Please provide atleast one integer when running program\n");
        return -1;
    }
    
    if(argc == 2){
        printf("Average: %d\nMaximum: %d\nMinimum: %d\n", atoi(argv[1]), atoi(argv[1]), atoi(argv[1]));
        return 1;
    }
    
    init(atoi(argv[1]));
    int i = 2;
    while (argc != 2)// argc stops at 2, we exclude the first argument as the actual program and we
        //initialize the list with the second argument.
    {
        addToList(atoi(argv[i]));
        argc--;
        i++;
    }
    
    pthread_attr_init(&atrr);
    
    ////////////////////////////////////////////////////////////////////////////////
    pthread_create(&tid[0], &atrr, aver, NULL); //thread to get average of values///
    pthread_join(tid[0], NULL);                                                  ///
    ////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////////
     pthread_create(&tid[1], &atrr, max, (void *) &head->number); //thread to get maximum value in list
     pthread_join(tid[1], NULL);                                                 ///
    ////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////////
     pthread_create(&tid[2], &atrr, min, (void *) &head ->number); //thread to get the minimum value in list
     pthread_join(tid[2], NULL);                                                  ///
    ////////////////////////////////////////////////////////////////////////////////

    
    printf("Average: %.2f\nMaximum: %d\nMinimumL %d\n", average, maximum, minimum);
    
    return 0;
    
}
