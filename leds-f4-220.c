/*
 *  leds-f4-220.c - LED light control for TerraMaster F4-220
 */
#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "TerraMaster F4-220 LED module loaded.\n");

	/*
	 * A non 0 return means init_module failed; module can't be loaded.
	 */
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "TerraMaster F4-220 LED module unloaded.\n");
}

MODULE_AUTHOR("Mike Stroyan <mike@stroyan.net>");
MODULE_DESCRIPTION("F4-220 LED driver");
MODULE_LICENSE("GPL");
