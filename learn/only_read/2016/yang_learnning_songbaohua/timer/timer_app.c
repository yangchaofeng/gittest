#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>

main()
{
	int fd;
	int counter = 0;
	int old_counter = 0;

	/*��/dev/second�豸�ļ�*/
	fd = open("/dev/second", O_RDONLY);
	
	
	if (fd != - 1)
	{
		while (counter <= 10)
		{
			read(fd,&counter, sizeof(unsigned int));//��Ŀǰ����������
			if(counter!=old_counter)
			{
				printf("seconds after open /dev/second :%d\n",counter);
				old_counter = counter;
			}
		}
	}
	else
	{
		printf("Device open failure\n");
	}
	 
	close(fd);
}