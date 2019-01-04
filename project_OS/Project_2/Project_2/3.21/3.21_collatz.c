#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int i = atoi(argv[1]);
	if (i <= 0){
		fprintf(stderr, "Only Positive Number Are Acceptable\n");
		return 1;
	}

	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if(pid == 0){  //child process
		printf("%d, ", i); //print first integer, will original integer

		do{
			if(i % 2 == 0) //even
				i = i/2;
			else 			//odd
				i = (3 * i) + 1;
			printf("%d, ", i);	
		}while(i != 1);

		printf("\n");
	}
	else{
		wait(NULL);
	}

	return 0;
}

