#ifndef _YANG_H_
#define _YANG_H_

#include <linux/ioctl.h>


/*mem设备描述结构体*/
struct mem_dev                                     
{                                                        
  char *data;                      
  unsigned long size;       
};

/* 定义幻数 */
#define YANG_IOC_MAGIC  'y'

/* 定义命令 */
#define YANG_IOCPRINT   _IO(YANG_IOC_MAGIC, 1)
#define YANG_IOCGETDATA _IOR(YANG_IOC_MAGIC, 2, int)
#define YANG_IOCSETDATA _IOW(YANG_IOC_MAGIC, 3, int)

#define YANG_IOC_MAXNR 3

#endif /* _YANG_H_ */
