/*
    1. Write a character driver with open and close functionality. Test the driver by writing an application that opens and closes the device driver. When open or closed, the open and close calls in the driver should be executed. */
    
#include<linux/module.h>
#include <linux/kernel.h> 
#include <linux/fs.h>		// file operations structure- which of course allows use to open/close, read/write to device
#include <linux/cdev.h> 	//this is a char driver; makes cdev available 
#include <linux/semaphore.h> 
#include <linux/uaccess.h>  	//copy_to_user;copy_from_user

//(1) creating a structure for our fake device
struct fake_device
{
	char data[100];
	struct semaphore sem;
} virtual_device;

//(2) to later register our device we need a cdev object & some other var 


struct cdev *mcdev; //m=mydevice
int major_number; //store major number-extracted from dev_t using macro - mknod /director/file major minor

int ret;			// will be used to hold return values of functions;
dev_t dev_num;	//will hold major number that kernel gives us //name--> appears in /proc/devices "mydevicename2"

#define DEVICE_NAME "mydevicename2"


		//(7) called ondevice file open 
		//inode reference to the file on disk
		//& contains info about file 
		//struct file is represents an abstract open file
static int device_open(struct inode *inode, struct file *filp)
{
	//only allow one process to open this device by using a semaphore as mutual exclusivelock- mutex	
	if(down_interruptible(&virtual_device.sem) != 0)
	{
		printk(KERN_ALERT "mydevicename2 : could not lock device during open");
		return -1;
	}
	printk(KERN_INFO "mydevicename2 : odevice opened ");
	return 0;
}
	//(8)called when user wants to get info from from the device.
ssize_t device_read(struct file* filp, char* bufStoreData, size_t bufCount , loff_t* curoffset)
	{
	//take data from kernel space(device)  to  userspace (process)
	//copy_to_user(destination , source , sizeto transfer);
	
	printk(KERN_INFO "mydevicename2: reading from device ");
	ret = copy_to_user (&bufStoreData, virtual_device.data, bufCount);
	return ret;
	}
	
	//(9) called when user wants to send info to the device	
ssize_t device_write(struct file* filp, const char* bufSourceData , size_t bufCount, loff_t* curoffset)
	{
	//send data from user to kernel
	//copy_from_user (dest, source, count)
	
	printk(KERN_INFO "mydevicename2: writing to device");
	ret = copy_from_user(&virtual_device.data,bufSourceData, bufCount);
	return ret;	
	}
	
	





	//(10) called upon user close
static int device_close(struct inode *inode, struct file *filp)
{
	//by calling up, which is opposite of down for semaphore , we release the mutex that we obtained at device open
	//this allows other process to use the device now
	up(&virtual_device.sem);
	printk(KERN_INFO "mydevicename2: closed device");
	return 0;
}


//(11) tell the kernel which function to call when user operates on our device  file
struct file_operations fops = {
	.owner = THIS_MODULE, //prevent unloading of this module when operations are in use
	.open = &device_open, //points to the method to call when opening the device
	.release = &device_close,//points to the method to call when closing the device 
	.read = device_read,//points to method to call when reading from device
	.write = device_write,//points to method to call when writing to device
	};
static int driver_entry(void)
{
	//(3)here Register our device with system: a 2step process
	//step1: using dynamic allocation to assign our device
	//a major num--alloc chrdev_region(dev_t*, uint fminor, uint count, char* name)
	
	ret = alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
	if(ret < 0)
	{	//alloc returns negative number if there is an error
		printk(KERN_INFO "mydevicename2 is failed to allocate major number\n");
		return ret;
	}

		major_number = MAJOR (dev_num); //extracts mjr num stored in dev_num structure
		printk(KERN_INFO "mydevicename2 : najor number is %d ",major_number);
		printk(KERN_INFO "\t use \"mknod /dev/%s  c %d  0 \" for device_file",DEVICE_NAME,major_number);
		
		//step2 
		mcdev = cdev_alloc();	//create our cdev structure , initialized our cdev
		mcdev->ops = &fops;	// it is structure in which we define function calls
		mcdev->owner = THIS_MODULE;
						// now that we created cdev, we have to add it to the kernel
						// int cdev_add(struct cdev* dev, dev_t num,unsigned int count )
		ret = cdev_add(mcdev, dev_num,1);
		if(ret < 0)
		{
			printk(KERN_ALERT "mydevicename2: unable to add cdev to kernel \n");
			return ret;
		}
		//step ----------------
		sema_init(&virtual_device.sem,1); //inital value of one
		

return 0;
}

	

static void driver_exit(void)	//step(4) exit module, in this unregister everything yove registerd 
{
	cdev_del(mcdev); //unregistering everything in reverse order.
	unregister_chrdev_region(dev_num, 1);
	printk(KERN_ALERT "mydevicename2: unload module ");
}


module_init(driver_entry);
module_exit(driver_exit);
