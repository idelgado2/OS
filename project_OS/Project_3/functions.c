#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "lib.h"

int numValues(char *history[]){ //keeps track of how many values are in the history array
    int i = 0, count = 0;
    while(history[i] != NULL){
        i++;
        count++;
    }
    return count;
}

void childExecvp(char **args){ //to execute shell commands
    if(execvp(args[0], args) == -1){
             perror("Error");
    } 
}

bool ampersand(char **args, int *size){ //check for ampersand
    int i;
    for (i=0; i < *size; i++) {
        if (strcmp(args[i], "&") == 0)
            return true;
    }
    return false;
}


int historyFunction(char *history[], int current, int numOfVal) //print out previously executed commands
{
        int i = 0;
        do {
                if (history[i]) {
                        printf("%d  %s\n", numOfVal, history[i]);
                        numOfVal--;
                }
                i++;
        } while (i != current);

        return 0;
}

