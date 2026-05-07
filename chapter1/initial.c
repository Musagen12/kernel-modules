// The simplest kernel module
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Musagen12");
MODULE_DESCRIPTION("A hello world module");

static int __init hello_entry(void) {
	printk(KERN_INFO "Hello world.");
	return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "Goodbye world.");
}

// "hello_entry()" is registered as the module's entry
module_init(hello_entry);
// "hello_exit()" is registered as the module's exit
module_exit(hello_exit);