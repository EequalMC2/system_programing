
/* pipe-driver.c */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PIPE DEVICE DRIVER EXAMPLE");

#define MIN(a, b)       ((a) < (b) ? (a) : (b))

#define PIPE_SIZE     4096

static int generic_open(struct inode *inodep, struct file *filp);
static int generic_release(struct inode *inodep, struct file *filp);
static ssize_t generic_read(struct file *filp, char *buf, size_t size, loff_t *off);
static ssize_t generic_write(struct file *filp, const char *buf, size_t size, loff_t *off);

static dev_t g_dev;
static struct cdev *g_cdev;
static struct file_operations g_file_ops = {
    .owner = THIS_MODULE,
    .open = generic_open,
    .release = generic_release,
    .read = generic_read,
    .write = generic_write,
};

static char g_pipebuf[PIPE_SIZE];
static size_t g_head = 0, g_tail = 0;
static size_t g_count = 0;

static int __init generic_init(void)     
{
    int result;

    if ((result = alloc_chrdev_region(&g_dev, 0, 1, "pipe-driver")) < 0) {
        printk(KERN_INFO "Cannot alloc char driver!...\n");
        return result; 
    }

    if ((g_cdev = cdev_alloc()) == NULL) {
        printk(KERN_INFO "Cannot allocate cdev!..\n");
        return -ENOMEM;
    }

    g_cdev->owner = THIS_MODULE;
    g_cdev->ops = &g_file_ops;
    
    if ((result = cdev_add(g_cdev, g_dev, 1)) != 0) {
        unregister_chrdev_region(g_dev, 1);
        printk(KERN_INFO "Cannot add charecter device driver!...\n");
        return result;
    }
    
    printk(KERN_INFO "Pipe driver initialized with %d:%d device number...\n", MAJOR(g_dev), MINOR(g_dev));

    return 0;
}

static void __exit generic_exit(void)
{
    cdev_del(g_cdev);
    unregister_chrdev_region(g_dev, 1);

    printk(KERN_INFO "Goodbye...\n");
}

static int generic_open(struct inode *inodep, struct file *filp)
{
    printk(KERN_INFO "Pipe device opened!..\n");

    return 0;
}

static int generic_release(struct inode *inodep, struct file *filp)
{
    printk(KERN_INFO "Pipe device released!..\n");

    return 0;
}

static ssize_t generic_read(struct file *filp, char *buf, size_t size, loff_t *off)
{
     size_t len;

     size = MIN(size, g_count);

     if (size == 0)
        return 0;

    if (g_head >= g_tail)
        len = MIN(size, PIPE_SIZE - g_head);
    else
        len = size;
    
    if (copy_to_user(buf, g_pipebuf + g_head, len) != 0) 
            return -EFAULT;
    if (size > len)
        if (copy_to_user(buf + len, g_pipebuf, size - len) != 0) 
            return -EFAULT;

    g_head = (g_head + size ) % PIPE_SIZE;
    g_count -= size;

    return size;
}

static ssize_t generic_write(struct file *filp, const char *buf, size_t size, loff_t *off)
{
    size_t len;

    if (size > PIPE_SIZE - g_count)    
        return -ENOMEM;

    if (g_tail >= g_head)
        len = MIN(size, PIPE_SIZE - g_tail);
    else
        len = size;

    if (copy_from_user(g_pipebuf + g_tail, buf, len) != 0) 
        return -EFAULT;
    
    if (size > len)
        if (copy_from_user(g_pipebuf, buf + len, size - len) != 0) 
            return -EFAULT;

    g_tail = (g_tail + size ) % PIPE_SIZE;
    g_count += size;

    return size;
}

module_init(generic_init);
module_exit(generic_exit);
    
