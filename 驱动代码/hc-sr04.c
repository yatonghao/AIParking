#include <linux/module.h>
#include <linux/poll.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/fcntl.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <asm/current.h>
#include <linux/delay.h>
#include <linux/timex.h>



static int major=0;
static struct class *sr04_class;
static struct gpio_desc *sr04_echo;
static struct gpio_desc *sr04_trig;
static int irq;
static u64 sr04_data_ns = 0;
static wait_queue_head_t sr04_wq;



static ssize_t sr04_read (struct file *file, char __user *buf, size_t size, loff_t *off)
{
	int err;
	int timeout;
	/*发出至少10us的触发信号*/
	gpiod_set_value(sr04_trig, 1);
	udelay(15);
	gpiod_set_value(sr04_trig, 0);

	/* 等待数据 */
	timeout = wait_event_interruptible_timeout(sr04_wq, sr04_data_ns, HZ);	
	if (timeout)
	{
		err = copy_to_user(buf, &sr04_data_ns, 4);
		sr04_data_ns = 0;
		return 4;
	}
	else
	{
		return -EAGAIN;
	}

	
	return 0;

}

static int sr04_open (struct inode *inode, struct file *file)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}



static struct file_operations sr04_ops={
	.owner		= THIS_MODULE,
	.open		= sr04_open,
	.read		= sr04_read,	
};

static irqreturn_t sr04_isr(int irq, void *dev_id)
{
	int val = gpiod_get_value(sr04_echo);

	if(val)
	{
		/*上升沿*/
		
sr04_data_ns = ktime_get_ns();
	}
	else
	{
		/*下降沿*/
		sr04_data_ns = ktime_get_ns() - sr04_data_ns;
		/* 2. 唤醒APP:去同一个链表把APP唤醒 */
		wake_up(&sr04_wq);
	}

	return IRQ_HANDLED; // IRQ_WAKE_THREAD;
}



static int sr04_probe(struct platform_device *pdev)
{
	int err;

	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

	/*1.获取硬件信息*/
	sr04_echo=gpiod_get(&pdev->dev, "echo", GPIOD_IN);
	if (IS_ERR(sr04_echo)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	}
	sr04_trig=gpiod_get(&pdev->dev, "trig", GPIOD_OUT_LOW);
	if (IS_ERR(sr04_trig)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	}

	/*得到irq*/
	irq = gpiod_to_irq(sr04_echo);
	/*申请中断并设置为双边沿触发*/
	err = request_irq(irq, sr04_isr, IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING, "sr04", NULL);
	if (err != 0) {
		printk("request_irq is err\n");
	}
	
	/*2.创建设备节点*/	
	device_create(sr04_class, NULL, MKDEV(major, 0), NULL, "sr04");
        
    return 0;	
}

static int sr04_remove(struct platform_device *pdev)
{		
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	device_destroy(sr04_class, MKDEV(major, 0));
	free_irq(irq, NULL);
	gpiod_put(sr04_trig);
	gpiod_put(sr04_echo);
	return 0;
}

static const struct of_device_id my_sr04[] = {
    { .compatible = "my,sr04" },
    { },
};


static struct platform_driver sr04={
	.driver = {
		.name = "sr04",
		.of_match_table = my_sr04,	
	},
	.probe = sr04_probe,
	.remove	= sr04_remove,	
};


static int __init sr04_init(void)
{
	int err;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	/*确定主设备号*/
	major=register_chrdev(major, "mysr04", &sr04_ops);
	/*创建类*/
	sr04_class=class_create(THIS_MODULE, "sr04");
	if (IS_ERR(sr04_class)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "mysr04");
		return PTR_ERR(sr04_class);
	}

	init_waitqueue_head(&sr04_wq);//初始化队列
	
	err=platform_driver_register(&sr04);
	
	return 0;
}

static void __exit sr04_exit(void)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	platform_driver_unregister(&sr04);
	class_destroy(sr04_class);
	unregister_chrdev(major, "mysr04");	
}

module_init(sr04_init);
module_exit(sr04_exit);

MODULE_LICENSE("GPL");


