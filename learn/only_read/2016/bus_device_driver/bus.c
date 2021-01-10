#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>


MODULE_AUTHOR("Dual BSD/GPL");
MODULE_LICENSE("Dual BSD/GPL");


static char *Version = "yang bus test";

static int my_match(struct device *dev, struct device_driver *driver)
{
	return !strncmp(dev->bus_id, driver->name, strlen(driver->name));
}


static void my_bus_release(struct device *dev)
{
	printk("my bus release\n");
}

struct bus_type my_bus_type = {
		.name = "my_bus_type_name",
		.match = my_match,
};

struct device my_bus = {
	.bus_id = "my_bus_device",
	.release = my_bus_release,
};
EXPORT_SYMBOL(my_bus);
EXPORT_SYMBOL(my_bus_type);

static ssize_t show_bus_version(struct bus_type *bus, char *buf)
{
	return snprintf(buf,PAGE_SIZE,"%s\n",Version);
}
static BUS_ATTR(version,S_IRUGO,show_bus_version,NULL);

static int __init my_bus_init(void)
{
	int ret;
	printk("<0>bus module initting!!!\n");
	ret=bus_register(&my_bus_type);
	if(ret)
		return ret;
		
	if(bus_create_file(&my_bus_type,&bus_attr_version))
		printk("Fail to create version attribute!");
		
	#if 0
	ret=device_register(&my_bus);
		if(ret)
			printk("fail to register device : my_bus");
	#endif
	
	return ret;	
}
static void my_bus_exit(void)
{
	printk("<0>bus module removed!!!\n");
	//device_unregister(&my_bus);
	bus_unregister(&my_bus_type);
}
module_init(my_bus_init);
module_exit(my_bus_exit);