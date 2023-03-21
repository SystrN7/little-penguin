# Exercice 00

Clone the Linux kernel source code from the official git repository.
`git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git`

Copy the config file from the current kernel to the new kernel source code.
`cp /boot/config-$(uname -r) .config`


Add the new kernel options to the config file.
`make oldconfig` i personally use `make menuconfig` by mistake.

Edit config file to enable the following options:
 - CONFIG_LOCALVERSION_AUTO=y

Build the kernel.
`make -j$(nproc)`

Install the kernel.
`su`
`cp -iv arch/x86/boot/bzImage /boot/vmlinuz-6.3.0-rc3-00012-g17214b70a159`
Install dubug symbols.
`cp -iv System.map /boot/System.map-6.3.0-rc3-00012-g17214b70a159`
Install the kernel config file.
`cp -iv .config /boot/config-6.3.0-rc3-00012-g17214b70a159`
Install the kernel modules.
`make modules_install`

Install docs.
```shell
install -d /usr/share/doc/linux-6.3.0-rc3
cp -r Documentation/* /usr/share/doc/linux-6.3.0-rc3
```

Update the grub config file to add the new version.
```grub.cfg
... top of the file

menuentry "GNU/Linux, Linux 6.3.0-rc3-00012-g17214b70a159" {
        linux   /vmlinuz-6.3.0-rc3-00012-g17214b70a159 root=/dev/sda3 ro
}

```

Reboot the system.
`reboot`

The kernel boot logs are available at :
 - /var/log/boot.log
 - dmesg > kernel.log

Warning: I don't update the installed kernel header on my system because i need to recompile the glibc and other packages to use the new kernel header. I prefer to use the kernel header form the previous install.



## Sources
 - [Linux KConfig docs](https://www.kernel.org/doc/html/v6.2/kbuild/kconfig.html)
 - [How to build linux kernel](https://phoenixnap.com/kb/build-linux-kernel)
 - [How to install the new kernel on lfs](http://fr.linuxfromscratch.org/view/lfs-11.2-fr/chapter10/kernel.html)
 - [Get boot logs](https://www.cyberciti.biz/faq/ubuntu-view-boot-log/)

