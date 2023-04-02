#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/proc_fs.h>      /* Needed for proc file system */
#include <linux/mount.h>        /* Needed for mount structure */
#include <linux/fs.h>       /* Needed for file operations */
#include <linux/uaccess.h>      /* Needed for copy_form_user/copy_to_user */
#include <linux/slab.h>         /* Needed for kmalloc */
#include <linux/list.h>         /* Needed for list_for_each_entry */
#include <linux/string.h>       /* Needed for strcat */
#include <linux/sched.h>        /* Needed for current */
#include <linux/nsproxy.h>      /* Needed for nsproxy */
#include <linux/mount.h>        /* Needed for mount */
// #include <linux/dcache.h>       /* Needed for dentry */



// #define BUFFER_SIZE 1024

// Return the list of mounted filesystems
static ssize_t mymounts_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    struct mnt_namespace *ns = current->nsproxy->mnt_ns;
    struct mount *mnt;

    char *buf;
    int len = 0;

    list_for_each_entry(mnt, &ns->list, mnt_list) {
        len += strlen(mnt->mnt_mountpoint->d_name.name) + 1;
    }

    buf = kmalloc(len, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;
    
    list_for_each_entry(mnt, &ns->list, mnt_list) {

        strcat(buf, mnt->mnt_mountpoint->d_name.name);
        strcat(buf, " ");
    }



    return 0;
}

static const struct proc_ops mymounts_fops = {
    // .owner = THIS_MODULE,
    .proc_read = &mymounts_read,
};

static int __init module_device_mymounts_start(void)
{
    // int error;

    proc_create("mymounts", 0444, NULL, &mymounts_fops);
    // if (error)
    // {
    //     pr_err("Can't register mymounts device\n");
    //     return (error);
    // }

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
