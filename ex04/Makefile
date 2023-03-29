obj-m = main.o
KVERSION = $(shell uname -r)

all:
	make -C /lib/modules/5.15.0-67-generic/build M=$(PWD) modules
clean:
	make -C /lib/modules/5.15.0-67-generic/build M=$(PWD) clean


install:
	insmod main.ko
	dmesg | tail -1

uninstall:
	rmmod main.ko
	dmesg | tail -1