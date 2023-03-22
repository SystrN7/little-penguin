#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */

static int __init module_hello_start(void)
{
    printk(KERN_INFO "Hello world !\n");
    return (0);
}

static void __exit module_hello_end(void)
{}

module_init(hello_start);
module_exit(hello_end);