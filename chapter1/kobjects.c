#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kobject.h>

static struct kobject *kobj;
static char name[5] = "test";

static struct kobject *kobj2;
static char name2[5] = "test2";

static struct kobject * create_kobject(char *name, struct kobject *parent) {
	kobj = kobject_create_and_add(name, kobj);

	return kobj;
}

static int __init kobjects(void) {
	kobj = create_kobject(name, NULL);

	if(!kobj)
		return -ENOMEM;

	printk(KERN_INFO "Created kernel object 1.");

	kobj2 = create_kobject(name2, kobj2);

	if(!kobj2)
		return -ENOMEM;

	printk(KERN_INFO "Created kernel object 2.");

	return 0;
}

static void __exit cleanup(void) {
	printk(KERN_INFO "Goodbye!!");
}

module_init(kobjects);
module_exit(cleanup);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A deep dive into kobjects");