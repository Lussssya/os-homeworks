#include <stdio.h>

struct TestA {
        char a;
        int b;
        double c;
};

struct TestB {
        double c;
        int b;
        char a;
};

struct TestC {
        int b;
        double c;
        char a;
};

int main () {
    	struct TestA testA;
    	struct TestB testB;
    	struct TestC testC;

        printf("size of struct A (char, int, double): %zu\n", sizeof(struct TestA));
    	printf("a: %p\n", (void *)&testA.a);
    	printf("b: %p\n", (void *)&testA.b);
    	printf("c: %p\n\n", (void *)&testA.c);

        printf("size of struct B (double, int, char): %zu\n", sizeof(struct TestB));
    	printf("c: %p\n", (void *)&testB.c);
   	printf("b: %p\n", (void *)&testB.b);
    	printf("a: %p\n\n", (void *)&testB.a);

        printf("size of struct C (int, double, char): %zu\n", sizeof(struct TestC));
    	printf("b: %p\n", (void *)&testC.b);
    	printf("c: %p\n", (void *)&testC.c);
    	printf("a: %p\n", (void *)&testC.a);

	return 0;
}
