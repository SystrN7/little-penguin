# Exercise 06

The linux-next is a git repository that contains the latest version of the Linux kernel. It is used by the Linux kernel developers to test new features and bug fixes before they are merged into the mainline kernel. The linux-next repository is updated daily and contains the latest version of the Linux kernel.

To build and install the linux-next kernel you can follow instruction of [ex00](../ex00/Readme.md).

Add the new kernel options to the grub config file. (This version can be instable)
```
menuentry "GNU/Linux, Linux 6.3.0-rc4-next-20230328" {
        linux   /vmlinuz-6.3.0-rc4-next-20230328 root=/dev/sda3 ro
}
```

## Sources
 - [Linux-next](https://www.kernel.org/doc/man-pages/linux-next.html)
 - [linux-next git repository](https://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git)
 - [Linux development process](https://www.kernel.org/doc/html/latest/process/development-process.html)