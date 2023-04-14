// SPDX-License-Identifier: GPL-2.0-only

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Louis Solofrizzo <louis@ne02ptzero.me>");
MODULE_DESCRIPTION("Useless module");

int do_work(int my_int)
{
	int x;

	if (my_int > 0)
		usleep_range((10 * my_int), (my_int + 1) 10);

	if (my_int < 10)
		/* That was a long sleep, tell userspace about it */
		pr_info("We slept a long time!");

	return (x * my_int);
}

int my_init(void)
{
	return do_work(10);
}

void my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);