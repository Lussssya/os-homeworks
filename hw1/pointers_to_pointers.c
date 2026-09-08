#include <stdio.h>

int main () {
	int x = 10;
	int* p = &x;
	int** pp = &p;

	printf("pointer: %d\n", *p);
	printf("pointer to pointer: %d\n", **pp);

	return 0;
}
