/*
 * �򵥲�������Է�������ڴ档���ʹ�á�Cר�ұ�̡�P148��������ӣ��ᵼ���ڴ�
 * �ڴ�й¶����������ͼʹ��alloca()��������Ϊ������ѭ�����³��򵱻�����������
 * �����������ԣ������ʾ�ҿ��Է���3068MB�����ʹ�õ�����������# valgrind --leak-check=all ./a.out���м��ʱ����ʾ����2148MB��������ʾδ�ͷţ�
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
