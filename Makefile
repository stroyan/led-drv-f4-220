ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := leds-f4-220.o

else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD C=1

install:
	make -C $(KDIR) M=$$PWD modules_install

clean:
	make -C $(KDIR) M=$$PWD clean
endif

