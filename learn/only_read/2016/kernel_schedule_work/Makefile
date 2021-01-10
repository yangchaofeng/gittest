ifneq ($(KERNELRELEASE),)

obj-m := hello.o

else
	
KDIR := /lib/modules/2.6.27.5-117.fc10.i686/build
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers

endif
