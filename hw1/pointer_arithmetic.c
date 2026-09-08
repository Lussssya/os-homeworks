#include <stdio.h>

int main () {
	int a[5] = {1, 2, 3, 4, 5};
	for (int i = 0; i < 5; i++) {
		printf("a[%d] = %d\n", i, *(a + i));
		*(a + i) += 1;
	}

	printf("Updated Array\n");

	for (int i = 0; i < 5; i++) {
		printf("using pointer: a[%d] = %d\n", i, *(a + i));
		printf("using array: a[%d] = %d\n\n", i, a[i]);
	}

	return 0;
}
