#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init oop_init(void) {
	int *p = NULL;
	pr_info("A NULL pointer dereference.");
	*p = 1;
	return 0;
}

static void __exit oop_exit(void) {
	pr_info("Exiting the module.");
}

module_init(oop_init);
module_exit(oop_exit);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("An intentional oops.");