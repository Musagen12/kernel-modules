#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/types.h> // To get the atomic_t type
#include <asm/atomic.h>

static struct task_struct *kthread1;
static struct task_struct *kthread2;
static int t1 = 1, t2 = 2;
static atomic_t i = ATOMIC_INIT(0); // This becomes an atomic variable and initializes it atomically

static int increament(void *ptr) {
	int num = *(int *)ptr;

	while(!kthread_should_stop()) {
		atomic_inc(&i);
		pr_info("Thread number %d increamented to %d.", num, atomic_read(&i));
		msleep(1000);
	}

	return 0;
}

/**
 * @briefly: The previous race condition is eliminated due to the use of an atomic variable and
 * 			 atomic operations irregardless of how closely timed the two threads are.
 **/
static int __init kthreads_init(void) {
	pr_info("playing around with kthreads.");

	kthread1 = kthread_create(increament, &t1, "superman");
	pr_info("Creating kernel thread %d.", t1);

	if(!IS_ERR(kthread1)) {
		wake_up_process(kthread1);
		pr_info("Created thread %s.", kthread1->comm);
	} else {
		pr_info("Couldn't create the thread.");
		return -ENOMEM;  // If thread can't be allocated 
	}

	kthread2 = kthread_create(increament, &t2, "batman");
	pr_info("Creating kernel thread %d.", t2);

	if(!IS_ERR(kthread2)) {
		wake_up_process(kthread2);
		pr_info("Created thread %s.", kthread2->comm);
	} else {
		pr_info("Couldn't create the thread.");
		kthread_stop(kthread1);
		return -ENOMEM;
	}

	return 0;
}

static void __exit kthreads_exit(void) {
	pr_info("Cleaning up!!!!!!");
	kthread_stop(kthread1);
	kthread_stop(kthread2);
	pr_info("Stopped the kthreads.");
}

module_init(kthreads_init);
module_exit(kthreads_exit);

MODULE_AUTHOR("Musagen12");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Using atomic variables.");