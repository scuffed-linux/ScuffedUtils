#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int isRegularFile(const char *path) {
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

int main(int argc, char* argv[]) {
	// TODO: args + multiple dirs

    char* path = "";

	if (argc != 2) {
		path = ".";
	}
    else {
        path = argv[1];
    }

	DIR *folder;
	struct dirent *entry;

	if (isRegularFile(path)) {
		printf(path);
		printf("\n");
	}
	else {
		folder = opendir(path);
		if (folder == NULL) {
			perror("no such file or directory");
			return 1;
		}

		while((entry = readdir(folder))) {
			// TODO: Only if not -a/-A
			if (entry->d_name[0] == '.')  {
				continue;
			}
			printf("%s   ", entry->d_name);
		}
        printf("\n");
		closedir(folder);
	}
	return(0);
}