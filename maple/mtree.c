#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/maple_tree.h>
#include <linux/rcupdate.h>

struct maple_tree *tree;

static int __init create_tree(void) {
	printk(KERN_INFO "Hello kernel.");

	// Allocating the memory
	tree = kmalloc(sizeof(tree), GFP_NOWAIT);

	// Always check if memory allocation failed otherwise you will run into a NULL pointer
	// dereference since you will be accessing memory(ie using a pointer) that doesn't exist
	// When this happens the OS crashes
	if (!tree) {
		printk(KERN_ALERT "Memory allocation failed");
		return -ENOMEM;
	}

	// Initialize the maple tree using previously allocated memory
	mt_init(tree);
	// The tree is in RCU mode hence we need to dereference it carefully
	void * root = rcu_dereference(tree->ma_root);

	printk(KERN_INFO "The root pointer address is %p.", &root);
	printk(KERN_INFO "The root pointer is %p.", root);

	return 0;
}

static void __exit cleanup(void) {
	printk(KERN_INFO "Freeing used memory.");
	kfree(tree);
	printk(KERN_INFO "Goodbye kernel.");
}

module_init(create_tree);
module_exit(cleanup);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module that creates and manipulates a maple tree");