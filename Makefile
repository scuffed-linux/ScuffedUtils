CC=gcc
CFLAGS= -static
compile=$(patsubst %.c,bin/%,$(shell find -O3 -name '*.c' | sed 's|\./||g'))

vpath %.c 

all: $(compile)
bin/%: %.c
	@mkdir -p $(@D)
	@$(info $s    CC $< ==> $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -rf bin