#include <linux/init.h>   
#include <linux/module.h>   
 
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/uaccess.h> 
#include <linux/platform_device.h>


static struct platform_device *lcd_platform_device = NULL;

void drm_sysfs_hotplug_event(int flag)
{
	char *envp[2] = {NULL};


	printk("generating hotplug event\n");

	/*int kobject_uevent_env(struct kobject *kobj, enum kobject_action action, char *envp[]);*/
	if (flag)
		envp[0] = "panel_status=resume";
	else
		envp[0] = "panel_status=suspend";
	
	kobject_uevent_env(&(lcd_platform_device->dev.kobj), KOBJ_CHANGE, envp);
}

static int __init hello_init(void)  
{ 
    
    printk("<0> Hello, 2021 0409 V000! \n"); 

	lcd_platform_device = platform_device_alloc("zte_lcd", -1);
	platform_device_add(lcd_platform_device); 

	drm_sysfs_hotplug_event(1);
#if 1
	msleep(5000);
	drm_sysfs_hotplug_event(0);
	msleep(5000);
	drm_sysfs_hotplug_event(1);
	msleep(5000);
	drm_sysfs_hotplug_event(0);
	msleep(50000);
#endif
	printk("<0> Bye, 2021 0409 V000! \n"); 
    return 0;  
}  
  
static void __exit hello_exit(void)  
{
	platform_device_unregister(lcd_platform_device);  
    printk("<0> Bye, 2021 0409 end!\n");  
}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
