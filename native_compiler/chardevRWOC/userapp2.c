/* Write a character driver with open and close functionality. Test the driver
 by writing an application that opens and closes the device driver. When open 
 or closed, the open and close calls in the driver should be executed. */
 
 #include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#define DEVICE "/dev/mydevicename2" 
int main () 
{
	 int i, fd=0; char ch, write_buf[100], read_buf[100];
	 fd = open(DEVICE, O_RDWR); //open for reading and writing 
	 if(fd == -1){
	 printf("file %s either does not exist or has been locked by another process\n", DEVICE); 
	 exit(-1);
	 }
	 printf (" the Device Driver  %s has opened  \n ", DEVICE );
	 
	 printf ("r = read from device\nw = write to device\nenter command: "); 
	 scanf ("%c ",&ch); 
	 
	 switch (ch)
	 {
	 	case 'w': 
	 		printf ("enter data: ");
	 		scanf (" [^\n]", &write_buf); 
	 		write(fd, write_buf, sizeof(write_buf)); 
	 		break; 
	 	case 'r':
	 		read (fd, read_buf, sizeof(read_buf));
	 		printf ("device: s\n", read_buf); 
	 		break; 
	 	default: 
	 		printf("command not recognized\n"); 
	 		break; 
	 } 
	 
	 close(fd);
	 return 0;

}


