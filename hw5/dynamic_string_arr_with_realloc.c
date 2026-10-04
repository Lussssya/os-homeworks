#include <stdio.h>
#include <stdlib.h>

int main () {
	char **arr;
	int n = 3;
	int n_str = 50;
	int new_n = 5;

	arr = (char **)malloc(n * sizeof(char *));
	if (arr == NULL) {
		printf("Memory allocation failed!\n");
		perror("malloc failed");
		return 1;
	}

	printf("Enter 3 strings: ");
	for (int i = 0; i < n; i++) {
        	arr[i] = (char *)malloc(n_str * sizeof(char));
        	if (arr[i] == NULL) {
            		printf("Memory allocation failed for string %d!\n", i);
            		perror("malloc failed");
			return 1;
        	}
		scanf("%49s", arr[i]);
    	}

	char **new_arr = (char **)realloc(arr, new_n * sizeof(char *));
	if (new_arr == NULL) {
        	printf("Memory reallocation failed!\n");
		perror("realloc failed");
        	free(arr);
        	return 1;
    	}


	printf("Enter 2 more strings: ");
	for (int i = n; i < new_n; i++) {
		new_arr[i] = (char *)malloc(n_str * sizeof(char));
		if (new_arr[i] == NULL) {
                        printf("Memory allocation failed for string %d!\n", i);
                        perror("malloc failed");
                        return 1;
                }
		scanf("%49s", new_arr[i]);
	}
	
	printf("All strings: ");
	for (int i = 0; i < new_n; i++) {
		printf("%s ", new_arr[i]);
	}
	printf("\n");

	for (int i = 0; i < new_n; i++) {
    		free(new_arr[i]);
	}
	free(new_arr);

	return 0;
}
