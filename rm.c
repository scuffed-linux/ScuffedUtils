#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>

int isDir(const char *path) {
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
}
int main(int argc, char *argv[]) {
	bool recursive = false;
	bool force = false;
	bool preserveRoot = true;
	char *files[50];
	int fileNum = 0;
	if (argc < 2) {
		fputs("bad args\r\n", stderr);
	}
	for (uint_fast8_t i = 0; i != argc - 1; i++) {
		if (strcmp(argv[i], "-r") == 0) {
			recursive = true;
		}
		if (strcmp(argv[i], "-f") == 0) {
			force = true;
		}
		if (strcmp(argv[i], "-rf") == 0 || strcmp(argv[i], "-fr") == 0) {
			recursive = true;
			force = true;
		}
		if (strcmp(argv[i], "--no-preserve-root") == 0) {
			preserveRoot = false;
		}
		else {
			files[fileNum] = argv[i];
			fileNum++;
			files[fileNum] = 0xDEADBEEF;
		}
	}

	for (uint_fast8_t i = 0; i != fileNum; i++) {
		if (files[i] == 0xDEADBEEF) {
			// stop
			break;
		}
		if (isDir(files[i])) {
			fputs("refusing to delete directory without recursive flag\r\n", stderr);
			return 1;
		}
		if (strcmp(files[i], "/") == 0 && preserveRoot) {
			fputs("cowardly refusing to delete the entire root filesystem.  please don't do that....\r\n", stderr);
			return 1;
		}
		remove(files[i]);
	}

}