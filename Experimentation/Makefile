# obj-m += driver.o
obj-m += current.o

KDIR := /home/colonel/kernel-test-bed/linux-6.19

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean