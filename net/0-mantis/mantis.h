/*
 * mantis.h
 *
 *  Created on: 2013-4-2
 *      Author: zekezang
 */

#ifndef MANTIS_H_
#define MANTIS_H_

#define MT_INFO(fmt, arg...) printk(KERN_INFO "Mantis: " fmt "\n" , ## arg)
#define MT_ERR(fmt, arg...)  printk(KERN_ERR "%s: " fmt "\n" , __func__ , ## arg)
#define MT_DBG(fmt, arg...)  pr_debug("%s: " fmt "\n" , __func__ , ## arg)


int __init mantis_sysfs_init(void);


#endif /* MANTIS_H_ */
