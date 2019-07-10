#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/types.h>
#include <functional>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <memory>

#include "libminui/include/minui/minui.h"

static GRSurface* gr_draw = NULL;

int main()
{
	int ret = -1;
	
	printf("%s %d yang add for test\n",__func__, __LINE__);
	ret = yanglibtest(4);
	printf("%s %d yang add for test ret=%d\n",__func__, __LINE__, ret);
	ret = gr_init(gr_draw);
	printf("%s %d yang add for test ret=%d\n",__func__, __LINE__, ret);
	
	//sleep(1);

	printf("%s %d yang add for test\n",__func__, __LINE__);
	return 0;
}
