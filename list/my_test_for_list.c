#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


static struct list_head head; // This is the head of the list.
static struct my_list{
	int data;
	struct list_head node;
};//Define my own list type.


static int __init my_list_init(void)
{
	int i;
	struct my_list *real_list[5];

	printk(KERN_ALERT "Enter init()...\n");
	printk(KERN_ALERT "Now try to init a list.\n");
	INIT_LIST_HEAD(&head);
//	LIST_HEAD(&head); //Why it doesn't work???
	printk(KERN_ALERT "init a list succeed!\n");

	printk(KERN_ALERT "Now try to add some nodes to this list.\n");
//	struct my_list *real_list[5];//should put this in the front.
	for(i=0; i<5; i++)
	{
		if(!(real_list[i] = (struct real_list *)vmalloc(sizeof(struct my_list))))
		{
			printk(KERN_ALERT "vmalloc failed!\n");
			break;
		}
	real_list[i]->data = i;
	list_add_tail(&real_list[i]->node, &head);
	printk(KERN_ALERT "list[%d]'s data is: %d.\n", i, real_list[i]->data);
	
	}
	printk(KERN_ALERT "list_add_tail succeed!\n");		










	
	return 0;
}

static void __exit my_list_exit(void)
{
	printk(KERN_ALERT "Now exit...\n");
}

module_init(my_list_init);
module_exit(my_list_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhao Shulin");
MODULE_DESCRIPTION("This is a simple test file for linux_kernel list.");
