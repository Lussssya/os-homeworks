#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_realloc (void *ptr, size_t original_size, size_t new_size) {
	if (new_size == 0) {
		free(ptr);
		return NULL;
	}
	
	void *cp;

	cp = malloc(new_size);
	if (cp == NULL) {
		printf("Initial memory allocation failed!\n");
		return NULL;
	}

	if (ptr == NULL) {
		return cp;
	}

	if (original_size > new_size) {
		memcpy(cp, ptr, new_size);
	} else {
		memcpy(cp, ptr, original_size);
		memset((char *)cp + original_size, 0, new_size - original_size);
	}
	

	free(ptr);
	return cp;
}

int main () {
	int *arr = malloc(3 * sizeof(int));
	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;

    	printf("Original, size 3: ");
    	for (int i = 0; i < 3; i++) {
        	printf("%d ", arr[i]);
    	}
    	printf("\n");

    	int *temp = my_realloc(arr, 3 * sizeof(int), 5 * sizeof(int));
    	if (temp == NULL) {
        	free(arr);
        	return 1;
    	}

	arr = temp;
	printf("After realloc to 5: ");
        for (int i = 0; i < 5; i++) {
                printf("%d ", arr[i]);
        }
	printf("\n");

    	arr[3] = 40;
    	arr[4] = 50;

   	printf("After value write: ");
    	for (int i = 0; i < 5; i++) {
        	printf("%d ", arr[i]);
    	}
    	printf("\n");

	temp = my_realloc(arr, 5 * sizeof(int), 2 * sizeof(int));
    	if (temp == NULL) {
        	free(arr);
        	return 1;
    	}

    	arr = temp;

    	printf("After realloc to 2: ");
    	for (int i = 0; i < 2; i++) {
        	printf("%d ", arr[i]);
    	}
   	 printf("\n");

    	free(arr);
	return 0;
}
