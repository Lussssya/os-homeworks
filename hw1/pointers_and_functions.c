#include <stdio.h>

void swap (int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main () {
	int a = 10;
	int* ap = &a;
	int b = -10;
	int* bp = &b;

	printf("a = %d\nb = %d\n", a, b);

	swap(ap, bp);
	printf("Swapped\n");

	printf("a = %d\nb = %d\n", a, b);

	return 0;
}
