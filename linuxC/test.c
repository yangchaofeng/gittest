#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

enum {
    TCP=3,
    TCP_PI,
    RTU
};

int main()
{
char s0[]="adc";
char str0[]={'a','b','c','d','e','f'};
char s[]="12345\0abc\0def";
char str[]={'1','\0','3','4','\0','5'};

printf("strlen =%d,sizeof= %d\n",strlen(s0),sizeof(s0));
printf("strlen =%d,sizeof= %d\n",strlen(str0),sizeof(str0));
printf("strlen =%d,sizeof= %d\n",strlen(s),sizeof(s));
printf("strlen =%d,sizeof= %d\n",strlen(str),sizeof(str));



	printf("=%d\n",TCP);
	printf("%d\n",TCP_PI);
	if(4==TCP_PI)
	goto fa;
	printf("%d\n",RTU);

	printf("########## end testing ##############\n");
	return 0;

fa:
	printf("The program is XXXXX\n");
}
