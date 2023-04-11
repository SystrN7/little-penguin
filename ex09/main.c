#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/proc_fs.h>      /* Needed for proc file system */
#include <linux/nsproxy.h>      /* Needed for nsproxy */
#include <linux/mnt_namespace.h>
#include <linux/security.h>
#include <linux/fs_struct.h>
#include <linux/sched/task.h>
#include <linux/mount.h>

#include <linux/seq_file.h>

// #include <linux/proc_fs.h>
// #include <linux/fs_struct.h>

static int show_vfsmnt(struct seq_file *m, struct vfsmount *mnt)
{
	struct proc_mounts *p = m->private;
	struct mount *r = real_mount(mnt);
	struct path mnt_path = { .dentry = mnt->mnt_root, .mnt = mnt };
	struct super_block *sb = mnt_path.dentry->d_sb;
	int err;

	if (sb->s_op->show_devname) {
		err = sb->s_op->show_devname(m, mnt_path.dentry);
		if (err)
			goto out;
	} else {
		mangle(m, r->mnt_devname ? r->mnt_devname : "none");
	}
	seq_putc(m, ' ');
	/* mountpoints outside of chroot jail will give SEQ_SKIP on this */
	err = seq_path_root(m, &mnt_path, &p->root, " \t\n\\");
	if (err)
		goto out;
	seq_putc(m, ' ');
	show_type(m, sb);
	seq_puts(m, __mnt_is_readonly(mnt) ? " ro" : " rw");
	err = show_sb_opts(m, sb);
	if (err)
		goto out;
	show_mnt_opts(m, mnt);
	if (sb->s_op->show_options)
		err = sb->s_op->show_options(m, mnt_path.dentry);
	seq_puts(m, " 0 0\n");
out:
	return err;
}

static int mounts_open_common(struct inode *inode, struct file *file,
			      int (*show)(struct seq_file *, struct vfsmount *))
{
	struct task_struct *task = get_proc_task(inode);
	struct nsproxy *nsp;
	struct mnt_namespace *ns = NULL;
	struct path root;
	struct proc_mounts *p;
	struct seq_file *m;
	int ret = -EINVAL;

	if (!task)
		goto err;

	task_lock(task);
	nsp = task->nsproxy;
	if (!nsp || !nsp->mnt_ns) {
		task_unlock(task);
		put_task_struct(task);
		goto err;
	}
	ns = nsp->mnt_ns;
	get_mnt_ns(ns);
	if (!task->fs) {
		task_unlock(task);
		put_task_struct(task);
		ret = -ENOENT;
		goto err_put_ns;
	}
	get_fs_root(task->fs, &root);
	task_unlock(task);
	put_task_struct(task);

	ret = seq_open_private(file, &mounts_op, sizeof(struct proc_mounts));
	if (ret)
		goto err_put_path;

	m = file->private_data;
	m->poll_event = ns->event;

	p = m->private;
	p->ns = ns;
	p->root = root;
	p->show = show;
	INIT_LIST_HEAD(&p->cursor.mnt_list);
	p->cursor.mnt.mnt_flags = MNT_CURSOR;

	return 0;

 err_put_path:
	path_put(&root);
 err_put_ns:
	put_mnt_ns(ns);
 err:
	return ret;
}

static int mounts_release(struct inode *inode, struct file *file)
{
	struct seq_file *m = file->private_data;
	struct proc_mounts *p = m->private;
	path_put(&p->root);
	mnt_cursor_del(p->ns, &p->cursor);
	put_mnt_ns(p->ns);
	return seq_release_private(inode, file);
}

static int mounts_open(struct inode *inode, struct file *file)
{
	return mounts_open_common(inode, file, show_vfsmnt);
}

static __poll_t mounts_poll(struct file *file, poll_table *wait)
{
	struct seq_file *m = file->private_data;
	struct proc_mounts *p = m->private;
	struct mnt_namespace *ns = p->ns;
	__poll_t res = EPOLLIN | EPOLLRDNORM;
	int event;

	poll_wait(file, &p->ns->poll, wait);

	event = READ_ONCE(ns->event);
	if (m->poll_event != event) {
		m->poll_event = event;
		res |= EPOLLERR | EPOLLPRI;
	}

	return res;
}

const struct file_operations proc_mounts_operations = {
	.open		= mounts_open,
	.read_iter	= seq_read_iter,
	.splice_read	= generic_file_splice_read,
	.llseek		= seq_lseek,
	.release	= mounts_release,
	// .poll		= mounts_poll,
};

static int __init module_device_mymounts_start(void)
{
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
