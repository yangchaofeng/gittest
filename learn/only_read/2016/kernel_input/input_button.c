#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/input.h>

struct input_dev *button_dev;

static void yang_input_test(void)
{
	int j=0;
for(j=0;j<5;j++)
{
	printk("<0> Hello, 2016! %pS() %d\n",__builtin_return_address(0),current->pid);	
	printk("<0>yangchaofeng add in %s:%d \n", __func__, __LINE__);
	msleep(8000);
		
  	input_report_key(button_dev, KEY_1, 0);
	input_sync(button_dev);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_1);
	msleep(3000);

	input_report_key(button_dev, KEY_2, 0);
	input_sync(button_dev);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_2);
	msleep(3000);
	
	input_report_key(button_dev, KEY_3, 0);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_3);
	msleep(3000);
	
	input_report_key(button_dev, KEY_4, 0);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_4);
	msleep(3000);
	
	input_report_key(button_dev, KEY_5, 0);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_5);
	msleep(3000);
	
	input_report_key(button_dev, KEY_6, 0);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_6);
	msleep(3000);
	
	input_report_key(button_dev, KEY_1, 1);
	input_sync(button_dev);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_1);
	msleep(3000);
	
	input_report_key(button_dev, KEY_2, 1);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_2);
	msleep(3000);
	
	input_report_key(button_dev, KEY_3, 1);
	input_sync(button_dev);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_3);
	msleep(3000);
	
	input_report_key(button_dev, KEY_4, 1);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_4);
	msleep(3000);
	
	input_report_key(button_dev, KEY_5, 1);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_5);
	msleep(3000);
	
	input_report_key(button_dev, KEY_6, 1);
	printk("<0>yangchaofeng add in %s:%d key=%d\n", __func__, __LINE__,KEY_6);
	input_sync(button_dev);      
}
  
}



static int __init dev_init(void)
{
	/* Initialise input stuff */
	button_dev = input_allocate_device();
	if (!button_dev) {
		printk(KERN_ERR "Unable to allocate the input device !!\n");
		return -ENOMEM;
	}

#if 1
	button_dev->name = "s3c2440_button";
	button_dev->id.bustype = BUS_RS232;
	button_dev->id.vendor = 0xDEAD;
	button_dev->id.product = 0xBEEF;
	button_dev->id.version = 0x0100;

	button_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT(EV_SYN);
	//set_bit(EV_KEY, button_dev->evbit)//支持EV_KEY事件
	set_bit(KEY_1,   button_dev->keybit);
	set_bit(KEY_2,   button_dev->keybit);
	set_bit(KEY_3,   button_dev->keybit);
	set_bit(KEY_4,   button_dev->keybit);
	set_bit(KEY_5,   button_dev->keybit);
	set_bit(KEY_6,   button_dev->keybit);
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
#endif	
	input_register_device(button_dev);   //注册input设备

	yang_input_test();
	return 0;
}

static void __exit dev_exit(void)
{
	input_unregister_device(button_dev);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Xie");
MODULE_DESCRIPTION("List Module");
MODULE_ALIAS("List module");

