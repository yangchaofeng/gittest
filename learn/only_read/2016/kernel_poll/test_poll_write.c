#include <stdio.h>

int main()
{
	FILE *fp = NULL;
	int Buf[8]={10,20,30,40,50,60,70,80};
	
	
	/*���豸�ļ�*/
	fp = fopen("/dev/yang_poll","r+");
	if (fp == NULL)
	{
		printf("Open Dev memdev Error!\n");
		return -1;
	}
	

	fwrite(Buf, sizeof(int), 1, fp);
	
	sleep(5);
	fclose(fp);
	
	return 0;	

}
