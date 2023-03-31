#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/miscdevice.h>   /* Needed for misc device */
#include <linux/fs.h>       /* Needed for file operations */
#include <linux/uaccess.h>      /* Needed for copy_form_user/copy_to_user */
#include <linux/slab.h>         /* Needed for kmalloc */
#include <linux/err.h>       /* Needed for error handling */


static ssize_t mymounts_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    struct mnt_namespace *ns = current->nsproxy->mnt_ns;
    struct mount *mnt;

    list_for_each_entry(mnt, &ns->list, mnt_list) {
        printk(KERN_INFO "Mount point: %s\n", mnt->mnt_mountpoint->d_name.name);
    }
}

static const struct file_operations mymounts_fops = {
    .owner = THIS_MODULE,
    .read = &mymounts_read,
};

static int __init module_device_mymounts_start(void)
{
    int error;

    error = proc_create("mymounts", 0444, NULL, &mymounts_fops);
    if (error)
    {
        pr_err("Can't register mymounts device\n");
        return (error);
    }

    // if ((write_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL)) == NULL)
    // {
    //     pr_err("Can't allocate memory for write buffer\n");
    //     misc_deregister(&mymounts_device);
    //     return (-ENOMEM);
    // }

    printk(KERN_INFO "Module loaded\n");
    return (0);
}

static void __exit module_device_mymounts_end(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
    // kfree(write_buffer);
    remove_proc_entry("mymounts", NULL);
}

module_init(module_device_mymounts_start);
module_exit(module_device_mymounts_end);

MODULE_LICENSE("GPL");
