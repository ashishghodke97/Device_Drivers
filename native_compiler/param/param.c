#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
void display(void);
int var1 =0;
module_param(var1 ,int , S_IRUSR | S_IWUSR );

void display()
{	
	printk(KERN_ALERT "param variable=%d\n",var1);
	
}

static int hello_init(void)
{
	printk(KERN_ALERT "inside hello \n");
	display();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "exiting hello \n");
	
}


module_init(hello_init);
module_exit(hello_exit);
