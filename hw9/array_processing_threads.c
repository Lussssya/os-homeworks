#include <stdio.h>
#include <pthread.h>

#define SIZE 20
#define N 2

int arr[SIZE];
long partial_sums[N];

void* sum_array (void* arg) {
        int thread_id = *((int*)arg);

        int start = thread_id * SIZE / N;
        int end = (thread_id + 1) * SIZE / N;

        for (int i = start; i < end; i++) {
                partial_sums[thread_id] += arr[i];
        }

        printf("Thread %d: %ld\n", thread_id, partial_sums[thread_id]);

        return NULL;
}

int main () {
        pthread_t threads[N];
        int thread_ids[N];

        for (int i = 0; i < SIZE; i++) {
                arr[i] = i + 1;
        }

        for (int i = 0; i < N; i++) {
                thread_ids[i] = i;
                
                if (pthread_create(&threads[i], NULL, sum_array, &thread_ids[i]) != 0) {
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

        long total = 0;
        for (int i = 0; i < N; i++) {
                total += partial_sums[i];
        }

        printf("Total sum: %ld\n", total);

        return 0;
}