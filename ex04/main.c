#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/usb.h>        /* Needed for usb */
#include <linux/hid.h>        /* Needed to select th right device class */


/*
 * usb_device_id provides a list of different types of USB devices that the driver supports
 */
static struct usb_device_id usb_id_table [] = {
        { USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
        USB_INTERFACE_SUBCLASS_BOOT,
            USB_INTERFACE_PROTOCOL_KEYBOARD) },
    { } /* Terminating entry */
};

/*
 * This enable the linux hotplug system to load the driver automatically when the device is plugged in
 */
MODULE_DEVICE_TABLE (usb, usb_id_table);


/*
** This function will be called when USB device is inserted.
*/
static int usb_keyboard_probe(struct usb_interface *interface,
                        const struct usb_device_id *id)
{
    pr_info("USB Driver is inserted\n");
    return 0;
}

/*
** This function will be called when USB device is removed.
*/
static void usb_keyboard_disconnect(struct usb_interface *interface)
{
    pr_info("USB Driver Disconnected\n");
}


static struct usb_driver usb_keyboard_driver = {
    .name       = "USB Keyboard Driver",
    .probe      = usb_keyboard_probe,
    .disconnect = usb_keyboard_disconnect,
    .id_table   = usb_id_table,
};

static int __init module_usb_keyword_start(void)
{
    printk(KERN_INFO "Init module\n");
    return usb_register(&usb_keyboard_driver);
}

static void __exit module_usb_keyword_end(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
    usb_deregister(&usb_keyboard_driver);
}

module_init(module_usb_keyword_start);
module_exit(module_usb_keyword_end);

MODULE_LICENSE("GPL");
