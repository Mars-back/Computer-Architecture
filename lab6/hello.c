// SPDX-License-Identifier: GPL-2.0-only
#include <linux/bug.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/slab.h>

static unsigned int count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Greeting count (default 1, max 10)");

struct hello_event {
	struct list_head node;
	ktime_t timestamp;
};

static LIST_HEAD(hello_events);

static void hello_free_events(void)
{
	struct hello_event *event, *tmp;

	list_for_each_entry_safe(event, tmp, &hello_events, node) {
		pr_info("hello: timestamp = %lld ns\n",
				(long long)ktime_to_ns(event->timestamp));
		list_del(&event->node);
		kfree(event);
	}
}

static int __init hello_init(void)
{
	struct hello_event *event;
	unsigned int i;

	BUG_ON(count > 10);

	if (count == 0 || count >= 5)
		pr_warn("hello: count=%u, continuing\n", count);

	for (i = 0; i < count; i++) {
		event = i == 4 ? NULL : kmalloc(sizeof(*event), GFP_KERNEL);
		if (!event && i != 4) {
			hello_free_events();
			return -ENOMEM;
		}

		event->timestamp = ktime_get();
		list_add_tail(&event->node, &hello_events);
		pr_info("Hello, world!\n");
	}

	return 0;
}

static void __exit hello_exit(void)
{
	hello_free_events();
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lab 4: memory allocation and linked lists");
