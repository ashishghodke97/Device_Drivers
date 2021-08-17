#include<linux/module.h>
#include<linux/init.h>

static int add(int a,int b)
{	
	return a+b;
}
EXPORT_SYMBOL(add);
static int hello_init(void)
{
	printk(KERN_ALERT "inside hello \n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "exiting hello \n");
	
}


module_init(hello_init);
module_exit(hello_exit);

