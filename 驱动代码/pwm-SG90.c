#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/irqreturn.h>
#include <linux/of_gpio.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/gpio/consumer.h>
#include <linux/delay.h>
#include <linux/timekeeping.h>
#include <linux/wait.h>
#include <linux/irqflags.h>
#include <linux/pwm.h>
#define SG90_CNT 1
#define SG90_NAME "sg90"
struct sg90dev_dev {
    dev_t devid;                    
    struct cdev cdev;          
	struct device *device;  
    struct class *class;
    struct device_node *node;
    struct pwm_device *sg90_pwm;
};
static struct sg90dev_dev  sg90_dev;


static int sg90_open (struct inode *node, struct file *filp)
{
	return 0;
}

static ssize_t sg90_write (struct file *filp, const char __user *buf, size_t size, loff_t *offset)
{
	int res;
	unsigned char data[1];
	if(size != 1)
		return 1;

	res = copy_from_user(data, buf, size);
	/* 配置PWM：旋转任意角度(单位1度) */
	pwm_config(sg90_dev.sg90_pwm, 500000 + data[0] * 100000 / 9, 20000000);   
	return 1;
}

static int sg90_release (struct inode *node, struct file *filp)
{
	return 0;
}

static struct file_operations sg90_ops = {
	.owner		=	THIS_MODULE,
	.open 		= 	sg90_open,
	.write 		= 	sg90_write,
	.release 	=	sg90_release,
};

static int sg90_probe(struct platform_device *pdev)
{

	/* 1、设置设备号 */
	alloc_chrdev_region(&sg90_dev.devid, 0, SG90_CNT,SG90_NAME);

 	/* 2、注册设备 */
	cdev_init(&sg90_dev.cdev, &sg90_ops);
	cdev_add(&sg90_dev.cdev, sg90_dev.devid, SG90_CNT);

	 /* 3、创建类 */
	sg90_dev.class = class_create(THIS_MODULE, SG90_NAME);
	if (IS_ERR(sg90_dev.class)) {
		return PTR_ERR(sg90_dev.class);
	}
	/* 4、创建设备 */
	sg90_dev.device = device_create(sg90_dev.class, NULL, sg90_dev.devid, NULL, SG90_NAME);
	if (IS_ERR(sg90_dev.device)) {
		return PTR_ERR(sg90_dev.device);
	}

    sg90_dev.node = pdev->dev.of_node;

    printk("sg90 match success \n");
    if (sg90_dev.node){
        /* 从子节点中获取PWM设备 */
        sg90_dev.sg90_pwm = devm_of_pwm_get(&pdev->dev, sg90_dev.node, NULL);  
        if (IS_ERR(sg90_dev.sg90_pwm)){
            printk(KERN_ERR" pwm_test,get pwm  error!!\n");
            return -1;
        }
    }
    else{
        printk(KERN_ERR" pwm_test of_get_next_child  error!!\n");
        return -1;
    }

    pwm_config(sg90_dev.sg90_pwm, 1500000, 20000000);   /* 配置PWM：1.5ms，90度，周期：20000000ns = 20ms */
    pwm_set_polarity(sg90_dev.sg90_pwm, PWM_POLARITY_NORMAL); /* 设置输出极性：占空比为高电平 */
    pwm_enable(sg90_dev.sg90_pwm);    /* 使能PWM输出 */

    return 0;
}

static int sg90_remove(struct platform_device *dev)
{
	pwm_config(sg90_dev.sg90_pwm, 500000, 20000000);  /* 配置PWM：0.5ms，0度 */
	pwm_free(sg90_dev.sg90_pwm);

	cdev_del(&sg90_dev.cdev);
	unregister_chrdev_region(sg90_dev.devid, SG90_CNT);
	device_destroy(sg90_dev.class, sg90_dev.devid);
	class_destroy(sg90_dev.class);
	
	return 0;
}

static const struct of_device_id sg90_of_match[] = {
	{ .compatible = "hc-sg90" },
	{ }
};

static struct platform_driver sg90_platform_driver = {
	.driver = {
		.name		= "my_sg90",
		.of_match_table	= sg90_of_match,
	},
	.probe			= sg90_probe,
	.remove			= sg90_remove,
};


static int sg90_init(void)
{
	return platform_driver_register(&sg90_platform_driver);
}

static void sg90_exit(void)
{
	platform_driver_unregister(&sg90_platform_driver);
}

module_init(sg90_init);
module_exit(sg90_exit);
MODULE_LICENSE("GPL");

