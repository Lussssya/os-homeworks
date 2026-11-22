#include <stdio.h>
#include <pthread.h>

void* print_thread (void *arg) {
        pthread_t self = pthread_self();
	printf("Thread %lu is running!\n", (unsigned long)self);
	return NULL;
}

int main () {
        pthread_t thread1, thread2, thread3;

        if (pthread_create(&thread1, NULL, print_thread, NULL) != 0) {
                perror("Failed to create thread");
                return 1;
        }

        if (pthread_create(&thread2, NULL, print_thread, NULL) != 0) {
                perror("Failed to create thread");
                return 1;
        }

        if (pthread_create(&thread3, NULL, print_thread, NULL) != 0) {
                perror("Failed to create thread");
                return 1;
        }


        if (pthread_join(thread1, NULL) != 0) {
                perror("Failed to join thread");
                return 1;
        }

        if (pthread_join(thread2, NULL) != 0) {
                perror("Failed to join thread");
                return 1;
        }

        if (pthread_join(thread3, NULL) != 0) {
                perror("Failed to join thread");
                return 1;
        }

        return 0;
}