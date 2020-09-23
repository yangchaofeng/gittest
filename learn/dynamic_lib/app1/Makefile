
CFLAGS  = -Wall -O3
ldflags := -lrt -lc -lyanglib
all:  x86_test

x86_test:
	gcc -o x86_test main.c $(ldflags)
clean:
	@rm -vf x86_test
