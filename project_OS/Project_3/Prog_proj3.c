/*************************************************************************
 * Programming project 3
 * Isaac Delgado
 * COSC_3346
 * 7/8/2016
 * Purpose: This program will execute a shell by executing commands thorugh
 *          a chold process. As well as an added history feature and 
 *          shortcut command to executing previously executed commands
 *
 * Input:   The input of the program will be and shell commands (ex. ls, 
 *          ls -l, cal, ps -ael, etc.)
 *
 * Output:  The output of this program will be the execution of specific 
 *          commands as well as a listing of preiviously executed commands
 **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_LINE 80 /* 80 chars per line, per command */



int main(void)
{
    char *args[MAX_LINE/2 + 1]; /* command line (of 80) has max of 40 arguments */
    char command[MAX_LINE];
    char *temp = NULL; //temprary to be copyied into args
    char *history[20];
    int hist_pos = 0;
    int num;
    bool amper = false;

    int k;
    for(k = 0; k < 20; k++){
        history[k] = NULL;
    }

    int should_run = 1;
    pid_t pid;
    
    while (should_run){
        printf("isaac>");
        fflush(stdout);
        
        fgets(command, sizeof(command), stdin); //get user input
        history[hist_pos] = strdup(command); //duplicate command into history
        hist_pos = (hist_pos + 1) % 20;

        temp = strtok(command, " \n"); //divide input into tokens  
        int i = 0;
        while(temp != NULL){ 
            args[i] = temp;
            i++;
            temp = strtok(NULL, " \n");
        }  

        args[i] = NULL; //append ending NULL character

        if (strcmp(args[0], "exit") == 0) { //close shell
                printf("Goodbye\n");
                should_run = 0;
            }
            else if(strcmp(args[0], "history") == 0){
                num = numValues(history);
                historyFunction(history, hist_pos, num);
            }
            else{
                 pid = fork();   //create child process
        
                if (pid < 0) {
                    perror("Fork Failed\n");
                    return 1;
                }
                else if (pid == 0){ //child process
                    should_run = 0; //to terminate child process
                    if(strcmp(args[0], "!!") == 0){
                        num = numValues(history);
                        printf("echo-execution: %s", history[num - 2]);

                        temp = strtok(history[num - 2], " \n");
                        int j = 0;  //configure most recent command for execution 
                        while(temp != NULL){
                            args[j] = temp;
                            j++;
                            temp = strtok(NULL, " \n");
                        }
                        args[j] = NULL; //append ending NULL character
                        childExecvp(args);
                    }
                    else if(strcmp(args[0], "!%d") == 0){ 
                        //could not figure this part, ("!#" -> executes the #th recent command in history)
                        printf("we have a number and an exlamation point\n");
                    }
                    else if(ampersand(args, &i)){
                        amper = true;
                        int k = 0;
                        while(args[k] != NULL){
                            if(args[k+1] == NULL){
                                args[k] = NULL;
                            }
                            k++;
                        }
                        childExecvp(args);
                    }
                    else{
                        childExecvp(args);
                    }
                        return 0;  
                 }
                else{   //parent process
                    if (!amper) {     //if no ampersand is found then parent will wait till child is done
                        wait(NULL);
                    }else{
                        printf("\n");   //else parent will not wait and allow child to execute in background
                    }
                }
            }
    }
    return 0;
}
