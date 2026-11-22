#include <stdio.h>
#include <pthread.h>

#define N 5

int arr[N];

void *square (void *arg) {
        int thread_id = *(int *)arg;
        int original = arr[thread_id];
        arr[thread_id] *= arr[thread_id];

        printf("Square of %d is %d\n", original, arr[thread_id]);

        return NULL;
}

int main () {
        pthread_t threads[N];
        int thread_ids[N];

        printf("Original array:\n");
        for (int i = 0; i < N; i++) {
                arr[i] = i + 1;
                printf("%d ", arr[i]);
        }
        printf("\n\n");

        for (int i = 0; i < N; i++) {
                thread_ids[i] = i;

                if (pthread_create(&threads[i], NULL, square, &thread_ids[i]) != 0) {
                        perror("Failed to create the thread");
                        return 1;
                }
        }

        for (int i = 0; i < N; i++) {
                if (pthread_join(threads[i], NULL) != 0) {
                        perror("Failed to join the thread");
                        return 1;
                }
        }

        printf("\nUpdated array:\n");
        for (int i = 0; i < N; i++) {
                printf("%d ", arr[i]);
        }
        printf("\n");

        return 0;
}