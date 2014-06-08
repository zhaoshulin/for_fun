/*
 * Author: Zhao Shulin
 * Date: 2014/06/06
 * Purpose: A simple implemetation of HashTable in c. 
 * 主要思路：我只要实现2个数据结构+5个接口即可：
 *              数据结构：(1)hashnode_struct (2)hashtable_struct
 *              接口：(1)hashtable_init() (2)hashtable_insert(key, value) (3)hashtable_remove(key, value) (4)hashtable_lookup(key) (5)hashtable_delete()	
 *              一个附加的哈希函数：功能是根据key->position,采用经典的ELF算法。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_MAX_SIZE 1024

int hashtable_init();
unsigned int hashtable_ELF_hash();
int hashtable_insert();
int hashtable_remove();
int hashtable_lookup();
int hashtable_delete();

struct hashnode_struct
{
	char * key;
	int value;
	struct hashnode_struct * next;
};
typedef struct hashnode_struct hashnode;//hashnode_struct定义完毕

hashnode * hashtable[HASH_TABLE_MAX_SIZE];
int size;//hashtable_struct定义完毕


int hashtable_init(void)
{
	size = 0;
        if(memset(hashtable, 0, sizeof(hashnode *) * HASH_TABLE_MAX_SIZE ) == NULL)
	{
		printf("Error in memset of hashtable_init!\n");
		return -1;
	}
	printf("hashtable_init succeed.\n");
	return 0;
}//hashtable_init()定义完毕


unsigned int hashtable_ELF_hash(char * key)
{
	unsigned int pos = 0;
	unsigned int x = 0;
	
	while(*key)
	{
		pos = (pos << 4) + (*key ++);
		if((x = pos & 0xF0000000L) != 0)
		{
			pos ^= (x >> 24);
			pos &= ~x;
		}
	}
	return (pos & 0x7FFFFFFF);
}//哈希函数定义完毕

int hashtable_insert(char * key, int value)
{
	unsigned int pos;
	hashnode * head;

	if(key == NULL | &value == NULL)
	{
		printf("Error input!\n");
		return -2;
	}
	
	if(size >= HASH_TABLE_MAX_SIZE)
	{
		printf("Error: Out of hash_table memory!\n");
		return -3;
	}	

	pos = hashtable_ELF_hash(key);
	head = hashtable[pos];
	//遍历该链表，如果已经存在了<key, value>对，则不用再插入了
	while(head)
	{
		if(head->value == value)//已经存在
		{
			printf("The <%s, %d> pair already exists, no need to insert again.\n", key, value);
			return 0;
		}
		head = head->next;
	}

	//遍历完毕，未发现已存在的<key, value>对。需要插入
	hashnode * newNode = (hashnode *)malloc(sizeof(hashnode));
	memset(newNode, 0x00, sizeof(hashnode));//初始化完毕

	newNode -> value = value;
	newNode -> key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(newNode -> key, key);//赋值完毕

	newNode -> next = hashtable[pos];
	hashtable[pos] = newNode;//尾插法

	size ++;
	
	printf("hashtable(%s, %d) is successful.\n", key, value);	
	
	return 0;	
}

int hashtable_remove(char * key, int value)
{
	unsigned int pos = hashtable_ELF_hash(key);
	hashnode * head = hashtable[pos];
	hashnode * before = NULL;
	//如果head->value就等于value，这是特殊情况，特殊处理：
	if(head -> value == value)
	{
		printf("remove <%s, %d> succeed.\n", key, value);
		hashtable[pos] = head -> next;
		free(head);
		return 0;
	}
	before = head;
	head = head -> next;
	//接下来，就是链表的删除一个节点操作了
	while(head)
	{
		if(head -> value == value)
		{
			before -> next = head -> next;
			free(head);
			printf("remove <%s, %d> succeed.\n", key, value);
			
			return 0;
		}
		before = head;
		head = head -> next;
	}
	//如果没有找到<key, value>对，打印错误
	printf("Error: <%s, %d> pair no found!\n", key, value);
	return -4;
}

int hashtable_lookup(char * key)
{
	unsigned int pos = hashtable_ELF_hash(key);
	hashnode * head = hashtable[pos];
	if(head == NULL)//说明该key没有对应的任何value
	{
		printf("Error: key is %s, but there is no value for it!\n", key);
		return -5;
	}
	
	//接下来，就是链表的遍历打印过程了
	while(head)
	{
		printf("<%s, %d> ", key, head -> value);
		head = head -> next;
	}
	printf("\n");
	
	return 0;
}

int hashtable_delete(void)
{
	int i;
	for(i = 0; i < HASH_TABLE_MAX_SIZE; i ++)
	{
		if(hashtable[i] != NULL)
		{
			hashnode * head = hashtable[i];
			hashnode * after = NULL;
			while(head)
			{
				after = head -> next;
				free(head -> key);
				free(head);
				head = after;
			}
			
		}
	}
	printf("hashtable has been deleted successfully.\n");
	return 0;
}

int main(void)
{
	char * key = "a";

	printf("hashtable_init() testing...\n");
	hashtable_init();

	printf("hashtable_ELF_hash() testing...\n");
	printf("key is %s => position is %d.\n", "ab", hashtable_ELF_hash("ab"));

	printf("hashtable_insert() testing...\n");
	hashtable_insert(key, 1);
	hashtable_insert("A", 2);
	hashtable_insert(key, 2);
	hashtable_insert(key, 1);
	hashtable_insert(key, 3);
	hashtable_insert(key, 4);
	hashtable_insert(key, 5);

	printf("hashtable_remove() testing...\n");
	hashtable_remove(key, 1);
	hashtable_remove(key, 1);
	hashtable_remove(key, 2);
	hashtable_remove(key, 2);	

	printf("hashtable_lookup() testing...\n");
	hashtable_lookup(key);
	hashtable_lookup("b");

	printf("hashtable_delete() testing...\n");
	hashtable_delete();
	return 0;
}
