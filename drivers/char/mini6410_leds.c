#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/irq.h>
//#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>

#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>

#include <plat/gpio-cfg.h>
#include <mach/gpio-bank-e.h>
#include <mach/gpio-bank-k.h>

#define DEVICE_NAME "leds"

static long sbc2440_leds_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	switch (cmd) {
	unsigned tmp;
case 0:
case 1:
	if (arg > 4) {
		return -EINVAL;
	}
	tmp = readl(S3C64XX_GPKDAT);
	tmp &= ~(1 << (4 + arg));
	tmp |= ((!cmd) << (4 + arg));
	writel(tmp, S3C64XX_GPKDAT);
	//printk (DEVICE_NAME": %d %d\n", arg, cmd);
	return 0;
default:
	return -EINVAL;
	}
}

static struct file_operations dev_fops = {
		.owner = THIS_MODULE,
		.unlocked_ioctl = sbc2440_leds_ioctl, };

static struct miscdevice misc = {
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &dev_fops, };

#include <linux/ioport.h>
#include <linux/timer.h>

static struct resource *led_res;
static void *map_addr;
static struct timer_list timer_list;
unsigned long len = 8;
void led_timer(unsigned long data) {

	int tmp;
	while (1) {
		tmp = ioread8((unsigned long *) map_addr);
		tmp |= (0xF << 4);
		iowrite8(tmp, (unsigned long *) map_addr);

		msleep(500);

		tmp &= ~(0xF << 4);
		iowrite8(tmp, (unsigned long *) map_addr);

		msleep(500);
	}
}

static int __init dev_init(void)
{
	int ret,tmp;

	{
		unsigned tmp;
		tmp = readl(S3C64XX_GPKCON);
		tmp = (tmp & ~(0xffffU<<16))|(0x1111U<<16);
		writel(tmp, S3C64XX_GPKCON);
		
		tmp = readl(S3C64XX_GPKDAT);
		tmp |= (0xF << 4);
		writel(tmp, S3C64XX_GPKDAT);
	}

	printk(KERN_INFO "----------S3C64XX_GPKDAT:%X-----\n",S3C64XX_GPKDAT);

	led_res = request_mem_region((unsigned long *)0x7F008808, len, "zeke_leds");

	if(!led_res){
		printk(KERN_INFO "--request_mem_region error--\n");
	}

	map_addr = ioremap_nocache((unsigned long *)0x7F008808, len);

	printk(KERN_INFO "------map_addr->V:%X-------\n",map_addr);

//	(unsigned long)*map_addr = 0 << 6;

//	while (1) {
//			tmp = ioread8((unsigned long *) map_addr);
//			tmp |= (0xFF << 4);
//			iowrite8(tmp, (unsigned long *) map_addr);
//
//			msleep(100);
//
//			tmp &= ~(0xFF << 4);
//			iowrite8(tmp, (unsigned long *) map_addr);
//
//			msleep(100);
//		}


//	init_timer(&timer_list);
//	timer_list.function = led_timer;
//	timer_list.expires = jiffies + HZ;
//	add_timer(&timer_list);

	ret = misc_register(&misc);

	printk (DEVICE_NAME"\tinitialized\n");

	return ret;
}

static void __exit dev_exit(void)
{
	iounmap(map_addr);
	release_mem_region((unsigned long *)0x7F008808, len);
//	del_timer(&timer_list);
	misc_deregister(&misc);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FriendlyARM Inc.");
