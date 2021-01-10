#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


//#define DEBUG
/***********************  modify begin ******************************************/

/***********************  modify end   ******************************************/
int main(int argc,char *argv[])
{
#ifdef DEBUG
	int i;
	printf("argc=%d\n",argc);
	for(i=0;i<argc;i++)
	{
		printf("argv[%d]=%s\n",i,argv[i]);
		printf("int data is argv[%d]=%d\n",i,atoi(argv[i]));
	}
#endif
/***********************  modify begin ******************************************/


	extern char **environ; 
	int i; 
	for(i=0; environ[i]!=NULL; i++) 
		printf("%s\n", environ[i]);
/***********************  modify end   ******************************************/
	return 0;
}
