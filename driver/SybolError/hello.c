#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

//Just declared
int g_value;

static int hello_init(void)
{
  printk(KERN_ALERT "TEST: hello world, this is hello world module\n");
  printk("Hello world!!. Value of g_value is %d \n",g_value);
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "TEST: Good bye, from hello world module\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yubao");
MODULE_DESCRIPTION("Kernal Sybmol Table");
