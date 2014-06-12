/*
 * Author: Zhao Shulin
 * Date: 2014/06/08
 * Purpose: ����һ����c����ʵ�ֵļ򵥵�����״̬�Զ���FSM��
 *          ע�⣺�˰汾��������
		s1 --------c1-------> s2 --------c2---------> s3
				       ^                       |
				       |		       |
				       -----------c3------------		       	
	����ʾ��ͼ����������׾ٵ��Ƴ���ת����

	��FSM�Ĺ��ܾ��ǣ���֪Ŀǰ״̬s����������c => ��һ��״̬�ʹ�������
	���Զ���һ�����ݽṹ���ͽ���NEXT_STEP������һ��״̬�ʹ�����������һ��.
	������Ҫ��һ�����ݽṹ������ת��Jump_table[state][condition]{NEXT_STEP};
					
							
				   
				    
				    
				    
				    	 
*/

#include <stdio.h>



typedef int State;
typedef int Condition;
typedef void (* Func)(State state, Condition condition);

#define STATES 4
#define STATE_1 0
#define STATE_2 1
#define STATE_3 2
#define STATE_TRAP 3

#define CONDITIONS 2
#define CONDITION_1 0
#define CONDITION_2 1

typedef struct NEXT_STEP
{
	State next_state;
	Func func;
}NEXT_STEP;

void func_1(State state, Condition condition)
{
	printf("func_1 has been triggered. State is %d, Condition is %d.\n", state, condition);
}

void func_2(State state, Condition condition)
{
	printf("func_2 has been triggered. State is %d, Condition is %d.\n", state, condition);
}

void func_3(State state, Condition condition)
{
	printf("func_3 has been triggered. State is %d, Condition is %d.\n", state, condition);
}

void func_trap(State state, Condition condition)
{
	printf("func_4 has been triggered. State is %d, Condition is %d.\n", state, condition);
}

struct NEXT_STEP n1 = {
	STATE_2,
	func_1		
};

struct NEXT_STEP n2 = {
	STATE_3,
	func_2
};

struct NEXT_STEP n3 = {
	STATE_2,
	func_3
};

struct NEXT_STEP nt = {
	STATE_TRAP,
	func_trap
};


// ��ʼ������ת��
struct  NEXT_STEP * Jump_table[STATES][CONDITIONS] = {
	&n1, &nt,
	&nt, &n2,
	&n3, &nt,
	&nt, &nt,
};

//���룺��ʼ״̬ + ������
//�������һ��״̬ + ���ô���������ֱ��trap��
void roll(State first_state)
{	
//	printf("Enter into roll()...\n");
	Condition condition;
	
	State current_state = first_state, next_state = -1;
	while(current_state != STATE_TRAP)
	{
		printf("current state is %d, and type the next condition with Enter: ", current_state);
		scanf("%d", &condition);
		
//		struct Jump_table * p = Jump_table[current_state][condition];
		(* (Jump_table[current_state][condition] -> func))(current_state, condition);
		current_state = Jump_table[current_state][condition] -> next_state;
		
	}
	
	printf("state is trapped!\n");
	return;
}

int main(void)
{
	printf("testing... first_state is 0, and the conditions are: 0, 1, 0, 1, 0, 0, 0\n");
	roll(0);
	return 0;
}
