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
P: Phys=PNP0C0C/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSYBUS:00/PNP0C0C:00/input/input0
U: Uniq=
H: Handlers=kbd event0 
B: PROP=0
B: EV=3
B: KEY=10000000000000 0

I: Bus=0019 Vendor=0000 Product=0003 Version=0000
N: Name="Sleep Button"
P: Phys=PNP0C0E/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSYBUS:00/PNP0C0E:00/input/input1
U: Uniq=
H: Handlers=kbd event1 
B: PROP=0
B: EV=3
B: KEY=4000 0 0

I: Bus=0019 Vendor=0000 Product=0001 Version=0000
N: Name="Power Button"
P: Phys=LNXPWRBN/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXPWRBN:00/input/input2
U: Uniq=
H: Handlers=kbd event2 
B: PROP=0
B: EV=3
B: KEY=10000000000000 0

I: Bus=0019 Vendor=0000 Product=0006 Version=0000
N: Name="Video Bus"
P: Phys=LNXVIDEO/video/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSYBUS:00/PNP0A08:00/device:01/LNXVIDEO:00/input/input3
U: Uniq=
H: Handlers=kbd event3 
B: PROP=0
B: EV=3
B: KEY=3e000b00000000 0 0 0

I: Bus=0003 Vendor=046a Product=0180 Version=0111
N: Name="  wired keyboard"
P: Phys=usb-0000:00:14.0-2/input0
S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.0/0003:046A:0180.0001/input/input4
U: Uniq=
H: Handlers=sysrq kbd event4 leds 
B: PROP=0
B: EV=120013
B: KEY=1000000000007 ff9f207ac14057ff febeffdfffefffff fffffffffffffffe
B: MSC=10
B: LED=7

I: Bus=0003 Vendor=046a Product=0180 Version=0111
N: Name="  wired keyboard Consumer Control"
P: Phys=usb-0000:00:14.0-2/input1
S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1/0003:046A:0180.0002/input/input5
U: Uniq=
H: Handlers=kbd event5 
B: PROP=0
B: EV=1f
B: KEY=3f000307ff 0 0 483ffff17aff32d bfd4444600000000 1 130ff38b17d000 677bfad9415fed 19ed68000004400 10000002
B: REL=1040
B: ABS=100000000
B: MSC=10

I: Bus=0003 Vendor=046a Product=0180 Version=0111
N: Name="  wired keyboard System Control"
P: Phys=usb-0000:00:14.0-2/input1
S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1/0003:046A:0180.0002/input/input6
U: Uniq=
H: Handlers=kbd event6 
B: PROP=0
B: EV=13
B: KEY=c000 10000000000000 0
B: MSC=10

I: Bus=0003 Vendor=093a Product=2510 Version=0111
N: Name="PixArt USB Optical Mouse"
P: Phys=usb-0000:00:14.0-4/input0
S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-4/1-4:1.0/0003:093A:2510.0003/input/input7
U: Uniq=
H: Handlers=mouse0 event7 
B: PROP=0
B: EV=17
B: KEY=70000 0 0 0 0
B: REL=903
B: MSC=10

I: Bus=0003 Vendor=05ac Product=8296 Version=0111
N: Name="Broadcom Corp. Bluetooth USB Host Controller"
P: Phys=usb-0000:00:14.0-6/input0
S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-6/1-6:1.0/0003:05AC:8296.0004/input/input8
U: Uniq=
H: Handlers=sysrq kbd event8 leds 
B: PROP=0
B: EV=120013
B: KEY=1000000000007 ff800000000007ff febeffdff3cfffff fffffffffffffffe
B: MSC=10
B: LED=7

I: Bus=0003 Vendor=05ac Product=8296 Version=0111
N: Name="Broadcom Corp. Bluetooth USB Host Controller"
P: Phys=usb-0000:00:14.0-6/input1
S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-6/1-6:1.1/0003:05AC:8296.0005/input/input9
U: Uniq=
H: Handlers=mouse1 event9 
B: PROP=0
B: EV=17
B: KEY=70000 0 0 0 0
B: REL=3
B: MSC=10

I: Bus=0000 Vendor=0000 Product=0000 Version=0000
N: Name="HDA ATI HDMI HDMI/DP,pcm=3"
P: Phys=ALSA
S: Sysfs=/devices/pci0000:00/0000:00:01.0/0000:01:00.1/sound/card1/input10
U: Uniq=
H: Handlers=event10 
B: PROP=0
B: EV=21
B: SW=140

I: Bus=0000 Vendor=0000 Product=0000 Version=0000
N: Name="HDA ATI HDMI HDMI/DP,pcm=7"
P: Phys=ALSA
S: Sysfs=/devices/pci0000:00/0000:00:01.0/0000:01:00.1/sound/card1/input11
U: Uniq=
H: Handlers=event11 
B: PROP=0
B: EV=21
B: SW=140

I: Bus=0000 Vendor=0000 Product=0000 Version=0000
N: Name="HDA ATI HDMI HDMI/DP,pcm=8"
P: Phys=ALSA
S: Sysfs=/devices/pci0000:00/0000:00:01.0/0000:01:00.1/sound/card1/input12
U: Uniq=
H: Handlers=event12 
B: PROP=0
B: EV=21
B: SW=140

I: Bus=0000 Vendor=0000 Product=0000 Version=0000
N: Name="HDA ATI HDMI HDMI/DP,pcm=9"
P: Phys=ALSA
S: Sysfs=/devices/pci0000:00/0000:00:01.0/0000:01:00.1/sound/card1/input13
U: Uniq=
H: Handlers=event13 
B: PROP=0
B: EV=21
B: SW=140

I: Bus=0000 Vendor=0000 Product=0000 Version=0000
N: Name="HDA ATI HDMI HDMI/DP,pcm=10"
P: Phys=ALSA
S: Sysfs=/devices/pci0000:00/0000:00:01.0/0000:01:00.1/sound/card1/input14
U: Uniq=
H: Handlers=event14 
B: PROP=0
B: EV=21
B: SW=140

I: Bus=0000 Vendor=0000 Product=0000 Version=0000
N: Name="HDA ATI HDMI HDMI/DP,pcm=11"
P: Phys=ALSA
S: Sysfs=/devices/pci0000:00/0000:00:01.0/0000:01:00.1/sound/card1/input15
U: Uniq=
H: Handlers=event15 
B: PROP=0
B: EV=21
B: SW=140

I: Bus=0000 Vendor=0000 Product=0000 Version=0000
N: Name="HDA ATI HDMI HDMI/DP,pcm=12"
P: Phys=ALSA
S: Sysfs=/devices/pci0000:00/0000:00:01.0/0000:01:00.1/sound/card1/input16
U: Uniq=
H: Handlers=event16 
B: PROP=0
B: EV=21
B: SW=140

I: Bus=0003 Vendor=05ac Product=8511 Version=7252
N: Name="FaceTime HD Camera (Built-in): "
P: Phys=usb-0000:00:14.0-5/button
S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-5/1-5:1.0/input/input17
U: Uniq=
H: Handlers=kbd event17 
B: PROP=0
B: EV=3
B: KEY=100000 0 0 0
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

  looking at device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.0/0003:046A:0180.0001/input/input4':
    KERNEL=="input4"
    SUBSYSTEM=="input"
    DRIVER==""
    ATTR{uniq}==""
    ATTR{properties}=="0"
    ATTR{name}=="  wired keyboard"
    ATTR{phys}=="usb-0000:00:14.0-2/input0"

  looking at parent device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.0/0003:046A:0180.0001':
    KERNELS=="0003:046A:0180.0001"
    SUBSYSTEMS=="hid"
    DRIVERS=="hid-generic"
    ATTRS{country}=="00"

  looking at parent device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.0':
    KERNELS=="1-2:1.0"
    SUBSYSTEMS=="usb"
    DRIVERS=="usbhid"
    ATTRS{bNumEndpoints}=="01"
    ATTRS{authorized}=="1"
    ATTRS{bInterfaceClass}=="03"
    ATTRS{supports_autosuspend}=="1"
    ATTRS{bAlternateSetting}==" 0"
    ATTRS{bInterfaceProtocol}=="01"
    ATTRS{bInterfaceNumber}=="00"
    ATTRS{bInterfaceSubClass}=="01"

  looking at parent device '/devices/pci0000:00/0000:00:14.0/usb1/1-2':
    KERNELS=="1-2"
    SUBSYSTEMS=="usb"
    DRIVERS=="usb"
    ATTRS{devpath}=="2"
    ATTRS{devnum}=="2"
    ATTRS{bConfigurationValue}=="1"
    ATTRS{bMaxPacketSize0}=="8"
    ATTRS{idVendor}=="046a"
    ATTRS{bNumConfigurations}=="1"
    ATTRS{bmAttributes}=="a0"
    ATTRS{rx_lanes}=="1"
    ATTRS{authorized}=="1"
    ATTRS{idProduct}=="0180"
    ATTRS{speed}=="1.5"
    ATTRS{bDeviceProtocol}=="00"
    ATTRS{avoid_reset_quirk}=="0"
    ATTRS{configuration}==""
    ATTRS{product}=="wired keyboard"
    ATTRS{quirks}=="0x0"
    ATTRS{version}==" 2.00"
    ATTRS{manufacturer}==" "
    ATTRS{bDeviceClass}=="00"
    ATTRS{maxchild}=="0"
    ATTRS{ltm_capable}=="no"
    ATTRS{tx_lanes}=="1"
    ATTRS{bcdDevice}=="0103"
    ATTRS{removable}=="removable"
    ATTRS{busnum}=="1"
    ATTRS{bNumInterfaces}==" 2"
    ATTRS{bMaxPower}=="100mA"
    ATTRS{bDeviceSubClass}=="00"
    ATTRS{urbnum}=="965"

  looking at parent device '/devices/pci0000:00/0000:00:14.0/usb1':
    KERNELS=="usb1"
    SUBSYSTEMS=="usb"
    DRIVERS=="usb"
    ATTRS{idProduct}=="0002"
    ATTRS{quirks}=="0x0"
    ATTRS{ltm_capable}=="no"
    ATTRS{bConfigurationValue}=="1"
    ATTRS{bcdDevice}=="0504"
    ATTRS{configuration}==""
    ATTRS{maxchild}=="16"
    ATTRS{bMaxPacketSize0}=="64"
    ATTRS{bDeviceSubClass}=="00"
    ATTRS{version}==" 2.00"
    ATTRS{bDeviceClass}=="09"
    ATTRS{manufacturer}=="Linux 5.4.0-146-generic xhci-hcd"
    ATTRS{authorized}=="1"
    ATTRS{urbnum}=="132"
    ATTRS{tx_lanes}=="1"
    ATTRS{busnum}=="1"
    ATTRS{rx_lanes}=="1"
    ATTRS{idVendor}=="1d6b"
    ATTRS{serial}=="0000:00:14.0"
    ATTRS{authorized_default}=="1"
    ATTRS{avoid_reset_quirk}=="0"
    ATTRS{bmAttributes}=="e0"
    ATTRS{product}=="xHCI Host Controller"
    ATTRS{devnum}=="1"
    ATTRS{bNumConfigurations}=="1"
    ATTRS{devpath}=="0"
    ATTRS{speed}=="480"
    ATTRS{interface_authorized_default}=="1"
    ATTRS{removable}=="unknown"
    ATTRS{bMaxPower}=="0mA"
    ATTRS{bDeviceProtocol}=="01"
    ATTRS{bNumInterfaces}==" 1"

  looking at parent device '/devices/pci0000:00/0000:00:14.0':
    KERNELS=="0000:00:14.0"
    SUBSYSTEMS=="pci"
    DRIVERS=="xhci_hcd"
    ATTRS{subsystem_device}=="0x7270"
    ATTRS{class}=="0x0c0330"
    ATTRS{local_cpus}=="f"
    ATTRS{msi_bus}=="1"
    ATTRS{local_cpulist}=="0-3"
    ATTRS{consistent_dma_mask_bits}=="64"
    ATTRS{numa_node}=="-1"
    ATTRS{vendor}=="0x8086"
    ATTRS{irq}=="36"
    ATTRS{subsystem_vendor}=="0x8086"
    ATTRS{broken_parity_status}=="0"
    ATTRS{d3cold_allowed}=="1"
    ATTRS{ari_enabled}=="0"
    ATTRS{dma_mask_bits}=="64"
    ATTRS{revision}=="0x31"
    ATTRS{enable}=="1"
    ATTRS{device}=="0xa12f"
    ATTRS{driver_override}=="(null)"
    ATTRS{dbc}=="disabled"

  looking at parent device '/devices/pci0000:00':
    KERNELS=="pci0000:00"
    SUBSYSTEMS==""
    DRIVERS==""
```

I find some information i can use to select the usb keyboard.

to create a rule file



## Sources
 - [Linux Device Drivers - 3rd Edition - Chapter 14](https://static.lwn.net/images/pdf/LDD3/ch14.pdf)
 - [Creating small usb devices drivers](https://embetronicx.com/tutorials/linux/device-drivers/usb-device-driver-example/)
 - [To find how to select the usb keyboard](https://stackoverflow.com/questions/23307579/loading-module-on-keyboard-hotplug)
 - [Install module](https://docs.kernel.org/kbuild/modules.html)
 - [Udev introduction (French)](https://www.linuxembedded.fr/2015/05/une-introduction-a-udev)
 - [Add usb keyboard to virtual machine](https://superuser.com/questions/144968/dedicated-mouse-and-keyboard-on-virtualbox-vm)
 - [USB Stuff 1](https://www.keil.com/pack/doc/mw/USB/html/_u_s_b__interface__descriptor.html)
 - [USB Stuff 2](https://www.usb.org/sites/default/files/hid1_11.pdf)