/*
 * Author: Zhao Shulin
 * Date: 2014/06/08
 * purpose: 测试类型提升。
*/

#include <stdio.h>

int main(void)
{	
	// printf()默认可以接收int型入参。
	printf("%d\n", sizeof('A'));//此句不会报警。
	
	long l = 1.999;
	printf("%ld\n", l);//一个常见的错误观点是：此句正常输出1.999。正确的观点是此句依然输出1,因为c语言编译器不是逐行解释的！
	printf("%d\n", l);//此句会报警，因为int型低于long型，结果输出1。
	printf("%ld\n", l);//此句输出1，因为在上一句中，l已经被降级为int 1 了。
	return 0;
}
