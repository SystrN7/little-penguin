#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/miscdevice.h>   /* Needed for misc device */
#include <linux/fs.h>       /* Needed for file operations */
#include <linux/uaccess.h>      /* Needed for copy_form_user/copy_to_user */
#include <linux/slab.h>         /* Needed for kmalloc */
#include <linux/err.h>       /* Needed for error handling */


#define BUFFER_SIZE 128

#define STUDENT_LOGIN "fgalaup"
#define STUDENT_LOGIN_LENGTH 7

// The write buffer
uint8_t *write_buffer;

/*
** This function will be called when we write the Misc Device file
*/
static ssize_t fortytwo_write(struct file *file, const char __user *buffer,
               size_t length, loff_t *ppos)
{
    if (length != STUDENT_LOGIN_LENGTH)
    {
        pr_err("Error: Invalid value\n");
        return (-EINVAL);
    }

    if (copy_from_user(write_buffer, buffer, STUDENT_LOGIN_LENGTH))
    {
        pr_err("Error while copying from user space.\n");
        return (-EFAULT);
    }
    pr_info("fortytwo misc device write\n");

    if (memcmp(write_buffer, STUDENT_LOGIN, STUDENT_LOGIN_LENGTH))
    {
        pr_err("Error: Invalid value\n");
        return (-EINVAL);
    }   
    return length; 
}
 
/*
** This function will be called when we read the Misc Device file
*/
static ssize_t fortytwo_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    size_t length = (count < STUDENT_LOGIN_LENGTH) ? count : STUDENT_LOGIN_LENGTH;

    if (copy_to_user(buffer, STUDENT_LOGIN, length))
    {
        pr_err("Error while copying to user space.\n");
        return (-EFAULT);
    }
    pr_info("fortytwo misc device read\n");
    return length;
}

/*
 * This structure contains the methods implemented by misc device (file /dev/fortytwo)
 */
static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = &fortytwo_read,
    .write = &fortytwo_write,
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

    if ((write_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL)) == NULL)
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
