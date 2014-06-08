/*
 * 简单测试你可以分配多大的内存。如果使用《C专家编程》P148里面的例子，会导致内存
 * 内存泄露。所以我试图使用alloca()，但是因为陷入死循环导致程序当机。所以我在
 * 虚拟机里面测试，结果显示我可以分配3068MB，如果使用第三方检测软件# valgrind --leak-check=all ./a.out进行检测时，显示分配2148MB。并且提示未释放！
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{	
	int MB = 0;
	while(malloc(1 << 20))
	{
		++ MB;
	}
	printf("You can allocate %d MB memory totally.\n", MB);
	return 0;
}
