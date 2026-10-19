#include <stdio.h>

#pragma pack(4)
struct Test {
	char a;
	int b;
	double c;
};

int main () {
	struct Test test;
	printf("size of struct (char, int, double): %zu\n", sizeof(test));
	printf("a: %p\n", (void *)&test.a);
	printf("b: %p\n", (void *)&test.b);
	printf("c: %p\n", (void *)&test.c);

	return 0;
}
