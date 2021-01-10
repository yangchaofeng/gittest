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

static struct work_struct tp_resume;
static struct delayed_work test_delayed_work;

static void tp_resume_work(struct work_struct *work)
{
printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
}
static void test_delayed_func(struct work_struct *work)  
{  
    printk("%s, %d, %ld\n", __func__, __LINE__, jiffies);  
} 
 
static int __init hello_init(void)  
{
    int i;
    bool run_state;  
    INIT_WORK(&tp_resume, tp_resume_work);
    INIT_DELAYED_WORK(&test_delayed_work, test_delayed_func);  
    for(i=0;i<4;i++){
	run_state = schedule_work(&tp_resume);
	msleep(300);
	printk("<0>yangchaofeng add in %s:%d run_state=%d\n", __func__, __LINE__,run_state);		

	 run_state = schedule_delayed_work(&test_delayed_work, 1 * HZ);
	 msleep(3000);
	printk("<0>yangchaofeng add in %s:%d run_state=%d\n", __func__, __LINE__,run_state);
    }
    return 0;  
}  
  
static void __exit hello_exit(void)  
{ 
cancel_work_sync(&tp_resume);
cancel_delayed_work_sync(&test_delayed_work); 
    printk("<0> Bye, 2016!\n");  
}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
