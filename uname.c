#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    struct utsname unameData;
    uname(&unameData);

    if(argc == 1) {
        printf("%s\n", unameData.sysname);
    }
    else {
        if(strcmp(argv[1], "-r") == 0) {
            printf("%s\n", unameData.release);
        }
        else if (strcmp(argv[1], "-v") == 0) {
            printf("%s\n", unameData.version);
        }
        else if (strcmp(argv[1], "-m") == 0) {
            printf("%s\n", unameData.machine);
        }
        else if (strcmp(argv[1], "-a") == 0) {
            printf("%s %s %s\n", unameData.sysname, unameData.release, unameData.version );
        }
        else if (strcmp(argv[1], "-s") == 0) {
            printf("%s\n", unameData.sysname);
        }
        else
        {
            printf("unknown arg: %s", argv[1]);
        }
        
    }
}
