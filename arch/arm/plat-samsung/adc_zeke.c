#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>
#include <plat/adc.h>
#include <plat/regs-adc.h>

MODULE_LICENSE("GPL");

int adc_major = 250;
int adc_minor = 0;
int number_of_devices = 1;
struct s3c_adc_client *client;

struct cdev cdev;
dev_t devno = 0;
static struct class *myclass;

static ssize_t adc_conversion_read(struct file *file, char __user *buff, size_t count, loff_t *offset){
	unsigned data;
	unsigned ch;
	data = 10;
	ch = 0;
	data = s3c_adc_read(client, ch);
//	printk("data0 = %d\n", data);

	if (copy_to_user(buff, (char *) &data, sizeof(data)))
		return -EFAULT;

	return 0;
}

static int adc_conversion_open(struct inode *inode, struct file *file){
	return 0;
}

static int adc_conversion_release(struct inode *inode, struct file *file) {
	return 0;
}

static struct file_operations adc_conversion_fops = {
		.owner = THIS_MODULE,
		.read = adc_conversion_read,
		.open = adc_conversion_open,
		.release = adc_conversion_release, };

static int __devinit adc_conversion_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	int ret = -EINVAL;

	printk("function = %s\n", __func__);
	devno = MKDEV(adc_major, adc_minor);

	ret = register_chrdev_region(devno, number_of_devices, "adc_conversion");
	if (ret) {
		dev_err(dev, "failed to register device number\n");
		goto
		err_register_chrdev_region;
	}

	cdev_init(&cdev, &adc_conversion_fops);
	cdev.owner = THIS_MODULE;
	ret = cdev_add(&cdev, devno, number_of_devices);
	if (ret) {
		dev_err(dev, "failed to add device\n");
		goto
		err_cdev_add;
	}

	client = s3c_adc_register(pdev, NULL, NULL, 0);

	if (IS_ERR(client)) {
		dev_err(dev, "failed to register adc client\n");
		goto err_s3c_adc_register;
	}

	//2.6自动创建设备文件
	myclass = class_create(THIS_MODULE, "adc_conversion");
	if (IS_ERR(myclass)) {
		dev_err(dev, "failed to class_create\n");
	}
	device_create(myclass, NULL, MKDEV(adc_major, adc_minor), NULL, "adc_conversion");

	return 0;

	err_s3c_adc_register: cdev_del(&cdev);
	err_cdev_add: unregister_chrdev_region(devno, number_of_devices);
	err_register_chrdev_region: return ret;
}

static int __devexit adc_conversion_remove(struct platform_device *pdev) {
	s3c_adc_release(client);
	cdev_del(&cdev);
	unregister_chrdev_region(devno, number_of_devices);
	return 0;
}

static struct platform_driver adc_conversion_driver = {
		.driver = {
				.name = "adc_conversion_zeke",
				.owner = THIS_MODULE, },
		.probe = adc_conversion_probe,
		.remove = __devexit_p(adc_conversion_remove) };

static int __init adc_conversion_init(void) {
	return platform_driver_register(&adc_conversion_driver);
}

static void __exit adc_conversion_exit (void)
{
		platform_driver_unregister(&adc_conversion_driver );
}

module_init(adc_conversion_init);
module_exit(adc_conversion_exit);
