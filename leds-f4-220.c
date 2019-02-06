/*
 *  leds-f4-220.c - LED light control for TerraMaster F4-220
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	/* for get_user and put_user */
#include <linux/printk.h>

#define DEBUG 1

static int leds_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk(KERN_INFO "leds_open(%p)\n", file);
#endif

	return 0;
}

static ssize_t leds_write(struct file *file, const char __user *buf,
				size_t count, loff_t *pos)
{
#define BUFSIZE 64
	char buffer[BUFSIZE];
	count = min(count, sizeof(buffer));
	if (copy_from_user(&buffer, buf, count))
		return -EFAULT;
	buffer[count] = 0;
	printk(KERN_INFO "leds_write(%s)\n", buffer);
	return count;
}

static int leds_release(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk(KERN_INFO "leds_release(%p)\n", file);
#endif
	return 0;
}

static const struct file_operations leds_fops = {
	.owner		= THIS_MODULE,
	.open		= leds_open,
	.write		= leds_write,
	.release	= leds_release,
	.llseek		= no_llseek,
};

static struct miscdevice leds_miscdev = {
	.name	= "leds",
	.fops	= &leds_fops,
	.minor	= MISC_DYNAMIC_MINOR,
};

int init_module(void){
	int error;
	error = misc_register(&leds_miscdev);
	if (error)
        return error;
#ifdef DEBUG
	printk(KERN_INFO "TerraMaster F4-220 LED module loaded.\n");
#endif

	/*
	 * A non 0 return means init_module failed; module can't be loaded.
	 */
	return 0;
}

void cleanup_module(void)
{
#ifdef DEBUG
	printk(KERN_INFO "TerraMaster F4-220 LED module unloaded.\n");
#endif
	misc_deregister(&leds_miscdev);
}

MODULE_AUTHOR("Mike Stroyan <mike@stroyan.net>");
MODULE_DESCRIPTION("F4-220 LED driver");
MODULE_LICENSE("GPL");
