ifneq ($(KERNELRELEASE),)

obj-m := list.o

else
	
KDIR := /lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.mod.o *.mod.c *.symvers *.order .*.cmd  .tmp_versions *.markers
endif
