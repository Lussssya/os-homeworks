#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void hello () {
	printf("Hello world!\n");
}

void bye () {
	printf("Bye world!\n");
}

int main () {
	atexit(bye);

	printf("main func\n");

	atexit(hello);

	return 0;
}
