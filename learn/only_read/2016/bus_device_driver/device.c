#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>

#include <linux/platform_device.h>


MODULE_AUTHOR("Dual BSD/GPL");
MODULE_LICENSE("Dual BSD/GPL");

extern struct device my_bus;
extern struct bus_type my_bus_type;

static void my_dev_release(struct device *dev)
{

}

static struct device my_dev = {
	.bus = &my_bus_type,
	//.parent = &my_bus,
	.parent = &platform_bus,
	.release = my_dev_release,
};

static ssize_t mydev_show(struct device *dev,struct device_attribute *attr, char *buf)
{ 
	return sprintf(buf, "%s\n" ,"This is my device!");
}

static DEVICE_ATTR(dev_version,S_IRUGO, mydev_show,NULL);

static int __init my_device_init(void)
{
	int ret=0;

	printk("<0>my device module initting!!!\n");

	strncpy(my_dev.bus_id,"my_dev",BUS_ID_SIZE);
	
	ret=device_register(&my_dev);
	
	ret=device_create_file(&my_dev, &dev_attr_dev_version);
	
	return ret;

}

static void my_device_exit(void)
{
	printk("<0>my device module removed!!!\n");
	device_unregister(&my_dev);
}

module_init(my_device_init);
module_exit(my_device_exit);