#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>

int main () {
	pid_t pid1;
	pid_t pid2;
	int status1;
	int status2;

	pid1 = fork();
	if (pid1 < 0) {
		// Fork failed
        	perror("Fork failed");
        	exit(1);
	} else if (pid1 == 0) {
		printf("In the child 1 process, child pid = %d\n", getpid());
		printf("In the child 1 process, parent pid = %d\n", getppid());
		exit(0);
	}

	pid2 = fork();
	if (pid2 < 0) {
                // Fork failed
                perror("Fork failed");
                exit(1);
        } else if (pid2 == 0) {
                printf("In the child 2 process, child pid = %d\n", getpid());
                printf("In the child 2 process, parent pid = %d\n", getppid());
                exit(0);
        }


	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2)) {
                printf("exit status of child2: %d\n", WEXITSTATUS(status2));
        }

	wait(&status1);
	if (WIFEXITED(status1)) {
		printf("exit status of child1: %d\n", WEXITSTATUS(status1));
	}

	printf("\nIn the parent process, parent pid = %d\n", getpid());
        printf("In the parent process, children: pid1 = %d, pid2 = %d\n", pid1, pid2);

	return 0;
}
