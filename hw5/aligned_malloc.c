#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void* aligned_malloc (size_t size, size_t alignment) {
	void* ptr = malloc(size + (alignment - 1) + sizeof(void *));
	if (ptr == NULL) {
		return NULL;
	}

	printf("malloc returned:       %p\n", ptr);

	char* aligned = (char *)ptr + sizeof(void *);
	printf("after pointer space:   %p\n", (void *)aligned);

	while ((uintptr_t)aligned % alignment != 0) {
		aligned++;
	}

	printf("aligned address:       %p\n", (void *)aligned);

	*(void **)(aligned - sizeof(void *)) = ptr;
	printf("saved original ptr at: %p\n\n", (void *)(aligned - sizeof(void *)));

	return aligned;
}

void aligned_free (void *ptr) {
	printf("aligned_free received: %p\n", ptr);
	void* ptr_to_free = *(void **)((char *)ptr - sizeof(void *));
	printf("recovered original:    %p\n\n", ptr_to_free);
	free(ptr_to_free);
}

int main () {
	void *p = aligned_malloc(100, 64);
	printf("Returned to main:      %p\n\n", p);
	aligned_free(p);

    	return 0;
}
