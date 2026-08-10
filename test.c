#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int age;
module_param(age, int, S_IRUGO);


static int __init test_init(void) {
	int multiple;

	pr_info("This is just a test module");
	multiple = age * 3;
	pr_info("The multiple is %d.", multiple);

	return 0;
}

static void __exit test_exit(void) {
	pr_info("Goodbye kernel.");
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("Musagen12");
MODULE_DESCRIPTION("Just a test module.");
MODULE_LICENSE("GPL");
