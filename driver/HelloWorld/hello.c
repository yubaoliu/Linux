#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void)
{
  printk(KERN_ALERT "TEST: hello world, this is hello world module\n");

  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "TEST: Good bye, from hello world module\n");
}

module_init(hello_init);
module_exit(hello_exit);
