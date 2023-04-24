// SPDX-License-Identifier: GPL
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kprobes.h>
#include <linux/module.h>
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

typedef int (*iterate_mounts_t)(int (*)(struct vfsmount *, void *), void *, struct vfsmount *);
typedef struct vfsmount *(*collect_mounts_t)(const struct path *);

static void *mymounts_lookup_symbol(const char *name)
{
	struct kprobe kp = {
		.symbol_name = name,
	};
	void *addr;

	if (register_kprobe(&kp) < 0)
		return NULL;

	addr = kp.addr;
	unregister_kprobe(&kp);
	return addr;
}

static int mymounts_show_single(struct vfsmount *mnt, void *ptr)
{
	struct seq_file *seqf = ptr;
	struct path mnt_path = {
		.dentry = mnt->mnt_root, .mnt = mnt
	};

	if (mnt->mnt_sb->s_op->show_devname)
		mnt->mnt_sb->s_op->show_devname(seqf, mnt->mnt_root);
	else
		seq_puts(seqf, mnt->mnt_sb->s_id);

	seq_putc(seqf, '\t');
	seq_path(seqf, &mnt_path, " \t\n\\");
	seq_putc(seqf, '\n');
	return 0;
}

static int mymounts_show(struct seq_file *seqf, void *unused_ptr)
{
	int err;
	struct path path;
	struct vfsmount *mnt;
	iterate_mounts_t iter_mounts_fn;
	collect_mounts_t coll_mounts_fn;

	(void)unused_ptr;
	iter_mounts_fn = (iterate_mounts_t)mymounts_lookup_symbol("iterate_mounts");
	coll_mounts_fn = (collect_mounts_t)mymounts_lookup_symbol("collect_mounts");

	if (iter_mounts_fn == NULL || coll_mounts_fn == NULL)
		return -1;

	err = kern_path("/", 0, &path);
	if (err)
		return err;

	mnt = coll_mounts_fn(&path);
	if (IS_ERR(mnt))
		return PTR_ERR(mnt);
	return iter_mounts_fn(mymounts_show_single, seqf, mnt);
}

static int mymounts_open(struct inode *inode, struct file *file)
{
	return single_open(file, mymounts_show, NULL);
}

const struct proc_ops mymounts_ops = {
	.proc_open = mymounts_open,
	.proc_read = seq_read,
};

static struct proc_dir_entry *mymounts_entry;

int ex09_init(void)
{
	pr_info("Hello, World!\n");
	mymounts_entry = proc_create("mymounts", 0444, NULL, &mymounts_ops);
	if (IS_ERR(mymounts_entry))
		return PTR_ERR(mymounts_entry);
	return 0;
}

void ex09_exit(void)
{
	pr_info("Cleaning up module.\n");
	proc_remove(mymounts_entry);
}

module_init(ex09_init);
module_exit(ex09_exit);

MODULE_LICENSE("GPL");