#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

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

ssize_t readByte(int fd, char *c) {
        while (1) {
                ssize_t result = read(fd, c, 1);

                if (result < 0) {
                        if (errno == EINTR) {
                                continue;
                        }

                        perror("read fail");
                        return -1;
                }

                return result;
        }
}

int writeAll (int fd, const char *buf, size_t count) {
        size_t written = 0;

        while (written < count) {
                ssize_t current = write(fd, buf + written, count - written);

                if (current < 0) {
                        if (errno == EINTR) {
                                continue;
                        }

                        perror("write fail");
                        return 1;
                }

                if (current == 0) {
                        printf("No bytes were written!\n");
                        return 1;
                }

                written += current;
        }

        return 0;
}

int main () {
        char* filename = "log.txt";
        int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0) {
                perror("fail opening file");
                return 1;
        }

        char line[1024];
        size_t used = 0;

        while (used < sizeof(line)) {
                ssize_t result = readByte(STDIN_FILENO, &line[used]);

                if (result < 0) {
                        closeFile(&fd);
                        return 1;
                }

                if (result == 0) {
                        break;
                }

                used++;

                if (line[used - 1] == '\n') {
                        break;
                }
        }

        char prefix[14];
        int prefix_len = snprintf(prefix, sizeof(prefix), "PID=%ld: ", (long) getpid());
        if (prefix_len < 0 || (size_t)prefix_len >= sizeof(prefix)) {
                printf("Failed to format PID prefix\n");
                closeFile(&fd);
                return 1;
        }

        if (writeAll(fd, prefix, (size_t)prefix_len) != 0) {
                closeFile(&fd);
                return 1;
        }

        if (writeAll(fd, line, used) != 0) {
                closeFile(&fd);
                return 1;
        }

        if (used == 0 || line[used - 1] != '\n') {
                if (writeAll(fd, "\n", 1) != 0) {
                        closeFile(&fd);
                        return 1;
                }
        }

        off_t position = lseek(fd, 0, SEEK_CUR);
        if (position < 0) {
                perror("fail getting file position");
                closeFile(&fd);
                return 1;
        }

        printf("Final file offset: %jd bytes\n", (intmax_t)position);

        return closeFile(&fd);
}