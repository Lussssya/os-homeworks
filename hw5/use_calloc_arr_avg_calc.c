#include <stdio.h>
#include <stdlib.h>

int main () {
	int *arr;
	int n;

	printf("Enter the number of elements: ");
	scanf("%d", &n);

	arr = (int *)calloc(n, sizeof(int));
	if (arr == NULL) {
		perror("Allocation failed\n");
		return 1;
    	}

	printf("Array after calloc: ");
	for (int i = 0; i < n; i++) {
        	printf("%d ", arr[i]);
    	}

	printf("\nEnter %d integers: ", n);
	for (int i = 0; i < n; i++) {
        	scanf("%d", &arr[i]);
    	}


	double avg = 0;
	printf("Updated array: ");
        for (int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
		avg += arr[i];
        }

	avg /= n;
	printf("\nAverage of the array: %.2f\n", avg);

	free(arr);
	arr = NULL;

	return 0;
}
