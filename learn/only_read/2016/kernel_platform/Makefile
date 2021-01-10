ifneq ($(KERNELRELEASE),)

obj-m := platform_device.o platform_driver.o

else
	
KDIR := /lib/modules/2.6.27.5-117.fc10.i686/build
all:
	gcc -o test_platform_mise_read test_platform_mise_read.c
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.mod.o test_platform_mise_read *.mod.c *.symvers

rmmod:
	rmmod platform_device
	rmmod platform_driver

insmod:
	insmod platform_device.ko
	insmod platform_driver.ko

endif
