#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/miscdevice.h>   /* Needed for misc device */
#include <linux/fs.h>       /* Needed for file operations */
#include <linux/uaccess.h>      /* Needed for copy_form_user/copy_to_user */
#include <linux/slab.h>         /* Needed for kmalloc */
#include <linux/err.h>       /* Needed for error handling */


// The write buffer
uint8_t *write_buffer;

/*
** This function will be called when we write the Misc Device file
*/
static ssize_t fortytwo_write(struct file *file, const char __user *buf,
               size_t len, loff_t *ppos)
{
    if (copy_from_user(write_buffer, buf, 128))
        pr_err("Error while copying from user space.\n");
    pr_info("fortytwo misc device write\n");
    if (memcmp(write_buffer, "fgalaup", 7))
    {
        pr_err("Error: Invalid value\n");
        return (-EINVAL);
    }   
    return len; 
}
 
/*
** This function will be called when we read the Misc Device file
*/
static ssize_t fortytwo_read(struct file *filp, char __user *buf,
                    size_t count, loff_t *f_pos)
{
    if (copy_to_user(buf, "fgalaup", 7))
        pr_err("Error while copying to user space.\n");
    pr_info("fortytwo misc device read\n");
    return 7;
}

/*
 * 
 */
static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = &fortytwo_read,
    .write = &fortytwo_write,
    .open = NULL,
    .release = NULL,
};


/*
 * The miscdevice structure is used to register a character device
 * with the kernel.
 */
struct miscdevice fortytwo_device = {
  .minor = MISC_DYNAMIC_MINOR,
  .name = "fortytwo",
  .fops = &fops,
};

static int __init module_device_mics_fortytwo_start(void)
{
    int error;

    error = misc_register(&fortytwo_device);
    if (error)
    {
        pr_err("Can't register fortytwo device\n");
        return (error);
    }

    if ((write_buffer = kmalloc(128, GFP_KERNEL)) == NULL)
    {
        pr_err("Can't allocate memory for write buffer\n");
        misc_deregister(&fortytwo_device);
        return (-ENOMEM);
    }

    printk(KERN_INFO "Module loaded\n");
    return (0);
}

static void __exit module_device_mics_fortytwo_end(void)
{
    kfree(write_buffer);
    misc_deregister(&fortytwo_device);
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(module_device_mics_fortytwo_start);
module_exit(module_device_mics_fortytwo_end);

MODULE_LICENSE("GPL");
