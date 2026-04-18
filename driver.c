#include <linux/module.h>
#include <linux/init.h>

static int __init custom_init(void) {
	printk(KERN_INFO "Hello Linux World. Driver loaded.");
	return 0;
}

static void __exit custom_exit(void) {
	printk(KERN_INFO "Goodbye.");
}

module_init(custom_init);
module_exit(custom_exit);

MODULE_AUTHOR("Musagen12");
MODULE_DESCRIPTION("This is a test driver for local experimentation");
MODULE_LICENSE("GPL");