#include <stdio.h>
#include <stdlib.h>

typedef int data_type;

typedef struct double_listnode{
	data_type data;
	struct double_listnode *prior, *next;
}double_listnode_t, *double_listnode_p;

static double_listnode_t *init_double_list(int n);
static double_listnode_t *get_double_listnode(double_listnode_p head, int i);
static void insert_double_listnode(double_listnode_p head, int i, data_type data);
static void delete_double_listnode(double_listnode_p head, int i);
static void print_double_listnode(double_listnode_p head);
static void destroy_double_list(double_listnode_p head);



static double_listnode_t *init_double_list(int n)
{
	int i;
	double_listnode_p head, p, s;
	
	head = (double_listnode_t *)malloc(sizeof(double_listnode_t));
	head -> prior = head -> next = head;

	p = head;
	for(i = 0; i < n; i++)
	{
		s = (double_listnode_t *)malloc(sizeof(double_listnode_t));
		s -> data = i + 1;

		s -> next = head;
		head -> prior = s;

		s -> prior = p;
		p -> next = s;

		p = s;
	}
	return head;
}



static double_listnode_t *get_double_listnode(double_listnode_p head, int i)
{
	double_listnode_p p = head;
	int j = 0;

	while(p -> next != head && j < i)
	{
		p = p -> next;
		j ++;
	}
	
	if(i == j)
		return p;
	else
		return NULL;
}

static void insert_double_listnode(double_listnode_p head, int i, data_type data)
{
	double_listnode_p tmp, p = NULL;
	
	p = get_double_listnode(head, i-1);
	if(p == NULL)
	{
		fprintf(stderr, "position error\n");
		exit(-1);
	}
	
	tmp = (double_listnode_t *)malloc(sizeof(double_listnode_t));
	tmp -> data =data;
	tmp -> prior = p;
	tmp -> next = p -> next;
	p -> next -> prior = tmp;
	p -> next = tmp;
}


static void delete_double_listnode(double_listnode_p head, int i)
{
	double_listnode_p p = NULL;
	p = get_double_listnode(head, i);
	if(p == NULL || p == head){
		fprintf(stderr, "position error\n");
		exit(-1);
	}
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
}


static void print_double_listnode(double_listnode_p head)
{
	double_listnode_p p = head->next;
	while(p != head){
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}



static void destroy_double_list(double_listnode_p head)
{
	double_listnode_p s, p = head->next;
	while(p != head)
	{
		s = p;
		p = p->next;
		free(s);
	}
	free(head);
}


int main(void)
{
	int a = 10;
	double_listnode_p head;
	
	head = init_double_listnode(a);
	print_double_listnode(head);

	insert_double_listnode(head, 7, 11);
	print_double_listnode(head);

	delete_double_listnode(head, 5);
	print_double_listnode(head);

	destroy_double_listnode(head);
	return 0;
}


