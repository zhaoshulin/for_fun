/*
 * Author: Zhao Shulin
 * Date: 2014/06/08
 * purpose: ��������������
*/

#include <stdio.h>

int main(void)
{	
	// printf()Ĭ�Ͽ��Խ���int����Ρ�
	printf("%d\n", sizeof('A'));//�˾䲻�ᱨ����
	
	long l = 1.999;
	printf("%ld\n", l);//һ�������Ĵ���۵��ǣ��˾��������1.999����ȷ�Ĺ۵��Ǵ˾���Ȼ���1,��Ϊc���Ա������������н��͵ģ�
	printf("%d\n", l);//�˾�ᱨ������Ϊint�͵���long�ͣ�������1��
	printf("%ld\n", l);//�˾����1����Ϊ����һ���У�l�Ѿ�������Ϊint 1 �ˡ�
	return 0;
}
