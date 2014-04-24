#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/blkdev.h>

static struct radix_tree_root root;

static int __init radix_tree_test_init(void)
{	
	int key;
	void *pointer;
	
	
	printk(KERN_ALERT "Now start to init a radix tree...\n");
	INIT_RADIX_TREE(&root, GFP_KERNEL);
	printk(KERN_ALERT "This radix tree has been inited succeed!\n");

	printk(KERN_ALERT "Now start to insert 5 nodes into this radix tree, hope it works~~~\n");
	for(key=0; key<5; key++)
	{
		pointer = (void *) __get_free_page(GFP_KERNEL);
		if(!pointer)
		{
			printk(KERN_EMERG "get free page failed!\n");
			return -1;
		}
		memcpy(pointer, "I love you.", sizeof("I love you."));
		if(radix_tree_insert(&root, key, pointer))
		{
			printk(KERN_EMERG "radix tree insert failed!\n");
			return -2;
		}
	}
	printk(KERN_ALERT "radix tree insert succeed!\n");

	printk(KERN_ALERT "now try to look up, which means: key=>value.\n");
	for(key=0; key<5; key++)
	{
		pointer = radix_tree_lookup(&root, key);
		printk(KERN_ALERT "This radix tree[%d]'s value is: %s\n", key, (char*)pointer);
		printk(KERN_ALERT "look up succeed!\n");
		
	}

	return 0;
}

static void __exit radix_tree_test_exit(void)
{	
	int key;
	void *pointer;	
	printk(KERN_ALERT "now start to delete this radix tree and exit! Stay focus, boy!\n");
	for(key=1; key<5; key++)
	{
		pointer = radix_tree_lookup(&root, key);
		radix_tree_delete(&root, key);
		free_page(pointer);
	}
	printk(KERN_ALERT "delete this radix tree succeed!\n");
	printk(KERN_ALERT "radix_tree_test_exit succeed!\n");
}

module_init(radix_tree_test_init);
module_exit(radix_tree_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhao Shulin");
MODULE_DESCRIPTION("This is a simple test file for radix_tree.");
