#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/platform_device.h>

#define S3C2400_PA_WATCHDOG	(0x15300000)
#define S3C24XX_PA_WATCHDOG	S3C2400_PA_WATCHDOG

#define SZ_1M                           0x00100000
#define S3C24XX_SZ_WATCHDOG SZ_1M

#define IRQ_WDT 	17		/* 0x00020000 */

static struct resource s3c_wdt_resource[] = {
	[0] = { 
		.start = S3C24XX_PA_WATCHDOG,
		.end   = S3C24XX_PA_WATCHDOG + S3C24XX_SZ_WATCHDOG - 1,
		.flags = IORESOURCE_MEM,
		.name  = "s3c_wdt io resource",
	},
	[1] = {
		.start = IRQ_WDT,
		.end   = IRQ_WDT,
		.flags = IORESOURCE_IRQ,
		.name  = "s3c_wdt irq resource",
	}

};

static struct platform_device *yang_device = NULL;

static int __init yang_device_init(void)
{
	int ret=0;

	yang_device = platform_device_alloc("yang_device_test",-1);
	if (!yang_device) {
		ret = -ENOMEM;
		printk("<0>yangchaofeng add in %s:%d ret=%d Device allocation failed\n", __func__, __LINE__,ret);
		goto exit;
	}	

	ret = platform_device_add_resources(yang_device, &s3c_wdt_resource[0], 2);
	if (ret) {
		printk("<0>yangchaofeng add in %s:%d ret=%d Device resource addition failed\n", __func__, __LINE__,ret);	   
		goto exit_device_put;
	}
	
	ret = platform_device_add(yang_device);
	if (ret) {
		printk("<0>yangchaofeng add in %s:%d ret=%d Device addition failed\n", __func__, __LINE__,ret);
		goto exit_device_put;
	}
	
	printk("<0>yangchaofeng add in %s:%d ret=%d \n", __func__, __LINE__,ret);
	return 0;
 exit_device_put:
	platform_device_put(yang_device);
 exit:
	yang_device = NULL;
	return ret;
}

static void __exit yang_device_exit(void)
{
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
	platform_device_unregister(yang_device);
}

module_init(yang_device_init);
module_exit(yang_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yangchaofeng device");
