ifneq ($(KERNELRELEASE),)

obj-m := input_button.o 

else
	
KDIR := /lib/modules/2.6.27.5-117.fc10.i686/build
all:
	gcc -o input_test app_input.c
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers
	rm -rf input_test
insmod:
	insmod input_button.ko
rmmod:
	rmmod input_button

endif
