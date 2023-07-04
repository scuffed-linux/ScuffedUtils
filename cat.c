#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	char c;
	int fdNum = argc - 1;
	int fd;

	if (argc < 2) {
		fputs("bad args\r\n", stderr);
		return 1;
	}
	struct stat st;
	for (uint_fast8_t i = 1; i != fdNum + 1; i++) {
		fd = open(argv[i], O_RDONLY);
		if (fd < 0) {
			char str[2048] = "Failed to open '";
			strcat(str, argv[i]);
			strcat(str, "'");
			perror(str);
		}

		fstat(fd, &st);
		size_t size = st.st_size;

		uint8_t *buf = malloc(size);

		read(fd, buf, size);
		close(fd);

		write(STDOUT_FILENO, buf, size);
	}
}