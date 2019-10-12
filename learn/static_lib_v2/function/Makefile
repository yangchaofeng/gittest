
CC=arm-linux-gcc
all: function.a
function.a:function.o
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) -ffunction-sections -fdata-sections  -c $<

clean:
	rm -f  ~* *~ *.ASV *.bak *.o *.a  core> /dev/null
