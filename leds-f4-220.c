// SPDX-License-Identifier: GPL-2.0
/*
 *  leds-f4-220.c - LED light control for TerraMaster F4-220
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	/* for get_user and put_user */

static void volatile __iomem *gpbcon[12];

#define DEBUG 1

static int leds_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk(KERN_INFO "leds_open(%p)\n", file);
#endif

	return 0;
}

static void turn_on(void volatile __iomem *addr)
{
		u64 reg;
		reg = readq(addr);
		reg &= 0x11111101;
		writeq(reg, addr);
		reg = readq(addr);
		reg |= 0x1;
		writeq(reg, addr);
		reg = readq(addr);
		reg |= 0x10;
		writeq(reg, addr);
}

static void turn_off(void volatile __iomem *addr)
{
		u64 reg;
		reg = readq(addr);
		reg &= 0x11111101;
		writeq(reg, addr);
		reg = readq(addr);
		reg &= ~0x1ul;
		writeq(reg, addr);
		reg = readq(addr);
		reg |= 0x10;
		writeq(reg, addr);
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
	if (!strcmp("led1on", buffer)) {
		turn_on(gpbcon[0]);
	}
	else if (!strcmp("led1off", buffer)) {
		turn_off(gpbcon[0]);
	}
	else if (!strcmp("led2on", buffer)) {
		turn_on(gpbcon[1]);
	}
	else if (!strcmp("led2off", buffer)) {
		turn_off(gpbcon[1]);
	}
	else if (!strcmp("led3on", buffer)) {
		turn_on(gpbcon[2]);
	}
	else if (!strcmp("led3off", buffer)) {
		turn_off(gpbcon[2]);
	}
	else if (!strcmp("led4on", buffer)) {
		turn_on(gpbcon[3]);
	}
	else if (!strcmp("led4off", buffer)) {
		turn_off(gpbcon[3]);
	}
	else if (!strcmp("led5on", buffer)) {
		turn_on(gpbcon[4]);
	}
	else if (!strcmp("led5off", buffer)) {
		turn_off(gpbcon[4]);
	}
	else if (!strcmp("led6on", buffer)) {
		turn_on(gpbcon[5]);
	}
	else if (!strcmp("led6off", buffer)) {
		turn_off(gpbcon[5]);
	}
	else if (!strcmp("led7on", buffer)) {
		turn_on(gpbcon[6]);
	}
	else if (!strcmp("led7off", buffer)) {
		turn_off(gpbcon[6]);
	}
	else if (!strcmp("led8on", buffer)) {
		turn_on(gpbcon[7]);
	}
	else if (!strcmp("led8off", buffer)) {
		turn_off(gpbcon[7]);
	}
	else if (!strcmp("led9on", buffer)) {
		turn_on(gpbcon[8]);
	}
	else if (!strcmp("led9off", buffer)) {
		turn_off(gpbcon[8]);
	}
	else if (!strcmp("led10on", buffer)) {
		turn_on(gpbcon[9]);
	}
	else if (!strcmp("led10off", buffer)) {
		turn_off(gpbcon[9]);
	}
	else if (!strcmp("led11on", buffer)) {
		turn_on(gpbcon[10]);
	}
	else if (!strcmp("led11off", buffer)) {
		turn_off(gpbcon[10]);
	}
	else if (!strcmp("led12on", buffer)) {
		turn_on(gpbcon[11]);
	}
	else if (!strcmp("led12off", buffer)) {
		turn_off(gpbcon[11]);
	}
	else if (!strcmp("HD1_off", buffer)) {
		turn_on(gpbcon[1]);
		turn_off(gpbcon[2]);
	}
	else if (!strcmp("HD1_green", buffer)) {
		turn_off(gpbcon[1]);
		turn_off(gpbcon[2]);
	}
	else if (!strcmp("HD1_yellow", buffer)) {
		turn_off(gpbcon[1]);
		turn_on(gpbcon[2]);
	}
	else if (!strcmp("HD1_red", buffer)) {
		turn_on(gpbcon[1]);
		turn_on(gpbcon[2]);
	}
	else if (!strcmp("HD2_off", buffer)) {
		turn_on(gpbcon[3]);
		turn_off(gpbcon[4]);
	}
	else if (!strcmp("HD2_green", buffer)) {
		turn_off(gpbcon[3]);
		turn_off(gpbcon[4]);
	}
	else if (!strcmp("HD2_yellow", buffer)) {
		turn_off(gpbcon[3]);
		turn_on(gpbcon[4]);
	}
	else if (!strcmp("HD2_red", buffer)) {
		turn_on(gpbcon[3]);
		turn_on(gpbcon[4]);
	}
	else if (!strcmp("HD3_off", buffer)) {
		turn_on(gpbcon[5]);
		turn_off(gpbcon[6]);
	}
	else if (!strcmp("HD3_green", buffer)) {
		turn_off(gpbcon[5]);
		turn_off(gpbcon[6]);
	}
	else if (!strcmp("HD3_yellow", buffer)) {
		turn_off(gpbcon[5]);
		turn_on(gpbcon[6]);
	}
	else if (!strcmp("HD3_red", buffer)) {
		turn_on(gpbcon[5]);
		turn_on(gpbcon[6]);
	}
	else if (!strcmp("HD4_off", buffer)) {
		turn_on(gpbcon[7]);
		turn_off(gpbcon[8]);
	}
	else if (!strcmp("HD4_green", buffer)) {
		turn_off(gpbcon[7]);
		turn_off(gpbcon[8]);
	}
	else if (!strcmp("HD4_yellow", buffer)) {
		turn_off(gpbcon[7]);
		turn_on(gpbcon[8]);
	}
	else if (!strcmp("HD4_red", buffer)) {
		turn_on(gpbcon[7]);
		turn_on(gpbcon[8]);
	}
	else if (!strcmp("LAN1_off", buffer)) {
		turn_on(gpbcon[11]);
	}
	else if (!strcmp("LAN1_green", buffer)) {
		turn_off(gpbcon[11]);
	}
	/*
	 * Lights 1, 3, 5, 7 turn green leds "off" for "on" for "HD1", "HD2", "HD3" and "HD4".
     * Lights 2, 4, 6, 8 turn red leds "off" for "off" for "HD1", "HD2", "HD3" and "HD4".
     * Lights 9 and 10 change nothing.
     * Light 11 turns a green led "off" for "on" for "LAN1".
	 */
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

	gpbcon[0] = ioremap_nocache(0xfed0d1b8, 16);
	printk(KERN_INFO "ioremap_nocache(0xfed0d1b8,16) returned %p\n",gpbcon[0]);
	gpbcon[1] = ioremap_nocache(0xfed0d028, 16);
	gpbcon[2] = ioremap_nocache(0xfed0d0b8, 16);
	gpbcon[3] = ioremap_nocache(0xfed0d0d8, 16);
	gpbcon[4] = ioremap_nocache(0xfed0d088, 16);
	gpbcon[5] = ioremap_nocache(0xfed0d0a8, 16);
	gpbcon[6] = ioremap_nocache(0xfed0d048, 16);
	gpbcon[7] = ioremap_nocache(0xfed0d068, 16);
	gpbcon[8] = ioremap_nocache(0xfed0d018, 16);
	gpbcon[9] = ioremap_nocache(0xfed0d038, 16);
	gpbcon[10] = ioremap_nocache(0xfed0d058, 16);
	gpbcon[11] = ioremap_nocache(0xfed0d098, 16);

	return 0;
}

void cleanup_module(void)
{
	int i;
#ifdef DEBUG
	printk(KERN_INFO "TerraMaster F4-220 LED module unloaded.\n");
#endif
	for (i = 0; i<12; i++)
		iounmap(gpbcon[i]);
	misc_deregister(&leds_miscdev);
}

MODULE_AUTHOR("Mike Stroyan <mike@stroyan.net>");
MODULE_DESCRIPTION("F4-220 LED driver");
MODULE_LICENSE("GPL");
