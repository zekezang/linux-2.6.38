/*
 * mantis_sysfs.c
 *
 *  Created on: 2013-4-2
 *      Author: zekezang
 */

/* mantis model support. */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/device.h>

#include "mantis.h"

static struct class *mantis_class;
struct dentry *mantis_debugfs = NULL;

int __init mantis_sysfs_init(void) {

	MT_INFO("mantis mantis_sysfs_init.....");

	mantis_debugfs = debugfs_create_dir("mantis", NULL);

	mantis_class = class_create(THIS_MODULE, "mantis");
	if (IS_ERR(mantis_class))
		return PTR_ERR(mantis_class);

	return 0;
}

