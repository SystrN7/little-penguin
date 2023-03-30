// SPDX-License-Identifier: GPL-2.0-only
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>

MODULE_LICENSE("GNU");
MODULE_AUTHOR("Louis Solofrizzo <louis@ne02ptzero.me>");
MODULE_DESCRIPTION("Useless module");

char reverse_string[PAGE_SIZE];
char string[PAGE_SIZE];

ssize_t myfd_read(struct file *fp, char __user *user, size_t size, loff_t *offs)
{
	size_t string_length;
	ssize_t t, i;

	string_length = strlen(string);

	// Reverse string
	for (t = string_length - 1, i = 0; t >= 0; t--, i++)
		reverse_string[i] = string[t];

	reverse_string[i] = '\0';

	return simple_read_from_buffer(user, size, offs, reverse_string, i);
}

ssize_t myfd_write(struct file *fp, const char __user *user, size_t size,
		   loff_t *offs)
{
	ssize_t result;

	if (size + 1 > PAGE_SIZE) {
		pr_err("String too long");
		return -EINVAL;
	}

	result = simple_write_to_buffer(string, size, offs, user, size);
	string[size] = '\0';

	return result + 1;
}

static struct file_operations myfd_fops = { .owner = THIS_MODULE,
					    .read = &myfd_read,
					    .write = &myfd_write };

static struct miscdevice myfd_device = { .minor = MISC_DYNAMIC_MINOR,
					 .name = "reverse",
					 .fops = &myfd_fops };

static int __init myfd_init(void)
{
	return misc_register(&myfd_device);
}

static void __exit myfd_cleanup(void)
{
	misc_deregister(&myfd_device);
}

module_init(myfd_init);
module_exit(myfd_cleanup);