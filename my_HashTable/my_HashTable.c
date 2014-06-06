/* 
 * Author: Zhao Shulin
 * Date: 2014/06/06
 * Purpose: A simple implemetation of HashTable in c. 
 * 主要思路：我只要实现2个数据结构+5个接口即可：
 *              数据结构：(1)hashnode_struct (2)hashtable_struct
 *              接口：(1)hashtable_init() (2)hashtable_insert(key, value) (3)hashtable_remove(key) (4)hashtable_lookup(key) (5)hashtable_delete()	
 *              一个附加的哈希函数：功能是根据key->position,采用经典的ELF算法。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_MAX_SIZE 1024

int hashtable_init();
unsigned int hashtable_ELF_hash();


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
	if(key == NULL | value == NULL)
	{
		printf("Error input!\n");
		return -2;
	}
	
	
	return 0;	
}





int main(void)
{
	printf("hashtable_init() testing...\n");
	hashtable_init();
	printf("hashtable_ELF_hash() testing...\n");
	printf("key is %s => position is %d.\n", "ab", hashtable_ELF_hash("ab"));

	return 0;
}
