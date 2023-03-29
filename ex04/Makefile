obj-m = main.o
KVERSION = $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

modules_install:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules_install

modules_uninstall:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules_uninstall

load:
	insmod main.ko
	dmesg | tail -1

unload:
	rmmod main.ko
	dmesg | tail -1