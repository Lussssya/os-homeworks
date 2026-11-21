#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int closeFile (int *fd) {
        if (*fd < 0) {
                return 0;
        }

        int result = close(*fd);
        *fd = -1;

        if (result < 0) {
                perror("close fail");
                return 1;
        }

        return 0;
}

ssize_t readChunk (int fd, char *buf, size_t capacity) {
        size_t used = 0;

        while (used < capacity) {
                ssize_t result = read(fd, buf + used, capacity - used);

                if (result < 0) {
                        if (errno == EINTR) {
                                continue;
                        }

                        return -1;
                }

                if (result == 0) {
                        break;
                }

                used += result;
        }

        return (ssize_t)used;
}

int main() {
        char first_file[1024];
        char second_file[1024];

        printf("Enter first file path: ");
        if (scanf("%1023s", first_file) != 1) {
                printf("Failed to read path\n");
                return 1;
        }

        printf("Enter second file path: ");
        if (scanf("%1023s", second_file) != 1) {
                printf("Failed to read path\n");
                return 1;
        }

        int fd1 = open(first_file, O_RDONLY);
        if (fd1 < 0) {
                perror("first file open fail");
                return 1;
        }

        int fd2 = open(second_file, O_RDONLY);
        if (fd2 < 0) {
                perror("second file open fail");
                closeFile(&fd1);
                return 1;
        }

        char a[16];
        char b[16];

        size_t progress = 0;
        int dif = 0;

        while (1) {
                ssize_t read_first = readChunk(fd1, a, sizeof(a));
                if (read_first < 0) {
                        perror("first file read fail");
                        closeFile(&fd1);
                        closeFile(&fd2);
                        return 1;
                }

                ssize_t read_second = readChunk(fd2, b, sizeof(b));
                if (read_second < 0) {
                        perror("second file read fail");
                        closeFile(&fd1);
                        closeFile(&fd2);
                        return 1;
                }

                if (read_first == 0 && read_second == 0) {
                        printf("Files are identical\n");
                        break;
                }

                ssize_t i;
                for (i = 0; i < read_first && i < read_second; i++) {
                        if (a[i] != b[i]) {
                                printf("Files differ at byte %zu\n", progress + (size_t)i);
                                dif = 1;
                                break;
                        }
                }

                if (dif == 1) {
                        break;
                }

                if (read_first != read_second) {
                        printf("Files differ at byte %zu\n", progress + (size_t)i);
                        dif = 1;
                        break;
                }

                progress += (size_t)read_first;
        }

        int first_file_close_failed = closeFile(&fd1);
        int second_file_close_failed = closeFile(&fd2);

        return first_file_close_failed || second_file_close_failed || dif;
}