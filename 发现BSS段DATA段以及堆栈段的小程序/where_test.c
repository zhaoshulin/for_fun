/*
*未初始化的全局和静态变量保存在.bss段内
*初始化后的全局和静态变量保存在.data段内
*函数内局部变量保存在堆栈
*/

#include <stdio.h>

int my_global;
static char my_static;
int main(void)
{
	printf("The .bss segment is near %p.\n", &my_global);
	
	my_static = 'c';
	printf("The .data segment is near %p.\n", &my_static);
	
	int my_local;
	printf("The stack top is near %p.\n", &my_local);
	int my_local2;
	if(&my_local < &my_local2)
		printf("The stack is growing up...\n");
	else if(&my_local > &my_local2)
		printf("The stack is growing down...\n");
	else
	{
		printf("Error in stack!\n");
		return -1;
	}
	return 0;
}

