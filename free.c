#include <string.h>
#include <sys/sysinfo.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL) {
		perror("Failed to open /proc/meminfo");
    }

    int total;
    int free;

    char line[256];
    while (fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemTotal: %d kB", &total) == 1) {
            printf("Total Memory: %i kb\n", total);
        }
        if (sscanf(line, "MemFree: %d kB", &free) == 1) {
            printf("Total Free: %i kb\n", free);
        }
    }
    printf("Used mem: %i kb\n", total - free);

    fclose(meminfo);
    return -1;
}