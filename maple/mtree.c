#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/maple_tree.h>
#include <linux/rcupdate.h>

struct maple_tree *tree;

static int __init create_tree(void) {
	int err;
	int entry = 567886761;

	printk(KERN_INFO "Welcome to maple tree hacking.");

	// Allocating the memory
	// Used the sizeof a maple tree struct not the pointer
	tree = kmalloc(sizeof(struct maple_tree), GFP_NOWAIT);

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

	err = mtree_insert_range(tree, 0, 0, &entry, GFP_NOWAIT);

	if (err){
		printk(KERN_ALERT "An error %d occured.", err);
		return -1;
	}

	printk(KERN_INFO "Stored an entry %d.", entry);

	void * post_root = rcu_dereference(tree->ma_root);

	// After storing an entry
	printk(KERN_INFO "The root pointer address is %p.", &post_root);
	printk(KERN_INFO "The root pointer is %p.", post_root);

	return 0;
}

static void __exit cleanup(void) {
	printk(KERN_INFO "Freeing used memory.");
	// You need to free any allocated memory to avoid
	kfree(tree);
	printk(KERN_INFO "Goodbye kernel.");
}

module_init(create_tree);
module_exit(cleanup);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module that creates and manipulates a maple tree");