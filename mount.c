#include <sys/mount.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fputs("bad args\r\n", stderr);
		return 1;
    }

    mount(argv[3], argv[4], argv[2], NULL, NULL);
}