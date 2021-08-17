#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
void decide(void);
int var1 =0,var2=0,res=0;
char *str="asd";

module_param(var1 ,int , S_IRUSR | S_IWUSR );
module_param(var2 ,int , S_IRUSR | S_IWUSR );
module_param(str ,charp , S_IRUSR | S_IWUSR );
module_param(res ,int , S_IRUSR | S_IWUSR );

void decide()
{	
	if(strcmp(str,"add"))
	goto lable1;
	else
	{	res = var1+var2;
	goto res;}
	//-----------	
lable1:if(strcmp(str,"sub"))
	goto lable2;
	else
	{	res = var1-var2;
	goto res;}
	//-----------	
lable2:if(strcmp(str,"mul"))
	goto lable3;
	else
	{	res = var1*var2;
	goto res;}
	//-----------	
lable3:if(strcmp(str,"div"))
	goto lable4;
	else
	{	res = var1/var2;
	goto res;}
	//-----------	
lable4:if(strcmp(str,"ab"))
	printk(KERN_ALERT " enterd wrong string\n");		
	
res:printk(KERN_ALERT "param variable=%d & %d %s = %d \n",var1,var2,str,res);
}

static int hello_init(void)
{
	printk(KERN_ALERT "inside hello \n");
	decide();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "exiting hello \n");
	
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE ("CDAC");
MODULE_AUTHOR ("ASHISH");
MODULE_DESCRIPTION (" mudule paramater with 2 var & string with arith oprations based on string");
