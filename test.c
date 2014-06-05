/*
* setjmp()的返回值受到longjmp()是否被调用的影响
×（1）如果longjmp(jmp_buf j, int i)还没被调用，setjmp返回0;
×（2）如果longjmp(jmp_buf j, int i)已经被调用，setjmp返回i。
*/

#include <stdio.h>
#include <setjmp.h>

#define RET_VALUE 2
int my_func();

jmp_buf j;

int my_func(void)
{
	printf("Enter into my_func()...\n");
	longjmp(j, RET_VALUE);
	printf("You will never see this in my_func!\n");
	return 0;
}

int main(void)
{
	int ret;

	printf("Enter into main()...\n");
	ret = setjmp(j);
	if(ret == 0)//第一次调用
	{
		printf("First call setjmp()...\n");
		my_func();
		printf("You will never see that in main!\n");
	}
	else if(ret == RET_VALUE)//longjmp已被调用啦
	{
		printf("I am back into main()!!!\n");
	}
	else
	{
		printf("setjmp return error!\n");
	}
	return 0;
}
