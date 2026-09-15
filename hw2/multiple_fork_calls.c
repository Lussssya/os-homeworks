#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>

int main () {
	pid_t pid;

	printf("before fork\n");

	pid = fork();
	if (pid < 0) {
        	// Fork failed
        	perror("Fork failed");
        	exit(1);
    	}

	printf("fork1\n");

	pid = fork();
	if (pid < 0) {
                // Fork failed
                perror("Fork failed");
                exit(1);
        }

	printf("fork2\n");

	pid = fork();
	if (pid < 0) {
                // Fork failed
                perror("Fork failed");
                exit(1);
        }

	printf("fork3\n");

	while(1);

	return 0;
}
