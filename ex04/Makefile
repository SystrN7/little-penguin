NAME = main

obj-m = $(NAME).o

ifeq ($(KVERSION),)
	KVERSION = $(shell uname -r)
endif

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

modules_install:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules_install

modules_uninstall:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules_uninstall

load:
	insmod $(NAME).ko
	dmesg | tail -1

unload:
	rmmod $(NAME).ko
	dmesg | tail -1