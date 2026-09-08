#include <stdio.h>

int main () {
	char str[] = "Hello";
	char* p = &str[0];
	int i = 0;

	while (*p != '\0') {
		printf("str[%d] = %c\n", i, *p);
		i++;
		p++;
	}

	int size = p - &str[0];
	printf("number of chars in array is %d\n", size);


	return 0;
}
