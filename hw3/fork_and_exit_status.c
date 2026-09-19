#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>

int main () {
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0) {
		// Fork failed
        	perror("Fork failed");
        	exit(1);
	} else if (pid == 0) {
		exit(100);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status)) {
                printf("finished with exit status %d\n", WEXITSTATUS(status));
        } else {
                printf("didn't finish normally\n");
        }

	pid = fork();
	if (pid < 0) {
                // Fork failed
                perror("Fork failed");
                exit(1);
        } else if (pid == 0) {
                exit(200);
        }

	waitpid(pid, &status, 0);
	if (WIFEXITED(status)) {
		printf("finished with exit status %d\n", WEXITSTATUS(status));
	} else {
		printf("didn't finish normally\n");
	}

	return 0;
}
