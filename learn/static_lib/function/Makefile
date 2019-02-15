
CC=gcc
all: function.a
function.a:function.o
	$(AR) rcs $@ $^

%.o: %.c
	$(CC)  -c $<

clean:
	rm -f  ~* *~ *.ASV *.bak *.o *.a  core> /dev/null
