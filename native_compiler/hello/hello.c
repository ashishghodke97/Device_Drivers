#include <linux/module.h>
#include <linux/init.h>
//#include <linux/moduleparam.h>

static int hello_init(void)
{
	printk(KERN_ALERT "HELLO WORLD\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "HELLO EXIT \n");
	
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE ("CDAC");
MODULE_AUTHOR ("ASHISH");
MODULE_DESCRIPTION ("just hello world module inside kernal");
