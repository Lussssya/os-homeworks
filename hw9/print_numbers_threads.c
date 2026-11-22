#include <stdio.h>
#include <pthread.h>

#define N 3

void *print_numbers (void *arg) {
        int thread_id = *(int *)arg;

        for (int i = 1; i <= 5; i++) {
                printf("Thread %d: %d\n", thread_id, i);
        }

        return NULL;
}

int main() {
        pthread_t threads[N];
        int thread_ids[N];

        for (int i = 0; i < N; i++) {
                thread_ids[i] = i;

                if (pthread_create(&threads[i], NULL, print_numbers, &thread_ids[i]) != 0) {
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

        return 0;
}