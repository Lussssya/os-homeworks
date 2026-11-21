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

int writeByte (int fd, char c) {
        while (1) {
                ssize_t result = write(fd, &c, 1);

                if (result < 0) {
                        if (errno == EINTR) {
                                continue;
                        }

                        perror("write fail");
                        return 1;
                }

                if (result == 0) {
                        printf("No byte was written!\n");
                        return 1;
                }

                return 0;
        }
}

int main () {
        char source_file[1024];

        printf("Enter source file path: ");
	if (scanf("%1023s", source_file) != 1) {
		printf("failed to read path");
		return 1;
	}

        int fd_src = open(source_file, O_RDONLY);
	if (fd_src < 0) {
		perror("file open fail");
		return 1;
	}

        off_t size = lseek(fd_src, 0, SEEK_END);
        if (size < 0) {
		perror("fail lseek");
		closeFile(&fd_src);
                return 1;
	}

        while (size > 0) {
                size--;
                off_t l = lseek(fd_src, size, SEEK_SET);
                if (l < 0) {
                        perror("fail lseek");
                        closeFile(&fd_src);
                        return 1;
                }

                char c;
                ssize_t result;
                while (1) {
                        result = read(fd_src, &c, 1);

                        if (result < 0) {
                                if (errno == EINTR) {
				        continue;
			        }
                                perror("read fail");
                                closeFile(&fd_src);
                                return 1;
                        } if (result == 0) {
                                printf("unexpected error, nothing has been read");
                                closeFile(&fd_src);
                                return 1;
                        }

                        break;
                }
                
                if (writeByte(STDOUT_FILENO, c) != 0) {
                        closeFile(&fd_src);
                        return 1;
                }

        }

        if (writeByte(STDOUT_FILENO, '\n') != 0) {
                closeFile(&fd_src);
                return 1;
        }

        return closeFile(&fd_src);
}