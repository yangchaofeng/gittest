#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>  /*timer*/
#include <asm/uaccess.h>  /*jiffies*/

MODULE_LICENSE("GPL");

struct timer_list timer1;

static void timer_function(int para)
{
    printk("<0>Timer Expired and para is %d !!\n",para);	
    add_timer(&timer1);
}


static int __init timer_init(void)
{
	printk("<0>yangchaofeng add in %s:%s:%d\n",__FILE__, __func__, __LINE__);
	init_timer(&timer1);
	timer1.data = 8;
	timer1.expires = jiffies + (5 * HZ);
	timer1.function = timer_function;
	add_timer(&timer1);
	
	return 0;
}


static void __exit timer_exit(void)
{
	printk("<0>yangchaofeng add in %s:%s:%d\n",__FILE__, __func__, __LINE__);
	del_timer( &timer1 );
}

module_init(timer_init);
module_exit(timer_exit);
