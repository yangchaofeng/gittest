ifneq ($(KERNELRELEASE),)

obj-m := poll.o

else
	
KDIR := /lib/modules/2.6.27.5-117.fc10.i686/build
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f read write *.ko *.o *.mod.o *.mod.c *.symvers

gcc:
	gcc -o read test_poll_read.c
	gcc -o write test_poll_write.c

endif
