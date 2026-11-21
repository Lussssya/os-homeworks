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
        char* filename = "numbers.txt";
        int fd = creat(filename, 0644);
        if (fd < 0) {
                perror("fail creating file");
                return 1;
        }

        char text[] = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n";
        if (writeAll(fd, text, sizeof(text) - 1) != 0) {
                closeFile(&fd);
                return 1;
        }
        if (closeFile(&fd) != 0) {
                return 1;
        }

        fd = open(filename, O_RDWR);
        if (fd < 0) {
                perror("fail opening file");
                return 1;
        }

        int lines = 0;
        char c;
        while (lines < 3) {
                ssize_t result = read(fd, &c, 1);
                if (result < 0) {
                        if (errno == EINTR) {
                                continue;
                        }

                        perror("read fail");
                        closeFile(&fd);
                        return 1;
                }
                if (result == 0) {
                        printf("File ended before line 4\n");
                        closeFile(&fd);
                        return 1;
                }

                if (c == '\n') {
                        lines++;
                }
        }

        off_t line4 = lseek(fd, 0, SEEK_CUR);
        if (line4 < 0) {
                perror("fail getting position");
                closeFile(&fd);
                return 1;
        }

        off_t line5 = lseek(fd, 2, SEEK_CUR);
        if (line5 < 0) {
                perror("fail getting position");
                closeFile(&fd);
                return 1;
        }

        char buf[16];
        size_t used = 0;

        ssize_t ret;
        while ((ret = read(fd, buf + used, sizeof(buf) - used)) != 0) {
		if (ret < 0) {
			if (errno == EINTR) {
				continue;
			}
			perror("read fail");
			closeFile(&fd);
			return 1;
		}

                used += ret;
        }

        off_t position = lseek(fd, line4, SEEK_SET);
        if (position < 0) {
                perror("fail getting position");
                closeFile(&fd);
                return 1;
        }

        char hundred[] = "100\n";
        if (writeAll(fd, hundred, sizeof(hundred) - 1) != 0) {
                closeFile(&fd);
                return 1;
        }

        if (writeAll(fd, buf, used) != 0) {
                closeFile(&fd);
                return 1;
        }

        off_t start = lseek(fd, 0, SEEK_SET);
        if (start < 0) {
                perror("fail getting position");
                closeFile(&fd);
                return 1;
        }

        while ((ret = read(fd, buf, sizeof(buf))) != 0) {
                if (ret < 0) {
                        if (errno == EINTR) {
                                continue;
                        }

                        perror("read fail");
                        closeFile(&fd);
                        return 1;
                }

                if (writeAll(STDOUT_FILENO, buf, (size_t)ret) != 0) {
                        closeFile(&fd);
                        return 1;
                }
        }

        return closeFile(&fd);
}