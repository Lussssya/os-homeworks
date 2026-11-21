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

int main () {
	char source_file[1024];
	char destination_file[1024];

	printf("Enter source file path: ");
	if (scanf("%1023s", source_file) != 1) {
		printf("failed to read path");
		return 1;
	}
	
	printf("Enter destination file path: ");
	if (scanf("%1023s", destination_file) != 1) {
		printf("failed to read path\n");
		return 1;
	}

	int fd_src = open(source_file, O_RDONLY);
	if (fd_src < 0) {
		perror("file open fail");
		return 1;
	}

	int fd_dest = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_dest < 0) {
		perror("file open fail");
		closeFile(&fd_src);
		return 1;
	}

	int len = 8;
	char buf[len];
	ssize_t ret;
	size_t total = 0;

	while ((ret = read(fd_src, buf, len)) != 0) {
		if (ret < 0) {
			if (errno == EINTR) {
				continue;
			}
			perror("read fail");
			closeFile(&fd_src);
			closeFile(&fd_dest);
			return 1;
		}

		ssize_t written = 0;
		while (written != ret) {
			ssize_t current = write(fd_dest, buf + written, ret - written);
			if (current < 0) {
				if (errno == EINTR) {
					continue;
				}
				perror("write fail");
				closeFile(&fd_src);
				closeFile(&fd_dest);
				return 1;
			}
			if (current == 0) {
				printf("No bytes were written!\n");
				closeFile(&fd_src);
				closeFile(&fd_dest);
				return 1;
			}

			written += current;
			total += current;
		}
	}

	printf("The total amount of bytes copied is %zu!\n", total);

	int source_close_failed = closeFile(&fd_src);
	int destination_close_failed = closeFile(&fd_dest);
	
	return source_close_failed || destination_close_failed;
}
