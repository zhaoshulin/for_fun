#include <stdio.h>
#include "stdlib.h"
#include "command.h"

int main()
{
	printf("#### time: %s ####\n", __TIME__);
	command();//����command.c�ﶨ���C����
	
	#ifdef PUB_H
		puts("##### the pub.h is included #####");
	#else
		puts("##### the pub.h is not included #####");
	#endif

	return 0;
}
