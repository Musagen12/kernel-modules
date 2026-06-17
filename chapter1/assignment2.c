#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

// Variable declaration
static int age;
static int array[5];
static int i;
static int array_count;

// Setting the module parameters
module_param(age, int, S_IRUGO);
module_param_array(array, int, &array_count, S_IRUGO);

static int __init entry_func(void) {
	printk(KERN_INFO "The age is %d", age);

	for (i = 0; i < array_count; i++) {
		printk(KERN_INFO "Array element %d: %d", i, array[i]);
	}

	return 0;
}

static void __exit cleanup(void) {
	printk(KERN_INFO "Exitting the function");
}

module_init(entry_func);
module_exit(cleanup);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Something");