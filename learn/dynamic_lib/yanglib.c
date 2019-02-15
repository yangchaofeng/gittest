#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#define MY_LIB_VERSION "0.0.1"


int yangadd(int a,int b){
	return (a+b);
}
int yangsub(int a,int b){
	return a-b;
}
int yangtest(void){
	return 0;
}

char* get_lib_version(void){
	static char buff[10];
	sprintf(buff,MY_LIB_VERSION);
	return buff;
}
int add_yangma(int a,int b)
{
        time_t timep;
        time (&timep);
        printf(" #######  .so test by yang at %s ######\n",ctime(&timep));
        return a+b;
}

int sub_yangma(int a,int b)
{
        time_t timep;
        time (&timep);
        printf(" #######  .so test by yang at %s ######\n",ctime(&timep));
        return a-b;
}
int print_lib_info(void)
{
	printf(" #######  lib info[data:%s time:%s] ######\n", __DATE__, __TIME__);
	return 0;
}
