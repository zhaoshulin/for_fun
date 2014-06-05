/*
* setjmp()�ķ���ֵ�ܵ�longjmp()�Ƿ񱻵��õ�Ӱ��
����1�����longjmp(jmp_buf j, int i)��û�����ã�setjmp����0;
����2�����longjmp(jmp_buf j, int i)�Ѿ������ã�setjmp����i��
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
	if(ret == 0)//��һ�ε���
	{
		printf("First call setjmp()...\n");
		my_func();
		printf("You will never see that in main!\n");
	}
	else if(ret == RET_VALUE)//longjmp�ѱ�������
	{
		printf("I am back into main()!!!\n");
	}
	else
	{
		printf("setjmp return error!\n");
	}
	return 0;
}
