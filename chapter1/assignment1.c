// Create a kernel program that takes 2 variables and adds them returning the sum as a kernel alert

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int variable1;
static int variable2;
static int sum;
static int i;
static int myarray[4];
static int array_count;

// A simple variable
module_param(variable1, int, S_IRUGO);
module_param(variable2, int, S_IRUGO);

// An array
module_param_array(myarray, int, &array_count, S_IRUGO);

static int __init calculate_sum(void) {
	printk(KERN_INFO "Loaded the kernel module");

	sum = variable1 + variable2;
	printk(KERN_ALERT "The sum is: %d", sum);

	for (i = 0; i < (sizeof(myarray) / sizeof(myarray[0])); i++) {
		printk(KERN_ALERT "The array variable is: %d.", myarray[i]);
	}

	printk(KERN_ALERT "The number of arguments passed into the array is: %d.", array_count);

	return 0;
}

static void __exit cleanup(void) {
	printk(KERN_INFO "Unloading the kernel module.");
}

module_init(calculate_sum);
module_exit(cleanup);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Calculating the sum of 2 variables.");