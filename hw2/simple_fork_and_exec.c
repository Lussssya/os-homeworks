#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>

int main () {
	pid_t pid;

	
	pid = fork();
	if (pid < 0) {
		 // Fork failed
        	perror("Fork failed");
        	exit(1);
	} else if (pid == 0) {
		// Child process
		execl("/usr/bin/ls", "ls", NULL);

		perror("execl failed");
        	exit(1);
	}

	wait(NULL);
	printf("Parent process done.\n");


	return 0;
}
