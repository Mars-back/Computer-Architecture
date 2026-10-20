ifneq ($(KERNELRELEASE),)
obj-m := hello1.o hello2.o
ccflags-y += -I$(src)/inc
else
KDIR ?= $(HOME)/repos/linux-stable

all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) modules

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) clean
endif
