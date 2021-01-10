#ifndef _YANG_H_
#define _YANG_H_

#include <linux/ioctl.h>


/*mem�豸�����ṹ��*/
struct mem_dev                                     
{                                                        
  char *data;                      
  unsigned long size;       
};

/* ������� */
#define YANG_IOC_MAGIC  'y'

/* �������� */
#define YANG_IOCPRINT   _IO(YANG_IOC_MAGIC, 1)
#define YANG_IOCGETDATA _IOR(YANG_IOC_MAGIC, 2, int)
#define YANG_IOCSETDATA _IOW(YANG_IOC_MAGIC, 3, int)

#define YANG_IOC_MAXNR 3

#endif /* _YANG_H_ */
