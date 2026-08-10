#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init output_init(void) {
	pr_info("Loading the kernel module.");
	return 0;
}

static void __exit output_exit(void) {
	pr_info("Unloading the kernel module.");
}

module_init(output_init);
module_exit(output_exit);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A demonstration for a printk alternative.");