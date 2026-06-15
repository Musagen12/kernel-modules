#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>

// You need to declare the variable first
// No need to pass it as a parameter since its globally accessible
static int age = 0;

module_param(age, int, S_IRUGO);

static int __init print_age(void) {
	printk(KERN_ALERT "The age is %d.", age);
	return 0;
}

static void __exit cleanup(void) {
	printk(KERN_ALERT "Goodbye!!");
}

module_init(print_age);
module_exit(cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Musagen12");
MODULE_DESCRIPTION("Exploring module parameters.");