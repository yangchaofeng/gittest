#include <stdio.h>
#include <stdlib.h>

extern int testnum;

int main()
{
	print_lib_info();
	printf("yang add for test %d\n", add_yangma(4,7));	
	printf("yang add for test %d\n", yangadd(4,7));
	
	for (int i=0;i<10;i++) {
		testnum++;
		printf("lib data testnum = 0x%x\n", testnum);
		sleep(1);
	}
	return 0;
}
