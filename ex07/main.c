#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/debugfs.h>      /* Needed for debugfs */
#include <linux/slab.h>         /* Needed for kmalloc */
#include <linux/jiffies.h>       /* Needed for jiffies */
#include <linux/err.h>          /* Needed for ERR_PTR */


#define BUFFER_SIZE PAGE_SIZE

#define STUDENT_LOGIN "fgalaup"
#define STUDENT_LOGIN_LENGTH 7


// read: user_buffer, read_length, ppos, module_buffer, module_buf_length
// write: module_buffer, module_buf_length, ppos, user_buffer, write_length
// ----------------------------
// File id

// The write buffer
char id_write_buffe[PAGE_SIZE];
uint8_t *foo_write_buffer[PAGE_SIZE];
size_t foo_write_length = 0;


static ssize_t id_write(struct file *file, const char __user *buffer,
               size_t length, loff_t *ppos)
{
    if (length != STUDENT_LOGIN_LENGTH)
    {
        pr_err("Error: Invalid value\n");
        return (-EINVAL);
    }

    if (simple_write_to_buffer(id_write_buffe, PAGE_SIZE, ppos, buffer, length))
    {
        pr_err("Error while copying from user space.\n");
        return (-EFAULT);
    }

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
   return simple_read_from_buffer(buffer, count, f_pos, STUDENT_LOGIN, STUDENT_LOGIN_LENGTH);
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

static ssize_t foo_write(struct file *file, const char __user *buffer,
               size_t length, loff_t *ppos)
{
    int status = 0;

    status = simple_write_to_buffer(foo_write_buffer, PAGE_SIZE, ppos, buffer, length);
    if (status > 0)
        foo_write_length = status;
    return status;
}

static ssize_t foo_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    return simple_read_from_buffer(buffer, count, f_pos, foo_write_buffer, foo_write_length);
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
}

module_init(module_debugfs_start);
module_exit(module_debugfs_end);

MODULE_LICENSE("GPL");
