#include <stdio.h>

int main () {
	int a;
	char b;
	double c;
	short d;	

	printf("int: %zu\nchar: %zu\ndouble: %zu\nshort: %zu\n",
			sizeof(int), sizeof(char),
			sizeof(double), sizeof(short));

	printf("a: %p\nb: %p\nc: %p\ndL: %p\n", (void*)&a, (void*)&b, (void*)&c, (void*)&d);

	return 0;
}
