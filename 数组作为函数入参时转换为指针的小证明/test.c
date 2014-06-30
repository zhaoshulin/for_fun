/*
 * Purpose: 证明数组名字作为函数的参数时，被转化为了指针！
 * Author: 赵庶林
 * Date: 2014/6/30
*/

#include <stdio.h>
#include <string.h>

int func(char a[])
{
	int len = sizeof(a);//输出指针的大小，应该是8
	printf("In func(char a[]), sizeof(a) is %d.\n", len);
	return 0;
}

int main(void)
{
	char a[10];
	int len = sizeof(a);//输出数组的大小，应该是10
	printf("In main(), sizeof(a) is %d.\n", len);
	func(a);
	return 0;
}
