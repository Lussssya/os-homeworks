#include <stdio.h>

int main () {
	int x = 10;
	int* p = &x;

	printf("using int variable %d\n", x);
	printf("using pointer x = %d\n", *p);

	*p = 7;
	printf("after update using int variable %d\n", x);
        printf("after update using pointer x = %d\n", *p);

	return 0;
}
