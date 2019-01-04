#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	pid_t pid;

	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if(pid == 0){
		execlp("/bin/ls", "ls", NULL);
	}
	else{
		printf("child is a ZOMBIE at this moment\n");
		sleep(20);
		wait(NULL);
		printf("Child Complete\n");
	}

	return 0;
}
