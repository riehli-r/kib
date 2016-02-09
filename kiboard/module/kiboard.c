#include <asm/unistd.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include "kiboard.h"

MODULE_AUTHOR("Alan Vannereau et Romain Riehling");
MODULE_DESCRIPTION("Kiboard");
MODULE_SUPPORTED_DEVICE("All keyboard");
MODULE_LICENSE("none");

static int		ret;
static unsigned char	buffer;
wait_queue_head_t	queue;
char			flag = 'n';

static ssize_t		kiboard_read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
  unsigned long a;
  wait_event_interruptible(queue, flag != 'n');
  a = copy_to_user((void*) buf, (void*) &buffer, sizeof(buffer));
  flag = 'n';
  return (sizeof(buffer));
}

static irqreturn_t	key_interuption(int irq, void* dev_id, struct pt_regs *regs)
{
  unsigned char		status;
  unsigned char		scancode;
  status = inb(0x64);
  scancode = inb(0x60);
  buffer = (unsigned short) ((status << 8) | (scancode & 0x00ff));
  flag = 'k';
  wake_up_interruptible(&queue);
  return (0);
}

static int		__init kiboard_init(void)
{
  ret = register_chrdev(333, "Kiboard", &kbd_fops); 
  if(ret < 0)
    {
      printk(KERN_WARNING "Kiboard failed to register\n");
      return ret;
    }
  if (request_irq(1, key_interuption, IRQF_SHARED, "Kiboard", (void *) &ret) < 0)
    {
      printk(KERN_WARNING "IRQ request failed\n");
      unregister_chrdev(333, "Kiboard");
      return (0);
    }
  else
    {
      init_waitqueue_head(&queue);
      printk(KERN_INFO "Kiboard sucess load\n");
      return (0);
    }
}

static void		__exit kiboard_cleanup(void)
{
  unregister_chrdev(333, "Kiboard");
  free_irq(1, (void*)&ret);
  printk(KERN_INFO "Kiboard sucess unload\n");
}

module_init(kiboard_init);
module_exit(kiboard_cleanup);
