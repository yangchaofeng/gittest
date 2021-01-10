#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/timer.h>  /*timer*/
#include <asm/uaccess.h>  /*jiffies*/

#include <linux/hrtimer.h>
#include <linux/ktime.h>


static struct hrtimer hrtimer;

static enum hrtimer_restart hrtimer_function(struct hrtimer *timer)
{
    printk("<0>Timer Expired and para  !!\n");	
	return HRTIMER_NORESTART;
}


static int __init my_hrtimer_init(void)
{
	int value=8000;//means 8000ms
	printk("<0>yangchaofeng add in %s:%d value=%dms\n", __func__, __LINE__,value);
	hrtimer_init(&hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer.function = hrtimer_function;
	
	hrtimer_start(&hrtimer, ktime_set(value / 1000, (value % 1000) * 1000000), HRTIMER_MODE_REL);
	return 0;
}


static void __exit my_hrtimer_exit(void)
{
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
	if (hrtimer_active(&hrtimer)) 
	{
		ktime_t r = hrtimer_get_remaining(&hrtimer);
		printk("<0>yangchaofeng add %s:%d value=%lld\n", __func__, __LINE__,r.tv64);
	} 
	hrtimer_cancel( &hrtimer );
}

module_init(my_hrtimer_init);
module_exit(my_hrtimer_exit);

MODULE_LICENSE("GPL");
