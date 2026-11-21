#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
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

off_t getFileSize (int *fd) {
	off_t size = lseek(*fd, 0, SEEK_END);

	if (size < 0) {
		perror("fail lseek");
		closeFile(fd);
	}

	return size;
}

int main () {
	char* filename = "data.txt";

	int fd = creat(filename, 0644);
	if (fd < 0) {
		perror("fail creating file");
		return 1;
	}

	char text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int len = sizeof(text) - 1;

	int written = 0;
	while (written != len) {
		ssize_t cur = write(fd, text + written, len - written);
		if (cur < 0) {
			if (errno == EINTR) {	
    				continue;
			}
			perror("write fail");
			closeFile(&fd);
			return 1;
		}
		if (cur == 0) {
			printf("0 bytes to write");
			closeFile(&fd);
			return 1;
		}

		written += cur;
	}

	if (closeFile(&fd) != 0) {
		return 1;
	}

	fd = open(filename, O_RDWR);
	if (fd < 0) {
		perror("fail opening file");
		return 1;
	}

	off_t size = getFileSize(&fd);
	if (size < 0) {
		return 1;
	}

	printf("Current size: %jd bytes\n", (intmax_t)size);
	int tr = ftruncate(fd, 10);
	if (tr == -1) {
		perror("fail truncate");
		closeFile(&fd);
		return 1;
	}

	size = getFileSize(&fd);
	if (size < 0) {
		return 1;
	}

	printf("Size after update: %jd bytes\n", (intmax_t)size);

	off_t set = lseek(fd, 0, SEEK_SET);
	if (set < 0) {
		perror("fail rewinding file");
		closeFile(&fd);
		return 1;
	}
	
	char buf[size];
	ssize_t ret = 0;
	while ((ret = read(fd, buf, size)) != 0) {
		if (ret < 0) {
			if (errno == EINTR) {
				continue;
			}

			perror("read fail");
			closeFile(&fd);
			return 1;
		}

		ssize_t written = 0;
		while (written < ret) {
			ssize_t current = write(STDOUT_FILENO, buf + written, ret - written);
			if (current < 0) {
				if (errno == EINTR) {
					continue;
				}
				perror("write fail");
				closeFile(&fd);
				return 1;
			}
			if (current == 0) {
				printf("No bytes were written!\n");
				closeFile(&fd);
				return 1;
			}

			written += current;
		}
	}

	printf("\n");

	return closeFile(&fd);
}
