#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

static int __init custom_entry(void) {
	struct task_struct *task = current;

	printk(KERN_INFO "Current process: %s [%d].\n", task->comm, task->pid);
	printk(KERN_INFO "The most recently used cpu: %d.\n", task->recent_used_cpu);
	printk(KERN_INFO "The number of vmas: %d", task->mm->map_count);
	printk(KERN_INFO "Linux entry.");

	return 0;
}

static void __exit custom_exit(void) {
	printk(KERN_INFO "Exitting the kernel module.");
}

module_init(custom_entry);
module_exit(custom_exit);

MODULE_AUTHOR("Musagen12");
MODULE_DESCRIPTION("Exploring the current process");
MODULE_LICENSE("GPL");