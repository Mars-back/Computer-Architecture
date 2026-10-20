ifneq ($(KERNELRELEASE),)
obj-m := hello.o
ccflags-y += -g
else
KDIR ?= $(HOME)/repos/linux-stable

all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) modules
	cp hello.ko hello.ko.unstripped
	$(CROSS_COMPILE)strip -g hello.ko

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) clean
	rm -f hello.ko.unstripped
endif
