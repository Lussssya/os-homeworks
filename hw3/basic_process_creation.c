#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>

int main () {
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		// Fork failed
        	perror("Fork failed");
        	exit(1);
	} else if (pid == 0) {
		printf("In the child process, child pid = %d\n", getpid());
		printf("In the child process, parent pid = %d\n", getppid());
		exit(0);
	}
	printf("In the parent process, parent pid = %d\n", getpid());
	printf("In the parent process, child pid = %d\n", pid);


	return 0;
}
