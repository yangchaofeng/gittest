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


struct task_struct *tsk;

static int  fun(void *data)
{
	int j;
	for(j=0;j<5;j++)
	{
//		printk("<0>yangchaofeng add in %s:%d  j=%d\n", __func__, __LINE__,j);
		msleep(3000);
	}
	return 0;
}

static int __init hello_init(void)  
{  
    int i;


	msleep(6000);	
    for(i=0;i<4;i++){
    tsk = kthread_run(fun,NULL,"fun_testa");
	
    	if (IS_ERR(tsk)) {
		printk("<0>yangchaofeng add in %s:%d fail\n", __func__, __LINE__);
	}
	else
		printk("<0>yangchaofeng add in %s:%d sucess pid=%d\n", __func__, __LINE__,tsk->pid);
    
	msleep(3000);	
    }
    return 0;  
}  
  
static void __exit hello_exit(void)  
{  
    printk("<0> Bye, 2016!\n");  
}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
