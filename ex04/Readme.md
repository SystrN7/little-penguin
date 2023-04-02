# Exercise 04

See source to get more information.

The big difficulty was to find how to select the usb keyboard.
I tried to use the `usbhid` module but it didn't work.
I found a solution on stackoverflow.
I had to add the usb keyboard to the virtual machine.
I found a solution on superuser.

To list the usb devices, I use the command :

`cat /proc/bus/input/devices`

Result :
```
I: Bus=0019 Vendor=0000 Product=0001 Version=0000
N: Name="Power Button"
P: Phys=LNXPWRBN/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXPWRBN:00/input/input0
U: Uniq=
H: Handlers=kbd event0
B: PROP=0
B: EV=3
B: KEY=10000000000000 0

I: Bus=0019 Vendor=0000 Product=0003 Version=0000
N: Name="Sleep Button"
P: Phys=LNXSLPBN/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSLPBN:00/input/input1
U: Uniq=
H: Handlers=kbd event1
B: PROP=0
B: EV=3
B: KEY=4000 0 0

I: Bus=0019 Vendor=0000 Product=0006 Version=0000
N: Name="Video Bus"
P: Phys=LNXVIDEO/video/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSYBUS:00/PNP0A03:00/LNXVIDEO:00/input/input2
U: Uniq=
H: Handlers=kbd event2
B: PROP=0
B: EV=3
B: KEY=3e000b00000000 0 0 0

I: Bus=0011 Vendor=0001 Product=0001 Version=ab41
N: Name="AT Translated Set 2 keyboard"
P: Phys=isa0060/serio0/input0
S: Sysfs=/devices/platform/i8042/serio0/input/input3
U: Uniq=
H: Handlers=sysrq kbd leds event3
B: PROP=0
B: EV=120013
B: KEY=402000000 3803078f800d001 feffffdfffefffff fffffffffffffffe
B: MSC=10
B: LED=7

I: Bus=0011 Vendor=0002 Product=0006 Version=0000
N: Name="ImExPS/2 Generic Explorer Mouse"
P: Phys=isa0060/serio1/input0
S: Sysfs=/devices/platform/i8042/serio1/input/input5
U: Uniq=
H: Handlers=event4
B: PROP=1
B: EV=7
B: KEY=1f0000 0 0 0 0
B: REL=143

I: Bus=0003 Vendor=1ea7 Product=0907 Version=0111
N: Name="SEMITEK USB-HID Gaming Keyboard"
P: Phys=usb-0000:00:06.0-1/input0
S: Sysfs=/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.0/0003:1EA7:0907.0006/input/input15
U: Uniq=SN0000000001
H: Handlers=sysrq kbd leds event5
B: PROP=0
B: EV=120013
B: KEY=1000000000007 ff800000000007ff febeffdfffefffff fffffffffffffffe
B: MSC=10
B: LED=7

I: Bus=0003 Vendor=1ea7 Product=0907 Version=0111
N: Name="SEMITEK USB-HID Gaming Keyboard System Control"
P: Phys=usb-0000:00:06.0-1/input2
S: Sysfs=/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2/0003:1EA7:0907.0008/input/input16
U: Uniq=SN0000000001
H: Handlers=kbd event6
B: PROP=0
B: EV=13
B: KEY=c000 10000000000000 0
B: MSC=10

I: Bus=0003 Vendor=1ea7 Product=0907 Version=0111
N: Name="SEMITEK USB-HID Gaming Keyboard Consumer Control"
P: Phys=usb-0000:00:06.0-1/input2
S: Sysfs=/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2/0003:1EA7:0907.0008/input/input17
U: Uniq=SN0000000001
H: Handlers=kbd event7
B: PROP=0
B: EV=13
B: KEY=2000000 3878d8011001 e000000000000 0
B: MSC=10

I: Bus=0003 Vendor=1ea7 Product=0907 Version=0111
N: Name="SEMITEK USB-HID Gaming Keyboard"
P: Phys=usb-0000:00:06.0-1/input2
S: Sysfs=/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2/0003:1EA7:0907.0008/input/input18
U: Uniq=SN0000000001
H: Handlers=sysrq kbd event8
B: PROP=0
B: EV=100013
B: KEY=1000000000007 ff980000000007ff febeffdfffefffff fffffffffffffffe
B: MSC=10

I: Bus=0003 Vendor=1ea7 Product=0907 Version=0111
N: Name="SEMITEK USB-HID Gaming Keyboard Mouse"
P: Phys=usb-0000:00:06.0-1/input2
S: Sysfs=/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2/0003:1EA7:0907.0008/input/input19
U: Uniq=SN0000000001
H: Handlers=event9
B: PROP=0
B: EV=17
B: KEY=ff0000 0 0 0 0
B: REL=1943
B: MSC=10
```

list devices atributes:
`udevadm info -a -p /devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2/0003:1EA7:0907.0008/input/input19`

Result
```
Udevadm info starts with the device specified by the devpath and then
walks up the chain of parent devices. It prints for every device
found, all possible attributes in the udev rules key format.
A rule to match, can be composed by the attributes of the device
and the attributes from one single parent device.

  looking at device '/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2/0003:1EA7:0907.0008/input/input19':
    KERNEL=="input19"
    SUBSYSTEM=="input"
    DRIVER==""
    ATTR{uniq}=="SN0000000001"
    ATTR{inhibited}=="0"
    ATTR{properties}=="0"
    ATTR{phys}=="usb-0000:00:06.0-1/input2"
    ATTR{name}=="SEMITEK USB-HID Gaming Keyboard Mouse"

  looking at parent device '/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2/0003:1EA7:0907.0008':
    KERNELS=="0003:1EA7:0907.0008"
    SUBSYSTEMS=="hid"
    DRIVERS=="hid-generic"
    ATTRS{country}=="00"

  looking at parent device '/devices/pci0000:00/0000:00:06.0/usb2/2-1/2-1:1.2':
    KERNELS=="2-1:1.2"
    SUBSYSTEMS=="usb"
    DRIVERS=="usbhid"
    ATTRS{bAlternateSetting}==" 0"
    ATTRS{authorized}=="1"
    ATTRS{bInterfaceSubClass}=="00"
    ATTRS{bInterfaceNumber}=="02"
    ATTRS{bInterfaceProtocol}=="00"
    ATTRS{bInterfaceClass}=="03"
    ATTRS{bNumEndpoints}=="01"
    ATTRS{supports_autosuspend}=="1"

  looking at parent device '/devices/pci0000:00/0000:00:06.0/usb2/2-1':
    KERNELS=="2-1"
    SUBSYSTEMS=="usb"
    DRIVERS=="usb"
    ATTRS{configuration}==""
    ATTRS{bMaxPacketSize0}=="64"
    ATTRS{bDeviceClass}=="00"
    ATTRS{bcdDevice}=="0300"
    ATTRS{bNumInterfaces}==" 3"
    ATTRS{bConfigurationValue}=="1"
    ATTRS{manufacturer}=="SEMITEK"
    ATTRS{bNumConfigurations}=="1"
    ATTRS{authorized}=="1"
    ATTRS{speed}=="12"
    ATTRS{idProduct}=="0907"
    ATTRS{urbnum}=="23"
    ATTRS{devnum}=="4"
    ATTRS{product}=="USB-HID Gaming Keyboard"
    ATTRS{maxchild}=="0"
    ATTRS{bmAttributes}=="80"
    ATTRS{bDeviceSubClass}=="00"
    ATTRS{bMaxPower}=="100mA"
    ATTRS{rx_lanes}=="1"
    ATTRS{removable}=="unknown"
    ATTRS{idVendor}=="1ea7"
    ATTRS{version}==" 1.10"
    ATTRS{avoid_reset_quirk}=="0"
    ATTRS{serial}=="SN0000000001"
    ATTRS{bDeviceProtocol}=="00"
    ATTRS{tx_lanes}=="1"
    ATTRS{ltm_capable}=="no"
    ATTRS{devpath}=="1"
    ATTRS{busnum}=="2"
    ATTRS{quirks}=="0x0"

  looking at parent device '/devices/pci0000:00/0000:00:06.0/usb2':
    KERNELS=="usb2"
    SUBSYSTEMS=="usb"
    DRIVERS=="usb"
    ATTRS{configuration}==""
    ATTRS{bMaxPacketSize0}=="64"
    ATTRS{bDeviceClass}=="09"
    ATTRS{bcdDevice}=="0603"
    ATTRS{bNumInterfaces}==" 1"
    ATTRS{bConfigurationValue}=="1"
    ATTRS{manufacturer}=="Linux 6.3.0-thor_kernel-g17214b70a159-dirty ohci_hcd"
    ATTRS{bNumConfigurations}=="1"
    ATTRS{authorized}=="1"
    ATTRS{speed}=="12"
    ATTRS{idProduct}=="0001"
    ATTRS{urbnum}=="139"
    ATTRS{devnum}=="1"
    ATTRS{product}=="OHCI PCI host controller"
    ATTRS{maxchild}=="12"
    ATTRS{bmAttributes}=="e0"
    ATTRS{bDeviceSubClass}=="00"
    ATTRS{bMaxPower}=="0mA"
    ATTRS{rx_lanes}=="1"
    ATTRS{removable}=="unknown"
    ATTRS{idVendor}=="1d6b"
    ATTRS{interface_authorized_default}=="1"
    ATTRS{authorized_default}=="1"
    ATTRS{version}==" 1.10"
    ATTRS{avoid_reset_quirk}=="0"
    ATTRS{serial}=="0000:00:06.0"
    ATTRS{bDeviceProtocol}=="00"
    ATTRS{tx_lanes}=="1"
    ATTRS{ltm_capable}=="no"
    ATTRS{devpath}=="0"
    ATTRS{busnum}=="2"
    ATTRS{quirks}=="0x0"

  looking at parent device '/devices/pci0000:00/0000:00:06.0':
    KERNELS=="0000:00:06.0"
    SUBSYSTEMS=="pci"
    DRIVERS=="ohci-pci"
    ATTRS{power_state}=="D0"
    ATTRS{broken_parity_status}=="0"
    ATTRS{subsystem_device}=="0x0000"
    ATTRS{dma_mask_bits}=="32"
    ATTRS{vendor}=="0x106b"
    ATTRS{local_cpus}=="1"
    ATTRS{class}=="0x0c0310"
    ATTRS{numa_node}=="-1"
    ATTRS{msi_bus}=="1"
    ATTRS{device}=="0x003f"
    ATTRS{local_cpulist}=="0"
    ATTRS{driver_override}=="(null)"
    ATTRS{d3cold_allowed}=="0"
    ATTRS{irq}=="22"
    ATTRS{revision}=="0x00"
    ATTRS{consistent_dma_mask_bits}=="32"
    ATTRS{ari_enabled}=="0"
    ATTRS{enable}=="1"
    ATTRS{subsystem_vendor}=="0x0000"

  looking at parent device '/devices/pci0000:00':
    KERNELS=="pci0000:00"
    SUBSYSTEMS==""
    DRIVERS==""
    ATTRS{waiting_for_supplier}=="0"
```

I find some information i can use to select the usb keyboard.

to create a rule file



## Sources
 - [Linux Device Drivers - 3rd Edition - Chapter 14](https://static.lwn.net/images/pdf/LDD3/ch14.pdf)
 - [Creating small usb devices drivers](https://embetronicx.com/tutorials/linux/device-drivers/usb-device-driver-example/)
 - [To find how to select the usb keyboard](https://stackoverflow.com/questions/23307579/loading-module-on-keyboard-hotplug)
 - [Install module](https://docs.kernel.org/kbuild/modules.html)
 - [Add usb keyboard to virtual machine](https://superuser.com/questions/144968/dedicated-mouse-and-keyboard-on-virtualbox-vm)
 - [USB Stuff 1](https://www.keil.com/pack/doc/mw/USB/html/_u_s_b__interface__descriptor.html)
 - [USB Stuff 2](https://www.usb.org/sites/default/files/hid1_11.pdf)