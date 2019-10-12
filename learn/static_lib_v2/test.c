#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int x=9,y=4;
	int val000,val001;

	val000=add_by_(x,y);
	val001=sub_by_(x,y);

	printf("val000=%d\n",val000);
	printf("val001=%d\n",val001);


	return 0;
}
