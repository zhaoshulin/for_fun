#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mempool.h>
#include <linux/workqueue.h>
#include <linux/device-mapper.h>

static struct work_struct my_work;
static struct workqueue_struct *my_workqueue;
static struct kmem_cache *my_cache;
struct my_object{
	int should_add_later;
};
static mempool_t *my_pool;
static struct target_type my_cache_target = {
	.name = "my_cache",
	.version = {0,0,0},
	.module = THIS_MODULE,
	.ctr = NULL,
	.dtr = NULL,
// should add something later...

};

static void do_work(void)
{
	printk(KERN_ALERT "This is do_work!\n");	
}

static int __init  zsl_init(void)
{
	printk(KERN_ALERT "hello, zsl.\n");
	my_cache = kmem_cache_create("my_cache",sizeof(struct my_object), __alignof__(struct my_object), 0, NULL );
	
	if(!my_cache){
		printk(KERN_EMERG "error: kmem_cache_create failed!\n");
		return -1;
	}
	printk(KERN_ALERT "kmem_cache_create succeed!\n");

	my_pool = mempool_create(1024, mempool_alloc_slab, mempool_free_slab, my_cache);
	if(!my_pool){
		printk(KERN_EMERG "error: mempool_create failed!\n");
		kmem_cache_destroy(my_cache);
		return -2;
	}	
		printk(KERN_ALERT "mempool_create succeed!\n");

	my_workqueue = create_singlethread_workqueue("zsl_kcache");
	if(!my_workqueue){
		printk(KERN_EMERG "error: create_singlethread_workqueue failed!\n");
		return -3;
	}

	printk(KERN_ALERT "create_singlethread_workqueue succeed!\n");

	INIT_WORK(&my_work, do_work);
	//queue_work(my_workqueue, &do_work);
	if(dm_register_target(&my_cache_target)<0)
		{
			printk(KERN_EMERG "error: dm_register_target failed!\n");
			return -4;
		}
	else
		printk(KERN_ALERT "dm_register_target succeed!\n");

	return 0;

}

static void __exit zsl_exit(void)
{
	dm_unregister_target(&my_cache_target);
	printk(KERN_ALERT "dm_unregister_target succeed!\n");

	mempool_destroy(my_pool);
	printk(KERN_ALERT "mempool_destroy succeed!\n");
	
	kmem_cache_destroy(my_cache);
	printk(KERN_ALERT "kmem_cache_destroy succeed!\n");
		
	my_pool = NULL;
	my_cache = NULL;

	destroy_workqueue(my_workqueue);
	printk(KERN_ALERT "destroy_workqueue succeed!\n");

	
	printk(KERN_ALERT "goodbye, zsl.\n");
}

module_init(zsl_init);
module_exit(zsl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhao Shulin");
MODULE_DESCRIPTION("Stay Focus!");
