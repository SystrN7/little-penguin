# Exercise 1

Build the module.
`make`

Install the module.
```shell
su
insmod main.ko
```

Print the last line of kernel log.
`dmesg | tail -1`

Remove the module.
```shell
su
rmmod main.ko
```

Print the last line of kernel log.
`dmesg | tail -1`


## Sources
 - [Create hello word kernel](https://www.cyberciti.biz/tips/compiling-linux-kernel-module.html)