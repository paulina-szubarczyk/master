#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/pagemap.h>
#include <linux/moduleparam.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hug");

static char* dev = NULL;
module_param(dev, charp, 0000);

static int __init init_fssuper(void) 
{

	struct super_block *sb;
	struct block_device *bdev;
	struct filename *tmp;
	
	if(dev == NULL)
		return -1;
	
	tmp = getname(dev);
	
	if(IS_ERR(tmp))
		return -1;
	
	bdev = lookup_bdev(tmp->name);
	
	if(IS_ERR(bdev))	
		return -1;
	
	sb = get_super(bdev);
	bdput(bdev);
	
	if(!sb)
	{
		printk(KERN_ERR "Can't load sb");
		return -1;
	}
	
	printk(KERN_INFO "Sucessfuly loaded sb");
	return 0;
}

static void __exit exit_fssuper(void)
{

}

module_init(init_fssuper);
module_exit(exit_fssuper);