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
 

static char buf[] ="你好";
static char buf1[4096];

static int __init hello_init(void)  
{  
    
    struct file *fp,*fp1;
    mm_segment_t fs;
    loff_t pos;
    int i;

    printk("<0> Hello, 2016 0805!\n"); 


    fp =filp_open("/2016_yang/workspace/kernel_file_open/123.bin",O_RDWR | O_CREAT,0644);
//    fp1 =filp_open("/2016_yang/workspace/kernel_file_open/000.bmp",O_RDWR | O_CREAT,0644);
    if (IS_ERR(fp)){
        printk("create file error/n");
        return -1;
    }
    fs =get_fs();
    set_fs(KERNEL_DS);
    pos =0;
//    vfs_write(fp,buf, sizeof(buf), &pos);
//    pos =0;
    vfs_read(fp,buf1, sizeof(buf1), &pos);

    for(i=0;i<16*6;i++)
	{
    		printk("%x,",buf1[i]);
		if(i%16==0)
			printk("\n");	
   	}
    filp_close(fp,NULL);
    set_fs(fs);

    fp1 =filp_open("/2016_yang/workspace/kernel_file_open/012345.bmp",O_RDWR | O_CREAT,0644);
    fs =get_fs();
    set_fs(KERNEL_DS);
    pos =0;
    vfs_write(fp1,buf1, sizeof(buf1), &pos);

    filp_close(fp1,NULL);
    set_fs(fs);


    return 0;   
}  
  
static void __exit hello_exit(void)  
{  
    printk("<0> Bye, 2016 0805!\n");  
}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
