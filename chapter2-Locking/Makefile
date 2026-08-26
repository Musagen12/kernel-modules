# obj-m += kthreads.o
# obj-m += race_condition.o
# obj-m += atomic_variables.o
# obj-m += spinlocks.o
# obj-m += semaphores.o
# obj-m += rw_semaphores.o
obj-m += mutex.o

KDIR := /home/colonel/kernel-test-bed/linux-6.19

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean