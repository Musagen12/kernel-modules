#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kobject.h>

static struct kobject *obj;

// Array size isn't defined(Kinda dangerous in the kernel without initialization) but the array is initialized
static struct kobject *kobj;
static char name[] = "charles";

static struct kobject *kobj1;
static char name2[] = "harry";

static struct kobject * create_kobject(char *name, struct kobject *parent) {
	obj = kobject_create_and_add(name, parent);

	return obj;
}

static int __init kobjects(void) {
	kobj = create_kobject(name, NULL);

	if(!kobj)
		return -ENOMEM;

	printk(KERN_INFO "Created kernel object %s.", kobj->name);
	printk(KERN_INFO "kobject %s has a kref of %d.", kobj->name, kobj->kref.refcount.refs.counter);

	kobj1 = create_kobject(name2, kobj);

	if(!kobj1)
		return -ENOMEM;

	printk(KERN_INFO "Created kernel object %s.", kobj1->name);
	printk(KERN_INFO "Kernel object %s is the child of object %s.", kobj1->name, kobj1->parent->name);
	printk(KERN_INFO "kobject %s has a kref of %d.", kobj1->name, kobj1->kref.refcount.refs.counter);

	return 0;
}

static void __exit cleanup(void) {
	// Reduces the reference count by 1. If it reaches 0 cleanup is done
	kobject_put(kobj);
	kobject_put(kobj1);
	printk(KERN_INFO "Goodbye!!");
}

module_init(kobjects);
module_exit(cleanup);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A deep dive into kobjects");