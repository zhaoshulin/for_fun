#include <stdio.h>
#include "stdlib.h"
#include "command.h"

int main()
{
	printf("#### time: %s ####\n", __TIME__);
	command();//调用command.c里定义的C函数
	
	#ifdef PUB_H
		puts("##### the pub.h is included #####");
	#else
		puts("##### the pub.h is not included #####");
	#endif

	return 0;
}
