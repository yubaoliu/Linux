#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h> //file operations. which of course allows use open/close, read/write to device
#include <linux/cdev.h> //this is a char driver; makes cdev available
#include <linux/semaphore.h> //synchronization behaviors

#include <linux/uaccess.h> //copy_to_user; copy_from_user

//(1) Create a structure for our fake device
struct fake_device{
  char data[100];
  struct semaphore sem;
} virtual_device;

//(2) To later register our device we need a cdev object and some other varibles
struct cdev *mcdev; //m stands for "my"
int major_number;
int ret; // Will be used to hold return values of functions; this is because the kernel stack is very small. So declaring variables all over the pass in our module functions eats up the stack very fast

dev_t dev_num; //will hold major number that kernel gives us

#define DEVICE_NAME "Mycharacterdevice"

//(7) Called on device_file open
//  inode reference to the file on disk
//  and contains information about that file
// struct file is represents an abstract open file
int device_open(struct inode *inode, struct file *flip)
{
  //only allow one process to open this device by using a semaphore as mutual exclusive lock - muttex
  if(down_interruptible(&virtual_device.sem)!=0)
  {
    printk(KERN_ALERT "Mycharacterdevice: could not lock device during open\n");
    return -1;
  }

  printk(KERN_INFO "Mycharacterdevice: opened device\n");
  return 0;
}

//(8) called when user wants to get information from the device
ssize_t device_read(struct file* filp, char* buffStoreData, size_t bufCount, loff_t* curOffset)
{
  //take data from kernel space(device) to user space (process)
  //copy_to_user (destination,source, sizeToTransfer)
  printk(KERN_INFO "Mycharacterdevice: Reading from device\n");
  ret=copy_to_user(buffStoreData, virtual_device.data, bufCount);
  return ret;
}

//(9) called when user wants to send information to the device
ssize_t device_write(struct file* filp, const char* bufSourceData, size_t bufCount, loff_t* curOffset)
{
  //send data from user to kernel
  //copy_from_user(dest, source, count)
  printk(KERN_INFO "Mycharacterdevice: writing to device");
  ret=copy_from_user(virtual_device.data,bufSourceData, bufCount);
  return ret;
}

//(10) called when close
int device_close(struct inode *inode, struct file *filp)
{
  //by calling up which is opposite of down for semaphore, we release the mutes that we obtained at device open, this has the effect of allowing other process to use the device now
  up(&virtual_device.sem);
  printk(KERN_INFO "mycharacterdevice: closed device\n");
  return 0;
}


//(6) Tell the kernel which functions to call when user operates on our device file
struct file_operations fops={
  .owner=THIS_MODULE, //prevent unloading of this module when operations are in use
  .open=device_open, //Points to the method to call when opening the device
  .release=device_close,
  .write=device_write,
  .read=device_read
};

static int driver_entry(void)
{
  //(3) Register our device with the system: a two step process
  //Step(1) use dynamic allocation to assign our device
  //  a major number --  alloc_chrdev_region(dev_t*,unit fminor, uint count,char* name)
  ret=alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
  if(ret<0){
    printk(KERN_ALERT "MyCharacterdevice: failed to allocate a major number\n");
    return ret; //propagate error
  }
  major_number=MAJOR(dev_num);
  printk(KERN_INFO "mycharacterdevice: major_number is %d \n",major_number);
  printk(KERN_INFO "\tuse \"mknod /dev/%s c %d 0\" for device file \n",DEVICE_NAME, major_number);
  //Step(2)
  mcdev=cdev_alloc(); //create our cdev structure, initialized our cdev
  mcdev->ops=&fops;
  mcdev->owner=THIS_MODULE;

  //now that we created cdev, we have to add it to the kernel
  ret=cdev_add(mcdev,dev_num,1);
  if(ret<0)
  {
    printk(KERN_ALERT "Mycharacterdevice: unable to add cdev to kernel\n");
  }

  //(4) Initialize our semaphore
  sema_init(&virtual_device.sem,1); //initialize value of one

  return 0;
}

static void driver_exit(void)
{
  //(5) unregister everything in reverse order
  //(a)
  cdev_del(mcdev);
  //(b)
  unregister_chrdev_region(dev_num,1);
  printk(KERN_ALERT "Mycharacterdevice: unloaded module\n");

}


module_init(driver_entry);
module_exit(driver_exit);
