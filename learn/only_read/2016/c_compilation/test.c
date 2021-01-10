#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

#ifdef EM_ODM_A01	
	printf("yang test and defind\n");
#else
	printf("yang test and no defind\n");
#endif

	return 0;
}
