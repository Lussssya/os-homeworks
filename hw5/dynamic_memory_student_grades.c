#include <stdio.h>
#include <stdlib.h>

int main () {
	int *arr;
	int n;

	printf("Enter the number of students: ");
	scanf("%d", &n);
	
	arr = (int *)malloc(n * sizeof(int));
	if (arr == NULL) { 
		perror("malloc failed");
		return 1;
	}

	int min = 100;
	int max = 0;
	printf("Enter the grades: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		if (min > arr[i]) {
			min = arr[i];
		}
		if (max < arr[i]) {
			max = arr[i];
		}
	}

	printf("Highest grade: %d\n", max);
	printf("Lowest grade: %d\n", min);

	free(arr);
	arr = NULL;

	return 0;
}
