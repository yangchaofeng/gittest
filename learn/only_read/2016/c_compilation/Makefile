
#包含配置文件
include config.mk


CFLAGS=-fPIC -g 

CFLAGS += -D$(DEVICETYPE)

all:test
test:
	gcc $(CFLAGS) -o test test.c
clean:
	rm -rf test test.o

