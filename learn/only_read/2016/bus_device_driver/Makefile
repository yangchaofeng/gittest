ifneq ($(KERNELRELEASE),)

obj-m := bus.o device.o driver.o

else
	
KDIR := /lib/modules/2.6.27.5-117.fc10.i686/build
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.mod.o *.mod.c *.symvers .*.cmd  .tmp_versions

rmmod:
	rmmod driver
	rmmod device
	rmmod bus
insmod:
	insmod bus.ko
	insmod device.ko
	insmod driver.ko
endif
