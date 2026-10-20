// SPDX-License-Identifier: GPL-2.0-only
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

#include "hello1.h"

static unsigned int count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Greeting count (default 1, max 10)");

static int __init hello2_init(void)
{
	unsigned int i;
	int ret;

	if (count > 10) {
		pr_err("hello2: count=%u exceeds 10\n", count);
		return -EINVAL;
	}

	if (count == 0 || count >= 5)
		pr_warn("hello2: count=%u, continuing\n", count);

	for (i = 0; i < count; i++) {
		ret = print_hello();
		if (ret)
			return ret;
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2: unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lab 5: greeting counter and module parameters");
