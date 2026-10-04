#include <stdio.h>
#include <stdlib.h>

int main () {
	int *arr;
	int n = 10;
	int new_n = 5;

	arr = (int *)malloc(n * sizeof(int));
	if (arr == NULL) {
		printf("Memory allocation failed!\n");
		perror("malloc failed\n");
		return 1;
    	}

	printf("Enter %d integers: ", n);
	for (int i = 0; i< n; i++) {
		scanf("%d", &arr[i]);
	}

	int *new_arr = (int *)realloc(arr, new_n * sizeof(int));
	if (new_arr == NULL) {
        	printf("Memory reallocation failed!\n");
        	free(arr);
        	return 1;
	}

	printf("Array after resizing: ");
	for (int i = 0; i < new_n; i++) {
		printf("%d ", new_arr[i]);
	}
	printf("\n");

	free(new_arr);
	new_arr = NULL;

	return 0;
}
