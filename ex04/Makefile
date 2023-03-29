obj-m = main.o
KVERSION = $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean


install:
	insmod main.ko
	dmesg | tail -1

uninstall:
	rmmod main.ko
	dmesg | tail -1