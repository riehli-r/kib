#ifndef __MOUSETICK_H__
#define __MOUSETICK_H__

static ssize_t          mousetick_read(struct file *file, char *buf, size_t count, loff_t *ppos);
static irqreturn_t      key_interuption(int, void* , struct pt_regs*);

static struct file_operations kbd_fops = {
 read:    mousetick_read,
};

#endif
