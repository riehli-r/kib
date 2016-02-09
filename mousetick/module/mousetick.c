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

#include "mousetick.h"

MODULE_AUTHOR("Alan Vannereau et Romain Riehling");
MODULE_DESCRIPTION("Mousetick");
MODULE_SUPPORTED_DEVICE("All mouse on IRQ 12");
MODULE_LICENSE("none");

static int ret;
static unsigned char buffer;
wait_queue_head_t queue;
char flag = 'n';

static ssize_t		mousetick_read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
  unsigned long a;
  wait_event_interruptible(queue, flag != 'n');
  a = copy_to_user((void*) buf, (void*) &buffer, sizeof(buffer));
  flag = 'n';
  return (sizeof(buffer));
}

static irqreturn_t	key_interuption(int irq, void* dev_id, struct pt_regs *regs)
{
  unsigned char		scancode;
  scancode = inb(0x60);
  buffer = (unsigned short) (scancode & 0x00ff);
  printk(KERN_INFO "Scancode: %u\n", buffer);
  flag = 'k';
  wake_up_interruptible(&queue);
  return (0);
}

static int		__init mousetick_init(void)
{
  ret = register_chrdev(332, "Mousetick", &kbd_fops); 
  if(ret < 0)
    {
      printk(KERN_WARNING "Mousetick failed to register\n");
      return ret;
    }
  if (request_irq(12, key_interuption, IRQF_SHARED, "Mousetick", (void *) &ret) < 0)
    {
      printk(KERN_WARNING "IRQ request failed\n");
      unregister_chrdev(332, "Mousetick");
      return (0);
    }
  else
    {
      init_waitqueue_head(&queue);
      printk(KERN_INFO "Mousetick sucess load\n");
      return (0);
    }
}

static void		__exit mousetick_cleanup(void)
{
  unregister_chrdev(332, "Mousetick");
  free_irq(12, (void*)&ret);
  printk(KERN_INFO "Mousetick sucess unload\n");
}

module_init(mousetick_init);
module_exit(mousetick_cleanup);
