#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/debugfs.h>      /* Needed for debugfs */
#include <linux/slab.h>         /* Needed for kmalloc */
#include <linux/jiffies.h>       /* Needed for jiffies */
#include <linux/err.h>          /* Needed for ERR_PTR */
#include <linux/uaccess.h>      /* Needed for copy_form_user/copy_to_user */


#define BUFFER_SIZE PAGE_SIZE

#define STUDENT_LOGIN "fgalaup"
#define STUDENT_LOGIN_LENGTH 7


// read: user_buffer, read_length, ppos, module_buffer, module_buf_length
// write: module_buffer, module_buf_length, ppos, user_buffer, write_length
// ----------------------------
// File id

// The write buffer
char id_write_buffer[STUDENT_LOGIN_LENGTH];
uint8_t *foo_write_buffer[PAGE_SIZE];
size_t foo_write_length = 0;


static ssize_t id_write(struct file *file, const char __user *buffer,
               size_t length, loff_t *ppos)
{
    int status = 0;

    if (length != STUDENT_LOGIN_LENGTH)
    {
        pr_err("Error: Invalid value\n");
        return (-EINVAL);
    }

    if ((status = simple_write_to_buffer(id_write_buffer, STUDENT_LOGIN_LENGTH, ppos, buffer, length)) < 0)
    {
        pr_err("Error while copying from user space.\n");
        return (status);
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


char    *ft_ulltostr(unsigned long long number, char *buffer, int size)
{
    int		i;

    i = size;
    while (number)
    {
        buffer[--i] = (number % 10) + '0';
        number /= 10;
    }
    return (buffer + i);
}

static ssize_t jiffies_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    char jiffies_buffer[20] = {0};

    char *jiffies_string = ft_ulltostr(jiffies, jiffies_buffer, 20);
    return simple_read_from_buffer(buffer, count, f_pos, jiffies_string, 20 - (jiffies_string - jiffies_buffer));
}

static const struct file_operations jiffies_fops = {
    .owner = THIS_MODULE,
    .read = &jiffies_read,
};

// ----------------------------
// File foo

struct mutex foo_mutex;

static ssize_t foo_write(struct file *file, const char __user *buffer,
               size_t length, loff_t *ppos)
{
    ssize_t status = 0;
    loff_t pos = *ppos;

    mutex_lock(&foo_mutex);

    if (pos < 0)
        return (-EINVAL);
    if (pos >= PAGE_SIZE || !length)
        return (0);
    if (length > PAGE_SIZE - pos)
        length = PAGE_SIZE - pos;
    
    status = copy_from_user(
        foo_write_buffer + pos,
        buffer,
        length
    );

    if (status)
        return (-EFAULT);

    mutex_unlock(&foo_mutex);
    return status;
}

static ssize_t foo_read(struct file *filp, char __user *buffer,
                    size_t count, loff_t *f_pos)
{
    ssize_t status = 0;
    loff_t pos = *f_pos;

    mutex_lock(&foo_mutex);

    if (pos < 0)
        return (-EINVAL);
    if (pos >= PAGE_SIZE)
        return (0);
    if (count > PAGE_SIZE - pos)
        count = PAGE_SIZE - pos;

    status = copy_to_user(buffer, foo_write_buffer + pos, count);

    *f_pos += count;
    mutex_unlock(&foo_mutex);

    return status;
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
    else if (fortytwo_directory == ERR_PTR(-EEXIST))
    {
        printk(KERN_ERR "Directory already exists\n");
        return (-1);
    }
    else if (IS_ERR(fortytwo_directory))
    {
        printk(KERN_ERR "Unknown error\n");
        return (-1);
    }

    // Create a file in debugfs
    id_file = debugfs_create_file("id", 0666, fortytwo_directory, NULL, &id_fops);
    if (IS_ERR(id_file))
        goto error;
    jiffies_file = debugfs_create_file("jiffies", 0444, fortytwo_directory, NULL, &jiffies_fops);
    if (IS_ERR(jiffies_file))
        goto error;
    foo_file = debugfs_create_file("foo", 0644, fortytwo_directory, NULL, &foo_fops);
    if (IS_ERR(foo_file))
        goto error;

    mutex_init(&foo_mutex);

    memset(id_write_buffer, 0, BUFFER_SIZE * sizeof(uint8_t));
    memset(foo_write_buffer, 0, BUFFER_SIZE * sizeof(uint8_t));

    return (0);

    error:
        printk(KERN_ERR "Error creating file\n");
        debugfs_remove_recursive(fortytwo_directory);
        return (-1);
}

static void __exit module_debugfs_end(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
    // Is not strictly necessary, but it's a good practice.
    mutex_destroy(&foo_mutex);

    // But now we live in a civilized world, and we can clean up file recursively.
    debugfs_remove_recursive(fortytwo_directory);
}

module_init(module_debugfs_start);
module_exit(module_debugfs_end);

MODULE_LICENSE("GPL");
