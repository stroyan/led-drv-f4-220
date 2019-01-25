ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := leds-f4-220.o

else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

# Force cross OS build
KDIR :=/lib/modules/4.15.0-43-generic/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
endif

