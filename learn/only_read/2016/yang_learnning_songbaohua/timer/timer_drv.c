#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>

#include <linux/cdev.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME     "second"

/*second设备结构体*/
struct second_dev
{
// struct cdev cdev; /*cdev结构体*/
 atomic_t counter;/* 一共经历了多少秒？*/
 struct timer_list s_timer; /*设备要使用的定时器*/
 };

 struct second_dev *second_devp; /*设备结构体指针*/

 /*定时器处理函数*/
 static void second_timer_handle(unsigned long arg)
 {
 mod_timer(&second_devp->s_timer,jiffies + HZ);
 atomic_inc(&second_devp->counter);

 printk("current jiffies is %ld\n", jiffies);
 }

 /*文件打开函数*/
 int second_open(struct inode *inode, struct file *filp)
 {
 /*初始化定时器*/
 init_timer(&second_devp->s_timer);
 second_devp->s_timer.function = &second_timer_handle;
 second_devp->s_timer.expires = jiffies + HZ;

 add_timer(&second_devp->s_timer); /*添加（注册）定时器*/

 atomic_set(&second_devp->counter,0); //计数清零

 return 0;
 }
 /*文件释放函数*/
 int second_release(struct inode *inode, struct file *filp)
 {
 del_timer(&second_devp->s_timer);

 return 0;
 }

 /*globalfifo读函数*/
 static ssize_t second_read(struct file *filp, char __user *buf,size_t count,loff_t *ppos)
 {
 int counter;

 counter = atomic_read(&second_devp->counter);
 if(put_user(counter, (int*)buf))
 return - EFAULT;
 else
 return sizeof(unsigned int);
 }

 /*文件操作结构体*/
 static const struct file_operations dev_fops =
 {
 .owner = THIS_MODULE,
 .open = second_open,
 .release = second_release,
 .read = second_read,
 };
 
 static struct miscdevice misc = {
	.minor = 2,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};
 /*设备驱动模块加载函数*/
 int second_init(void)
 {
    int ret;

	ret = misc_register(&misc);
	/* 动态申请设备结构体的内存*/
 second_devp = kmalloc(sizeof(struct second_dev), GFP_KERNEL);
  memset(second_devp, 0, sizeof(struct second_dev));
 }

 /*模块卸载函数*/
 void second_exit(void)
 {
 printk(KERN_NOTICE "exit\n");
misc_deregister(&misc);
 }

 MODULE_AUTHOR("Song Baohua");
 MODULE_LICENSE("Dual BSD/GPL");

 module_init(second_init);
 module_exit(second_exit);