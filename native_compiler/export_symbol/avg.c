/* 
    1. Write a module program Add.c that exports the add functionality using the EXPORT_SYMBOL macro. Write another module program Average.c that calls the add function, exported by the Add Module and computes the average of 2 numbers. Manually implement and demonstrate this functionality.*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include "header.h"
void avg(void);
int var1=44 ,var2=66;

module_param(var1 ,int , S_IRUSR | S_IWUSR );
module_param(var2 ,int , S_IRUSR | S_IWUSR );



void avg()
{	
	printk(KERN_ALERT "average of %d & %d  =%d\n",var1,var2,(add(var1,var2)/2));
	
}

static int hello_init(void)
{
	printk(KERN_ALERT "inside hello \n");
	avg();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "exiting hello \n");
	
}


module_init(hello_init);
module_exit(hello_exit);
