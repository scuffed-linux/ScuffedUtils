#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
	for (uint_fast8_t i = 0; i != argc - 1; i++) {
		printf("%s", argv[i]);
	}
}