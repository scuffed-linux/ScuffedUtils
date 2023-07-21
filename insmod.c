#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define finitModule(fd, paramValues, flags) syscall(__NR_finit_module, fd, paramValues, flags)

int main(int argc, char **argv) {
	const char *params;
	int fd;

	/* Make sure the user follows all of the rules */
	if (argc < 2) {
		printf("Usage: insmod module-name.ko [parameters]\n");
		return EXIT_FAILURE;
	}
	if (argc < 3) {
		params = "";
	}
	else {
		params = argv[2];
	}

	/* Insert the module */
	fd = open(argv[1], O_RDONLY);
	if (finitModule(fd, params, 0) != 0) {
		perror("insmod");
		return EXIT_FAILURE;
	}
	close(fd);
	return EXIT_SUCCESS;
}
