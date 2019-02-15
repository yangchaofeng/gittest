
CC=gcc
CFLAGS=-fPIC -g
all: test

test:
	$(CC)  $(CFLAGS) -o test test.c function/function.a

#%.o: %.c
#	$(CC)   $(CFLAGS)-c $<
clean:
	rm -f  function.a ~* *~ *.ASV *.bak  *.so test  core> /dev/null
