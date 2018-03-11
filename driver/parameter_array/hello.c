#include <linux/init.h>
#include <linux/module.h>

#include <linux/moduleparam.h>

int param_var[3]={0,0,0};

module_param_array(param_var,int,NULL,S_IRUSR|S_IWUSR);

void display(void)
{
  printk(KERN_ALERT "TEST:param_var[0]=%d \n", param_var[0]);
  printk(KERN_ALERT "TEST:param_var[1]=%d \n", param_var[1]);
  printk(KERN_ALERT "TEST:param_var[2]=%d \n", param_var[2]);
}

static int hello_init(void)
{
  printk(KERN_ALERT "TEST: hello world, this is hello world module\n");
  display();

  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "TEST: Good bye, from hello world module\n");
}

module_init(hello_init);
module_exit(hello_exit);
