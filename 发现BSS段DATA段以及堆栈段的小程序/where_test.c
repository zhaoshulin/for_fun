/*
*未初始化的全局和静态变量保存在.bss段内
*初始化后的全局和静态变量保存在.data段内
*alloca()函数分配栈中的内存
*malloc()函数分配堆中的内存
*/

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

int my_global;
static char my_static;
int main(void)
{
	printf("The .bss segment is near %p.\n", &my_global);
	
	my_static = 'c';
	printf("The .data segment is near %p.\n", &my_static);
	
	char * my_stack = (char *)alloca(1);
	char * my_heap = (char *)malloc(1);
	printf("The stack top is near %p.\n", my_stack);
	printf("The heap top is near %p.\n", my_heap);

	char * my_stack2 = (char *)alloca(1);
	char * my_heap2 = (char *)malloc(1);

	if(my_stack < my_stack2)
		printf("The stack is growing up...\n");
	else if(my_stack > my_stack2)
		printf("The stack is growing down...\n");
	else
	{
		printf("Erro in stack!\n");
		return -1;
	}
	

	if(my_heap < my_heap2)
		printf("The heap is growing up...\n");
	else if(my_heap > my_heap2)
		printf("The heap is growing down...\n");
	else 
	{
		printf("Error in heap!\n");
		return -2;
	}	
	return 0;
}

