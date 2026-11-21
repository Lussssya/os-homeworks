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
        char* filename = "sparse.bin";
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
                perror("fail opening file");
                return 1;
        }

        char text[] = "START";
        if (writeAll(fd, text, sizeof(text) - 1) != 0) {
                closeFile(&fd);
                return 1;
        }

        off_t position = lseek(fd, 1024 * 1024, SEEK_CUR);
        if (position < 0) {
                perror("fail lseek");
                closeFile(&fd);
                return 1;
        }

        char end_text[] = "END";
        if (writeAll(fd, end_text, sizeof(end_text) - 1) != 0) {
                closeFile(&fd);
                return 1;
        }

        if (closeFile(&fd) == 1) {
                return 1;
        }

        fd = open(filename, O_RDONLY);
        if (fd < 0) {
                perror("fail opening file");
                return 1;
        }

        off_t size = lseek(fd, 0, SEEK_END);
	if (size < 0) {
		perror("fail lseek");
		closeFile(&fd);
                return 1;
	}

        printf("The file size is %jd\n", size);

        // Read returns the 0s without allocating data block for those, so du shows less disk usage than the file size.

        return closeFile(&fd);
}