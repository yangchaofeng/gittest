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
#include <linux/sched.h>


#define DEVICE_NAME     "yang_poll"
static wait_queue_head_t yang_wait_queue;
static bool yang_have_data = false;

int i;
int data_array[50]={0};

/*读函数*/
static ssize_t yang_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
  unsigned long p =  *ppos;
  unsigned int count = size;
  int ret = 0;
printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
  while (!yang_have_data) /* 没有数据可读，考虑为什么不用if，而用while */
  {
        if (filp->f_flags & O_NONBLOCK)
            return -EAGAIN;
	wait_event_interruptible(yang_wait_queue,yang_have_data);
  }
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
  /*读数据到用户空间*/
  if (copy_to_user(buf, &data_array, count))
  {
    ret =  - EFAULT;
  }
  else
  {
    *ppos += count;
    ret = count;
    printk(KERN_INFO "read %d bytes(s) from %ld\n", count, p);
  }
  
  yang_have_data = false; /* 表明不再有数据可读 */
  /* 唤醒写进程 */
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
  yang_have_data = true; /* 有新的数据可读 */
    
    /* 唤醒读进程 */
    wake_up(&yang_wait_queue);

  return ret;
}

unsigned int yang_poll(struct file *filp, poll_table *wait)
{
    unsigned int mask = 0;
    printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
   /*将等待队列添加到poll_table */
    poll_wait(filp, &yang_wait_queue,  wait);
 
    printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
    if (yang_have_data)         mask |= POLLIN | POLLRDNORM;  /* readable */

    return mask;
}

static struct file_operations dev_fops = {
    .owner   =   THIS_MODULE,
    .poll    =   yang_poll,
	.read    =   yang_read,
	.write   =   yang_write,
};

static struct miscdevice misc = {
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};
static int __init yang_init(void)
{
	int ret;
	ret = misc_register(&misc);
	init_waitqueue_head(&yang_wait_queue);
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
	return ret;
}
static void __exit yang_exit(void)
{
	printk("<0>yangchaofeng add in %s:%d\n", __func__, __LINE__);
	misc_deregister(&misc);
}

module_init(yang_init);
module_exit(yang_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FriendlyARM Inc.");
