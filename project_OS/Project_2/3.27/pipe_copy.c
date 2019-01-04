#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]){
    FILE *infile;
    FILE *outfile;
    char writeArray[50];
    char readArray[50];
    int fd[2];
    pid_t pid;
    
    infile = fopen(argv[1], "r");
    if (!infile) {
        perror("file does not exist\n");
        exit(1);
    }

    outfile = fopen(argv [2], "w");
    if (!outfile) {
        perror("output file Failed\n");
        exit(1);
    }
    
    if (pipe(fd) == -1) {
        perror("pipe failed\n");
        exit(1);
    }
    
    pid = fork(); //forking a child
    if (pid < 0) {
        perror("fork failed\n");
        exit(1);
    }
    
    if (pid > 0) { //parent process
        close(fd[READ_END]);
        
        printf("writing file information to pipe ...\n");

        while (fgets(writeArray, sizeof(writeArray), infile) != NULL) {
            write(fd[WRITE_END], writeArray, sizeof(writeArray));
            //writing data from file to pipe
        }

        close(fd[WRITE_END]);
    }else{//child process
        close(fd[WRITE_END]);
        printf("reading information from pipe to destination file ...\n");
        //
        while ((read(fd[READ_END], readArray, sizeof(readArray))) != 0) {
            fprintf(outfile, "%s", readArray);
        }
        close(fd[READ_END]);
    }

    printf("I am DONE!\n");
}
