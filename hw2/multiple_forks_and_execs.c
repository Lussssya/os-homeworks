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
		// Child 1 process
		execl("/usr/bin/ls", "ls", NULL);

		// Only reached if execl fails
        	perror("execl failed");
        	exit(1);
	}

	waitpid(pid, NULL, 0);

	pid = fork();
	if (pid < 0) {
                // Fork failed
                perror("Fork failed");
                exit(1);
        } else if (pid == 0) {
                // Child 2 process
                execl("/usr/bin/date", "date", NULL);

                // Only reached if execl fails
                perror("execl failed");
                exit(1);
        }

	waitpid(pid, NULL, 0);
	printf("Parent process done.\n");	

	return 0;
}
