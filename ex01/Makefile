NAME = main

obj-m = $(NAME).o

ifeq ($(KVERSION),)
	KVERSION = $(shell uname -r)
endif

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

load:
	insmod $(NAME).ko
	dmesg | tail -1

unload:
	rmmod $(NAME).ko
	dmesg | tail -1