#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define initModule(moduleImage, len, paramValues) syscall(__NR_init_module, moduleImage, len, paramValues)
#define finitModule(fd, paramValues, flags) syscall(__NR_finit_module, fd, paramValues, flags)

int main(int argc, char **argv) {
	const char *params;
	int fd, useFinit;
	size_t imageSize;
	struct stat st;
	void *image;

	/* CLI handling. */
	if (argc < 2) {
		puts("Usage ./prog mymodule.ko [args="" [useFinit=0]");
		return EXIT_FAILURE;
	}
	if (argc < 3) {
		params = "";
	}
	else {
		params = argv[2];
	}
	if (argc < 4) {
		useFinit = 0;
	}
	else {
		useFinit = (argv[3][0] != '0');
	}

	/* Action. */
	fd = open(argv[1], O_RDONLY);
	if (useFinit) {
		puts("finit");
		if (finitModule(fd, params, 0) != 0) {
			perror("finitModule");
			return EXIT_FAILURE;
		}
		close(fd);
	}
	else {
		puts("init");
		fstat(fd, &st);
		imageSize = st.st_size;
		image = malloc(imageSize);
		read(fd, image, imageSize);
		close(fd);
		errno = 0;
		if (initModule(image, imageSize, params) != 0) {
			perror("initModule");
			return EXIT_FAILURE;
		}
		free(image);
	}
	return EXIT_SUCCESS;
}