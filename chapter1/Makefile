# obj-m += hello_world.o
# obj-m += module_parameters.o
# obj-m += assignment1.o
# obj-m += assignment2.o
obj-m += test.o

KDIR := /home/colonel/kernel-test-bed/linux-6.19

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean