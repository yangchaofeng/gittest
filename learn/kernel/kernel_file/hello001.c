#include <linux/init.h>   
#include <linux/module.h>   
 
/*#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/uaccess.h> 
*/



#include <linux/fs.h>
#include <linux/file.h>
#include <linux/unistd.h>
#include <linux/uaccess.h>

#include <linux/rtc.h>
#include <linux/delay.h>
static int zte_lcd_write_file(char *filename, char *buf, int size)
{
	struct file *f = NULL;
	mm_segment_t fs;
	loff_t pos = 0;
ssize_t ret;

	fs = get_fs();
	set_fs(KERNEL_DS);

	if (f == NULL)
		f = filp_open(filename, O_CREAT | O_WRONLY, 0644);

	if (IS_ERR(f)) {
		printk("failed to open file= %s\n", filename);
		return -1;
	}

	/*f->f_op->write(f, buf, size, &f->f_pos);*/
	ret = vfs_write(f, buf, size, &pos);
	if (ret <= 0)
		printk("failed to write file= %s\n", filename);
	set_fs(fs);
	filp_close(f, NULL);

	return 0;
}
static int zte_lcd_read_file(char *filename, char *buf, int size)
{
	struct file *f = NULL;
	mm_segment_t fs;
	loff_t pos = 0;
ssize_t ret;

	fs = get_fs();
	set_fs(KERNEL_DS);

	if (f == NULL)
		f = filp_open(filename, O_RDONLY, 0644);

	if (IS_ERR(f)) {
		printk("failed to open file=%s when read\n", filename);
		return -1;
	}
	
	/*f->f_op->write(f, buf, size, &f->f_pos);*/
	/*vfs_llseek(f, 0, SEEK_SET);*/
	ret = vfs_read(f, buf, size, &pos);
	if (ret <= 0)
		printk("failed to read file= %s\n", filename);
	set_fs(fs);
	filp_close(f, NULL);

	return 0;
}
static unsigned long get_current_time_sec(void)
{
	struct timeval current_time;

	do_gettimeofday(&current_time);
	return current_time.tv_sec;
}

static bool lcd_is_run_bist_mod(void)
{
	


	return 0;
}

static int test(void)
{
	int ret = 0,i = 0;
	char filename[] = "/data/lcd_bist_time";
	unsigned char buf[64] = {0};
	unsigned char read_buf[64] = {0};
	struct rtc_time tm;

	unsigned long tsec;
	tsec = get_current_time_sec();
	rtc_time_to_tm(tsec, &tm);

	printk("[%04x-%02d-%02d %02d:%02d:%02d] %s:%d tsec=%ld \n",tm.tm_year, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min , tm.tm_sec,__func__, __LINE__, tsec);	
	memcpy(&buf, &tsec, sizeof(unsigned long));

	ret = zte_lcd_write_file(filename, &buf, sizeof(unsigned long));
       if (ret == 0) {
        for(i=0;i<sizeof(unsigned long)*2;i++)
                printk("%s:%d buf[%d]=0x%x\n",__func__, __LINE__,i,buf[i]);
        }


	msleep(5000);

       tsec = get_current_time_sec();
        rtc_time_to_tm(tsec, &tm);

        printk("[%04x-%02d-%02d %02d:%02d:%02d] %s:%d tsec=%ld \n",tm.tm_year, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min , tm.tm_sec,__func__, __LINE__, tsec);
        memcpy(&buf[4], &tsec, sizeof(unsigned long));

	
        ret = zte_lcd_write_file(filename, &buf, sizeof(unsigned long));
       if (ret == 0) {
        for(i=0;i<sizeof(unsigned long)*2;i++)
                printk("%s:%d buf[%d]=0x%x\n",__func__, __LINE__,i,buf[i]);
        }


        printk("%s:%d ret=%d sizeof=%d\n",__func__, __LINE__, ret, sizeof(unsigned long));



	ret = zte_lcd_read_file(filename, &read_buf, sizeof(unsigned long));


	if (ret == 0) {
	for(i=0;i<sizeof(unsigned long)*2;i++)
		printk("%s:%d read_buf[%d]=0x%x\n",__func__, __LINE__,i,read_buf[i]);
	}

	printk("%s:%d  read=0x%x ret=%d sizeof=%d\n",__func__, __LINE__, read_buf,ret, sizeof(unsigned long));
	return 0;
}

static int __init hello_init(void)  
{  
    
    printk("<0> Hello, 2021!\n");  

    test();

    return 0;  
}  
  
static void __exit hello_exit(void)  
{  
    printk("<0> Bye, 2021!\n");  

}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
