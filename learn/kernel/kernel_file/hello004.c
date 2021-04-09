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

#define DEBUG 1
#define FILE_DATA_LEN (sizeof(struct data_file_bist))


static int zte_lcd_write_file(char *filename, char *buf, int size)
{
	struct file *filp = NULL;
	mm_segment_t oldfs;
	loff_t pos = 0;
	ssize_t ret;

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	filp = filp_open(filename, O_CREAT | O_WRONLY, 0644);
	if (IS_ERR(filp)) {
		printk("failed to open file= %s when write\n", filename);
		return -1;
	}

	ret = vfs_write(filp, buf, size, &pos);
	if (ret <= 0) {
		printk("failed to write file= %s\n", filename);
		return ret;
	}
	
	filp_close(filp, NULL);
	set_fs(oldfs);

	return 0;
}
static int zte_lcd_read_file(char *filename, char *buf, int size)
{
	struct file *filp = NULL;
	mm_segment_t oldfs;
	loff_t pos = 0;
	ssize_t ret;

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	filp = filp_open(filename, O_CREAT | O_RDONLY, 0644);
	if (IS_ERR(filp)) {
		printk("failed to open file=%s when read\n", filename);
		return -1;
	}

	/*f->f_op->write(f, buf, size, &f->f_pos);*/
	/*vfs_llseek(f, 0, SEEK_SET);*/
	ret = vfs_read(filp, buf, size, &pos);
	if (ret <= 0) {
		printk("failed to read file= %s\n", filename);
		return ret;
	}

	filp_close(filp, NULL);
	set_fs(oldfs);

	return 0;
}
static u64 get_current_time_sec(void)
{
	struct timeval current_time;
	do_gettimeofday(&current_time);

	#if	DEBUG
	unsigned long tsec;
	struct rtc_time tm;

	tsec = current_time.tv_sec;

	rtc_time_to_tm(tsec, &tm);
	printk("%s:%d tsec=%ld --> [%04x-%02d-%02d %02d:%02d:%02d]\n",__func__, __LINE__, tsec, tm.tm_year, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min , tm.tm_sec);	
	#endif
	printk("%s:%d current_time.tv_sec=0x%08x\n",__func__, __LINE__,current_time.tv_sec);
	return current_time.tv_sec;
}

struct data_file_bist {
	u32 is_need_bist;
	u32 bist_total_time;//sec
	u64 sart_bist;
	u64 stop_bist;
};
struct data_file_bist lcd_data_file_bist;

static void dump_data_file_bist(void)
{
	printk("%s:%d bis_need_bist=0x%04x\n",__func__, __LINE__,lcd_data_file_bist.is_need_bist);
	printk("%s:%d bist_total_time=0x%04x\n",__func__, __LINE__,lcd_data_file_bist.bist_total_time);
	printk("%s:%d sart_bist=0x%08x\n",__func__, __LINE__,lcd_data_file_bist.sart_bist);
	printk("%s:%d stop_bist=0x%08x\n",__func__, __LINE__,lcd_data_file_bist.stop_bist);
}

static int test(int flag)
{
	int ret = 0,i = 0;
	char filename[] = "/data/lcd_bist_time00";
	unsigned char buf[64] = {0};

	//first read data from file
	ret = zte_lcd_read_file(filename, &buf[0], FILE_DATA_LEN);
	memcpy(&lcd_data_file_bist, &buf[0], FILE_DATA_LEN);

	//suspend
	if (lcd_data_file_bist.is_need_bist == 0 && flag == 0) {
		return 0;
	} else if (lcd_data_file_bist.is_need_bist == 1) {
		lcd_data_file_bist.sart_bist = get_current_time_sec();
	} else if (lcd_data_file_bist.is_need_bist == 0 && flag == 1){
		lcd_data_file_bist.sart_bist = get_current_time_sec();
	}

	//resume
	if (lcd_data_file_bist.is_need_bist == 0) {
		return 0;
	} else if (lcd_data_file_bist.is_need_bist == 1) {
		lcd_data_file_bist.stop_bist = get_current_time_sec();
		//wirte data to file
		memcpy(&buf[0], &lcd_data_file_bist, FILE_DATA_LEN);
		ret = zte_lcd_write_file(filename, &buf[0], FILE_DATA_LEN);
	} 

	#if 0
	//read data from file
	ret = zte_lcd_read_file(filename, &buf[0], FILE_DATA_LEN);
	memcpy(&lcd_data_file_bist, &buf[0], FILE_DATA_LEN);
	dump_data_file_bist();

	//lcd_data_file_bist.is_need_bist = 0x1234;
	//lcd_data_file_bist.bist_total_time = 0x5678;
	//msleep(5000);

	//wirte data to file
	memcpy(&buf[0], &lcd_data_file_bist, FILE_DATA_LEN);
	ret = zte_lcd_write_file(filename, &buf[0], FILE_DATA_LEN);

	//read file for check wirte ok ?
	ret = zte_lcd_read_file(filename, &buf[0], FILE_DATA_LEN);
	memcpy(&lcd_data_file_bist, &buf[0], FILE_DATA_LEN);
	dump_data_file_bist();
	#endif

	return 0;
}

static int __init hello_init(void)  
{  
    
    printk("<0> Hello, 2021! v0402_001\n");  

    test(1);
	test(0);

    return 0;  
}  
  
static void __exit hello_exit(void)  
{  
    printk("<0> Bye, 2021!\n");  

}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
