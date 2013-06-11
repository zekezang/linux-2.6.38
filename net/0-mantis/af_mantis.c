/*
 * af_mantis.c
 *
 *  Created on: 2013-4-2
 *      Author: zekezang
 */

/* mantis address family and sockets. */

#include <linux/module.h>

#include <linux/types.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <net/sock.h>
#include <asm/ioctls.h>
#include <linux/kmod.h>

#include "mantis.h"

#define VERSION "0.01"


static int __init mantis_init(void)
{
	int err;
	MT_INFO("mantis initial.....");

	err = mantis_sysfs_init();
	if (err < 0)
		return err;

	return 0;
}

static void __exit mantis_exit(void)
{
	MT_INFO("mantis exit.....");
}

subsys_initcall(mantis_init);
module_exit(mantis_exit);

MODULE_AUTHOR("zeke zang <zekezang@mantis.org>");
MODULE_DESCRIPTION("mantis Core ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_MANTIS);
