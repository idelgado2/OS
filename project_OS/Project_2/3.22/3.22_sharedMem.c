#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
	pid_t pid; //Process id
	int i = atoi(argv[1]);
	if (i <= 0){
		fprintf(stderr, "Only Positive Number Are Acceptable\n");
		return 1;
	}

	const int SIZE = 4096;
	int shm_fd;
	const char *name = "OurMemory";

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); //open shared memory
	void *ptr; //pointer to shared memory

	ftruncate(shm_fd, SIZE); //configure the size of shared memory

	ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); //memory mapped


	pid = fork();

	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if(pid == 0){  //child process
		printf("Processing Collatz conjecture in CHILD process\n");
		printf("Child is thinking......\n");
        sprintf(ptr, "%d", i); //print first integer, will original integer
        ptr += sizeof(i);
        do{
            if(i % 2 == 0) //even
                i = i/2;
            else 			//odd
                i = (3 * i) + 1;
            sprintf(ptr, "%d", i);
            ptr += sizeof(i);
        }while(i != 1);
	}
	else{
		printf("Waiting for child to finish\n");
        wait(NULL);
        sleep(3);
        printf("child is DONE, now printing from parent process\n");

        while(strcmp((char*)ptr, "\0") != 0){
            printf("%s, ", (char*)ptr);
            ptr += sizeof(i);
        }
        printf("\n");
	}
	return 0;
}
