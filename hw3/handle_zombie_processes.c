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
		exit(0);
	}

	for (int i = 0; i < 1000000000000; i++) {
		//dummy work
	}

	return 0;
}
