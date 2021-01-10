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

#include "ioctl.h"

#define DEVICE_NAME     "yang_ioctl"

int yang_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{

    int err = 0;
    int ret = 0;
    int ioarg = 0;
	printk("pid[%d]: \n", current->pid);    
	printk("<0>yangchaofeng add in %s:%d cmd=0x%x\n", __func__, __LINE__,cmd);
	
    /* 检测命令的有效性 */
    if (_IOC_TYPE(cmd) != YANG_IOC_MAGIC) 
        return -EINVAL;
    if (_IOC_NR(cmd) > YANG_IOC_MAXNR) 
        return -EINVAL;

    /* 根据命令类型，检测参数空间是否可以访问 */
    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
    if (err) 
        return -EFAULT;

    /* 根据命令，执行相应的操作 */
    switch(cmd) {

      /* 打印当前设备信息 */
      case YANG_IOCPRINT:
      	printk("<--- CMD YANG_IOCPRINT Done at 20160521--->\n\n");
        break;
      
      /* 获取参数 */
      case YANG_IOCGETDATA: 
        ioarg = 1985;
        ret = copy_to_user((int *)arg,&ioarg,sizeof(int));
        break;
      
      /* 设置参数 */
      case YANG_IOCSETDATA: 
        //ret = __get_user(ioarg, (int *)arg);
		ret = copy_from_user(&ioarg, (int *)arg, sizeof(int));
        printk("<--- In Kernel YANG_IOCSETDATA 20160521 ioarg = %d --->\n\n",ioarg);
        break;

      default:  
        return -EINVAL;
    }
    return ret;

}

static struct file_operations dev_fops = {
    .owner   =   THIS_MODULE,
    .ioctl 	 =   yang_ioctl,
};

static struct miscdevice misc = {
	//.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};
static int __init yang_init(void)
{
	int ret;
	ret = misc_register(&misc);
	printk("yang init pid[%d]: \n", current->pid);
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
