#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/proc_fs.h>      /* Needed for proc file system */
#include <linux/mount.h>        /* Needed for mount structure */
#include <linux/fs.h>           /* Needed for file operations */
#include <linux/mount.h>        /* Needed for mount */

#include <linux/seq_file.h>     /* Needed for seq_file */
#include <linux/fs_struct.h>    /* Needed for fs_struct */

#include <linux/namei.h>        /* Needed for kern_path */

// https://stackoverflow.com/questions/46591203/get-all-mount-points-in-kernel-module


// struct vfsmount {
// 	struct dentry *mnt_root;	/* root of the mounted tree */
// 	struct super_block *mnt_sb;	/* pointer to superblock */
// 	int mnt_flags;
// 	struct mnt_idmap *mnt_idmap;
// } __randomize_layout;


static int mount_add(struct vfsmount *mount, void *arg)
{
    struct seq_file *file = arg;
	struct path mount_path = { .dentry = mount->mnt_root, .mnt = mount };

	if (mount->mnt_sb->s_op->show_devname)
		mount->mnt_sb->s_op->show_devname(file, mount->mnt_root);
	else
		seq_printf(file, "%s", mount->mnt_sb->s_id);
	seq_putc(file, '\t');
	seq_path(file, &mount_path, " \t\n\\");
	seq_putc(file, '\n');

    return 0;
}

static int mymounts_show(struct seq_file *file, void *p)
{
    struct path root;
    struct vfsmount *mounts;
    int error;

    error = kern_path("/", 0, &root);
    if (error)
        return error;
    mounts = collect_mounts(&root);
    if (IS_ERR(mounts))
        return PTR_ERR(mounts);

    return iterate_mounts(&mount_add, file, mounts);
}

static int mymounts_open(struct inode *inode, struct file *file)
{
    return single_open(file, mymounts_show, NULL);
}

static const struct proc_ops mymounts_fops = {
    // .owner = THIS_MODULE,
    .proc_open = &mymounts_open,
    .proc_read = &seq_read,
};

static int __init module_device_mymounts_start(void)
{
    // int error;

    proc_create("mymounts", 0444, NULL, &mymounts_fops);


    printk(KERN_INFO "Module loaded\n");
    return (0);
}

static void __exit module_device_mymounts_end(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
    remove_proc_entry("mymounts", NULL);
}

module_init(module_device_mymounts_start);
module_exit(module_device_mymounts_end);

MODULE_LICENSE("GPL");