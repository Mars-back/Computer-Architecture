// SPDX-License-Identifier: GPL-2.0-only
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>

#include "hello1.h"

struct hello_event {
	struct list_head node;
	ktime_t before;
	ktime_t after;
};

static LIST_HEAD(hello_events);

int print_hello(void)
{
	struct hello_event *event;

	event = kmalloc(sizeof(*event), GFP_KERNEL);
	if (!event)
		return -ENOMEM;

	event->before = ktime_get();
	pr_info("Hello, world!\n");
	event->after = ktime_get();
	list_add_tail(&event->node, &hello_events);

	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1: loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *event, *tmp;
	s64 duration;

	list_for_each_entry_safe(event, tmp, &hello_events, node) {
		duration = ktime_to_ns(ktime_sub(event->after, event->before));
		pr_info("hello1: print duration = %lld ns\n",
			(long long)duration);
		list_del(&event->node);
		kfree(event);
	}

	pr_info("hello1: unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lab 5: exported greeting and event timing");
