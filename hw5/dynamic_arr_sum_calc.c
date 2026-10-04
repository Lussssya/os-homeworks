#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main () {
	int *arr;
	int n;

	printf("Enter the number of elements: ");
	scanf("%d", &n);

	arr = (int *)malloc(n * sizeof(int));
	if (arr == NULL) {
        	perror("Allocation failed\n");
		return 1;
    	}

	printf("Enter %d integers: ", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
    	}

	long sum = 0L;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}

	printf("Sum of the array: %ld\n", sum);

	free(arr);


	return 0;
}
