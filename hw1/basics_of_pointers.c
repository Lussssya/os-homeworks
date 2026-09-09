#include <stdio.h>

int main () {
	int x = 10;
	int* p = &x;

	printf("value using int variable %d\n", x);
	printf("value using pointer x = %d\n", *p);

	printf("address using int variable %p\n", &x);
        printf("address using pointer x = %p\n", p);
	printf("&x == p : %b\n", &x == p);

	*p = 7;
	printf("after update using int variable %d\n", x);
        printf("after update using pointer x = %d\n", *p);

	return 0;
}
