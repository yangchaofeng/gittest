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

/*second�豸�ṹ��*/
struct second_dev
{
// struct cdev cdev; /*cdev�ṹ��*/
 atomic_t counter;/* һ�������˶����룿*/
 struct timer_list s_timer; /*�豸Ҫʹ�õĶ�ʱ��*/
 };

 struct second_dev *second_devp; /*�豸�ṹ��ָ��*/

 /*��ʱ��������*/
 static void second_timer_handle(unsigned long arg)
 {
 mod_timer(&second_devp->s_timer,jiffies + HZ);
 atomic_inc(&second_devp->counter);

 printk("current jiffies is %ld\n", jiffies);
 }

 /*�ļ��򿪺���*/
 int second_open(struct inode *inode, struct file *filp)
 {
 /*��ʼ����ʱ��*/
 init_timer(&second_devp->s_timer);
 second_devp->s_timer.function = &second_timer_handle;
 second_devp->s_timer.expires = jiffies + HZ;

 add_timer(&second_devp->s_timer); /*��ӣ�ע�ᣩ��ʱ��*/

 atomic_set(&second_devp->counter,0); //��������

 return 0;
 }
 /*�ļ��ͷź���*/
 int second_release(struct inode *inode, struct file *filp)
 {
 del_timer(&second_devp->s_timer);

 return 0;
 }

 /*globalfifo������*/
 static ssize_t second_read(struct file *filp, char __user *buf,size_t count,loff_t *ppos)
 {
 int counter;

 counter = atomic_read(&second_devp->counter);
 if(put_user(counter, (int*)buf))
 return - EFAULT;
 else
 return sizeof(unsigned int);
 }

 /*�ļ������ṹ��*/
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
 /*�豸����ģ����غ���*/
 int second_init(void)
 {
    int ret;

	ret = misc_register(&misc);
	/* ��̬�����豸�ṹ����ڴ�*/
 second_devp = kmalloc(sizeof(struct second_dev), GFP_KERNEL);
  memset(second_devp, 0, sizeof(struct second_dev));
 }

 /*ģ��ж�غ���*/
 void second_exit(void)
 {
 printk(KERN_NOTICE "exit\n");
misc_deregister(&misc);
 }

 MODULE_AUTHOR("Song Baohua");
 MODULE_LICENSE("Dual BSD/GPL");

 module_init(second_init);
 module_exit(second_exit);