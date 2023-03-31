#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/debugfs.h>      /* Needed for debugfs */
#include <linux/slab.h>         /* Needed for kmalloc */
#include <linux/jiffies.h>       /* Needed for jiffies */
#include <linux/err.h>          /* Needed for ERR_PTR */


#define BUFFER_SIZE 128

#define STUDENT_LOGIN "fgalaup"
#define STUDENT_LOGIN_LENGTH 7


// ----------------------------
// File id

// The write buffer
uint8_t *id_write_buffer;

static ssize_t id_write(struct file *file, const char __user *buffer,
               size_t length, loff_t *ppos)
{
    if (length != STUDENT_LOGIN_LENGTH)
    {
        pr_err("Error: Invalid value\n");
        return (-EINVAL);
    }

    if (copy_from_user(id_write_buffer, buffer, BUFFER_SIZE))
        pr_err("Error while copying from user space.\n");

    if (memcmp(id_write_buffer, STUDENT_LOGIN, STUDENT_LOGIN_LENGTH))
    {
        pr_err("Error: Invalid value\n");
        return (-EINVAL);
    }   
    return length; 
}

static ssize_t id_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    size_t length = (count < STUDENT_LOGIN_LENGTH) ? count : STUDENT_LOGIN_LENGTH;

    if (copy_to_user(buffer, STUDENT_LOGIN, length))
        pr_err("Error while copying to user space.\n");
    return length;
}

static const struct file_operations id_fops = {
    .owner = THIS_MODULE,
    .read = &id_read,
    .write = &id_write,
};


// ----------------------------
// File jiffies

static ssize_t jiffies_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    long unsigned int jiffies_value = jiffies;

    if (count < sizeof(jiffies_value))
        return -EINVAL;
        
    if (copy_to_user(buffer, &jiffies_value, sizeof(jiffies_value)))
        pr_err("Error while copying to user space.\n");
    return sizeof(jiffies);
}

static const struct file_operations jiffies_fops = {
    .owner = THIS_MODULE,
    .read = &jiffies_read,
};

// ----------------------------
// File foo

uint8_t *foo_write_buffer;
size_t foo_write_length = 0;

static ssize_t foo_write(struct file *file, const char __user *buffer,
               size_t length, loff_t *ppos)
{
    foo_write_length = (length > BUFFER_SIZE) ? BUFFER_SIZE : length;

    if (copy_from_user(foo_write_buffer, buffer, foo_write_length))
        pr_err("Error while copying from user space.\n");
    return foo_write_length; 
}

static ssize_t foo_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    if (copy_to_user(buffer, foo_write_buffer, foo_write_length))
        pr_err("Error while copying to user space.\n");
    return 7;
}

static const struct file_operations foo_fops = {
    .owner = THIS_MODULE,
    .read = &foo_read,
    .write = &foo_write,
};

struct dentry *fortytwo_directory;
struct dentry *id_file;
struct dentry *jiffies_file;
struct dentry *foo_file;

static int __init module_debugfs_start(void)
{
    printk(KERN_INFO "Module loaded\n");

    // Create a directory in debugfs
    fortytwo_directory  = debugfs_create_dir("fortytwo", NULL);

    // Error handling
    if (fortytwo_directory == ERR_PTR(-ENODEV))
    {
        printk(KERN_ERR "Debugfs feature is not enabled\n");
        return (-1);
    }
    else if (fortytwo_directory == ERR_PTR(-ENOMEM))
    {
        printk(KERN_ERR "Not enough memory to create directory\n");
        return (-1);
    }

    // Create a file in debugfs
    id_file = debugfs_create_file("id", 0666, fortytwo_directory, NULL, &id_fops);
    if (id_file == ERR_PTR(-ENOMEM))
        goto error;
    jiffies_file = debugfs_create_file("jiffies", 0444, fortytwo_directory, NULL, &jiffies_fops);
    if (jiffies_file == ERR_PTR(-ENOMEM))
        goto error;
    foo_file = debugfs_create_file("foo", 0644, fortytwo_directory, NULL, &foo_fops);
    if (foo_file == ERR_PTR(-ENOMEM))
        goto error;

    id_write_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    if (id_write_buffer == NULL)
        goto error;
    foo_write_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    if (foo_write_buffer == NULL)
    {
        kfree(id_write_buffer);
        goto error;
    }

    memset(id_write_buffer, 0, BUFFER_SIZE);
    memset(foo_write_buffer, 0, BUFFER_SIZE);

    return (0);

    error:
        printk(KERN_ERR "Error creating file\n");
        debugfs_remove_recursive(fortytwo_directory);
        return (-1);
}

static void __exit module_debugfs_end(void)
{
    printk(KERN_INFO "Cleaning up module.\n");

    // But now we live in a civilized world, and we can clean up file recursively.
    debugfs_remove_recursive(fortytwo_directory);
    kfree(id_write_buffer);
    kfree(foo_write_buffer);
}

module_init(module_debugfs_start);
module_exit(module_debugfs_end);

MODULE_LICENSE("GPL");
