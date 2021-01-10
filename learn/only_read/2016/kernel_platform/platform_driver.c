#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/platform_device.h>

#include <asm/uaccess.h> //copy_from_user

#include <linux/miscdevice.h>
#include <linux/cdev.h>
#include <linux/fs.h>


#define to_platform_driver(drv)	(container_of((drv), struct platform_driver, driver))
#define to_platform_device(x) container_of((x), struct platform_device, dev)

#define DEVICE_NAME     "yang_paltform_misc"


struct resource	*wdt_mem;
struct resource	*wdt_irq;

int i;
int data_array[50]={0};

/*读函数*/
static ssize_t yang_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
  unsigned long p =  *ppos;
  unsigned int count = size;
  int ret = 0;
  struct resource	wdt;
	
  wdt=*wdt_mem;
  
  memset(&data_array[0],0,sizeof(data_array));
  memcpy(&data_array[0],&(wdt.start),sizeof(wdt.start));
  
  printk("<0>yangchaofeng add in %s:%d wdt.end=%d wdt.flags=%d wdt=%d\n", __func__, __LINE__,sizeof(wdt.end),sizeof(wdt.flags),sizeof(wdt));
  
  /*读数据到用户空间*/
  if (copy_to_user(buf, &data_array, count))
  {
    ret =  -EFAULT;
  }
  else
  {
    *ppos += count;
    ret = count;
    printk(KERN_INFO "read %d bytes(s) from %ld\n", count, p);
  }
  
  return ret;
}

/*写函数*/
static ssize_t yang_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
  unsigned long p =  *ppos;
  unsigned int count = size;
  int ret = 0;
 
  /*从用户空间写入数据*/
  if (copy_from_user(&data_array, buf, count))
    ret =  - EFAULT;
  else
  {
    *ppos += count;
    ret = count;
    printk(KERN_INFO "written %d bytes(s) from %ld\n", count, p);
  }
  
  for(i=0;i<count;i++)
	printk("<0>yangchaofeng add in %s:%d data_array[%d]=%d\n", __func__, __LINE__,i,data_array[i]);
    
  return ret;
}
static struct file_operations dev_fops = {
    .owner   =   THIS_MODULE,
	.read    =   yang_read,
	.write   =   yang_write,
};
static struct miscdevice misc = {
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int yang_device_driver_probe(struct device *dev)
{
	int ret;
	struct platform_device *pdev;
	
	printk("<0>yangchaofeng add in %s:%d  dev->driver->name=%s init_name=%s\n", __func__, __LINE__,dev->driver->name,dev->init_name);
	
	pdev = to_platform_device(dev);
	printk("<0>yangchaofeng add in %s:%d  pdev->dev.driver->name=%s\n", __func__, __LINE__,pdev->dev.driver->name);
	
	wdt_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (wdt_mem == NULL) {
		printk("<0>yangchaofeng add in %s:%d get io resource ERROR!!!\n", __func__, __LINE__);
		return -ENOENT;
	}
	printk("<0>yangchaofeng add in %s:%d  wdt_mem->name=%s wdt_mem->start=0x%lx wdt_mem->end=0x%lx\n", __func__, __LINE__,wdt_mem->name,(unsigned long) wdt_mem->start,(unsigned long) wdt_mem->end);
	
	wdt_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (wdt_irq == NULL) {
		printk("<0>yangchaofeng add in %s:%d get irq resource ERROR!!!\n", __func__, __LINE__);
		return -ENOENT;
	}	
	printk("<0>yangchaofeng add in %s:%d  wdt_irq->name=%s wdt_irq->start=0x%lx\n", __func__, __LINE__,wdt_irq->name,(unsigned long) wdt_irq->start);
	
	ret = misc_register(&misc);
	printk("<0>yangchaofeng add in %s:%d ret=%d\n", __func__, __LINE__,ret);
	
	return 0;
}

static int yang_driver_probe(struct platform_device *pdev)
{
	printk("<0>yangchaofeng add in %s:%d %s\n", __func__, __LINE__,pdev->dev.driver->name);
	
	return 0;
}
static int yang_driver_remove(struct platform_device *pdev)
{
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
	misc_deregister(&misc);
	return 0;
}

static struct platform_driver yang_driver = {
	//.probe     = yang_driver_probe,
	.remove    = yang_driver_remove,
	.driver    = {          //struct device_driver driver;
		.owner = THIS_MODULE,
		.name  = "yang_device_test",
		.probe = yang_device_driver_probe,
	},

};

static int __init yang_driver_init(void)
{
	int ret=-1;
	
	ret = platform_driver_register(&yang_driver);
	if (ret) {
		printk("<0>yangchaofeng add in %s:%d ret=%d platform_driver_register failed\n", __func__, __LINE__,ret);
	}
	printk("<0>yangchaofeng add in %s:%d ret=%d yang_driver.driver->bus->nam=%s yang_driver.driver.name=%s\n", __func__, __LINE__,ret,yang_driver.driver.bus->name,yang_driver.driver.name);
	return ret;
}

static void __exit yang_driver_exit(void)
{
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
	platform_driver_unregister(&yang_driver);
}

module_init(yang_driver_init);
module_exit(yang_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yangchaofeng driver");
