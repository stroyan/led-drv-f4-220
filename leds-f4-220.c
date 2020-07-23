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

static void volatile __iomem *map[12];

#define DEBUG 1

static int leds_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk(KERN_INFO "leds_open(%p)\n", file);
#endif // DEBUG

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
	size_t cmdlen;
	count = min(count, sizeof(buffer)-1);
	if (copy_from_user(&buffer, buf, count))
		return -EFAULT;
	buffer[count] = 0;
#ifdef DEBUG
	printk(KERN_INFO "leds_write(%s)\n", buffer);
#endif // DEBUG

	/* Strip trailing newline */
	cmdlen = strlen(buffer);
	if (cmdlen > 0 && buffer[cmdlen-1] == '\n') {
		buffer[cmdlen-1] = 0;
	}

	if (!strcmp("led1on", buffer)) {
		turn_on(map[0]);
	}
	else if (!strcmp("led1off", buffer)) {
		turn_off(map[0]);
	}
	else if (!strcmp("led2on", buffer)) {
		turn_on(map[1]);
	}
	else if (!strcmp("led2off", buffer)) {
		turn_off(map[1]);
	}
	else if (!strcmp("led3on", buffer)) {
		turn_on(map[2]);
	}
	else if (!strcmp("led3off", buffer)) {
		turn_off(map[2]);
	}
	else if (!strcmp("led4on", buffer)) {
		turn_on(map[3]);
	}
	else if (!strcmp("led4off", buffer)) {
		turn_off(map[3]);
	}
	else if (!strcmp("led5on", buffer)) {
		turn_on(map[4]);
	}
	else if (!strcmp("led5off", buffer)) {
		turn_off(map[4]);
	}
	else if (!strcmp("led6on", buffer)) {
		turn_on(map[5]);
	}
	else if (!strcmp("led6off", buffer)) {
		turn_off(map[5]);
	}
	else if (!strcmp("led7on", buffer)) {
		turn_on(map[6]);
	}
	else if (!strcmp("led7off", buffer)) {
		turn_off(map[6]);
	}
	else if (!strcmp("led8on", buffer)) {
		turn_on(map[7]);
	}
	else if (!strcmp("led8off", buffer)) {
		turn_off(map[7]);
	}
	else if (!strcmp("led9on", buffer)) {
		turn_on(map[8]);
	}
	else if (!strcmp("led9off", buffer)) {
		turn_off(map[8]);
	}
	else if (!strcmp("led10on", buffer)) {
		turn_on(map[9]);
	}
	else if (!strcmp("led10off", buffer)) {
		turn_off(map[9]);
	}
	else if (!strcmp("led11on", buffer)) {
		turn_on(map[10]);
	}
	else if (!strcmp("led11off", buffer)) {
		turn_off(map[10]);
	}
	else if (!strcmp("led12on", buffer)) {
		turn_on(map[11]);
	}
	else if (!strcmp("led12off", buffer)) {
		turn_off(map[11]);
	}
	else if (!strcmp("HD1_off", buffer)) {
		turn_on(map[0]);
		turn_off(map[1]);
	}
	else if (!strcmp("HD1_green", buffer)) {
		turn_off(map[0]);
		turn_off(map[1]);
	}
	else if (!strcmp("HD1_yellow", buffer)) {
		turn_off(map[0]);
		turn_on(map[1]);
	}
	else if (!strcmp("HD1_red", buffer)) {
		turn_on(map[0]);
		turn_on(map[1]);
	}
	else if (!strcmp("HD2_off", buffer)) {
		turn_on(map[2]);
		turn_off(map[3]);
	}
	else if (!strcmp("HD2_green", buffer)) {
		turn_off(map[2]);
		turn_off(map[3]);
	}
	else if (!strcmp("HD2_yellow", buffer)) {
		turn_off(map[2]);
		turn_on(map[3]);
	}
	else if (!strcmp("HD2_red", buffer)) {
		turn_on(map[2]);
		turn_on(map[3]);
	}
	else if (!strcmp("HD3_off", buffer)) {
		turn_on(map[4]);
		turn_off(map[5]);
	}
	else if (!strcmp("HD3_green", buffer)) {
		turn_off(map[4]);
		turn_off(map[5]);
	}
	else if (!strcmp("HD3_yellow", buffer)) {
		turn_off(map[4]);
		turn_on(map[5]);
	}
	else if (!strcmp("HD3_red", buffer)) {
		turn_on(map[4]);
		turn_on(map[5]);
	}
	else if (!strcmp("HD4_off", buffer)) {
		turn_on(map[6]);
		turn_off(map[7]);
	}
	else if (!strcmp("HD4_green", buffer)) {
		turn_off(map[6]);
		turn_off(map[7]);
	}
	else if (!strcmp("HD4_yellow", buffer)) {
		turn_off(map[6]);
		turn_on(map[7]);
	}
	else if (!strcmp("HD4_red", buffer)) {
		turn_on(map[6]);
		turn_on(map[7]);
	}
	else if (!strcmp("LAN1_off", buffer)) {
		turn_on(map[10]);
	}
	else if (!strcmp("LAN1_green", buffer)) {
		turn_off(map[10]);
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
#endif // DEBUG
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

static phys_addr_t map_addrs[12] = {
	0xfed0d1b8,
	0xfed0d028,
	0xfed0d0b8,
	0xfed0d0d8,
	0xfed0d088,
	0xfed0d0a8,
	0xfed0d048,
	0xfed0d068,
	0xfed0d018,
	0xfed0d038,
	0xfed0d058,
	0xfed0d098
};

int init_module(void){
	int error;
	int map_id;
	error = misc_register(&leds_miscdev);
	if (error)
		return error;
#ifdef DEBUG
	printk(KERN_INFO "TerraMaster F4-220 LED module loaded.\n");
#endif // DEBUG

	for (map_id = 0; map_id < 12; map_id++) {
		map[map_id] = ioremap_nocache(map_addrs[map_id], 16);
		if (!map[map_id]) {
			int i;
#ifdef DEBUG
			printk(KERN_INFO "ioremap_nocache(%lld,16) returned 0\n", map_addrs[map_id]);
#endif // DEBUG
			for (i = 0; i<map_id; i++)
				iounmap(map[i]);
			misc_deregister(&leds_miscdev);
			return ENOMEM;
		}
	}
	return 0;
}

void cleanup_module(void)
{
	int i;
#ifdef DEBUG
	printk(KERN_INFO "TerraMaster F4-220 LED module unloaded.\n");
#endif // DEBUG
	for (i = 0; i<12; i++)
		iounmap(map[i]);
	misc_deregister(&leds_miscdev);
}
MODULE_AUTHOR("Mike Stroyan <mike@stroyan.net>");
MODULE_DESCRIPTION("F4-220 LED driver");
MODULE_LICENSE("GPL");
