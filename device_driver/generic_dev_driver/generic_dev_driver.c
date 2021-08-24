/* Generic Kernel Module */

#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GENERAL CHARACTER DEVICE DRIVER");
MODULE_AUTHOR("MURAT ONER");

#define BUFFER_SIZE 256
const char g_buf[BUFFER_SIZE];

static int generic_open(struct inode* inode, struct file* filp);
static int generic_release(struct inode* inode, struct file* filp);

static ssize_t generic_read(struct file* filp, char* buf, size_t size, loff_t* offset);
static ssize_t generic_write(struct file* filp, const char* buf, size_t size, loff_t* offset);
static loff_t generi_llseek(struct file* filp, loff_t offset, int whence);

static dev_t g_dev;
struct cdev g_cdev;
static struct file_operations g_file_ops = {
    .owner = THIS_MODULE,
    .open = generic_open,
    .release = generic_release,
    .read = generic_read,
    .write = generic_write,
    .llseek = generi_llseek,
};

static int __init helloworld_init(void)
{
    int result = 0;

    pr_info("[MRTDBG] module init is called\n");

    if ((result = alloc_chrdev_region(&g_dev, 0, 1, "generic-char-driver")) < 0) {
        printk(KERN_INFO "Cannot alloc char driver!...\n");
        return result;
    }

    cdev_init(&g_cdev, &g_file_ops);

    result = cdev_add(&g_cdev, g_dev, 1);
    if (result < 0) {
        pr_info("can not add cdev\n");
        return result;
    }

    pr_info("[MRTDBG] SUCCESS module init\n");

    return 0;
}

static void __exit helloworld_exit(void)
{
    unregister_chrdev_region(g_dev, 1);
    pr_info("[MRTDBG] exit is called\n");
}

static int generic_open(struct inode* inode, struct file* filp)
{
    pr_info("[MRTDBG] generic open is called\n");
    return 0;
}

static int generic_release(struct inode* inode, struct file* filp)
{
    pr_info("[MRTDBG] generic close is called\n");
    return 0;
}

static ssize_t generic_read(struct file* filp, char* buf, size_t size, loff_t* offset)
{

    size_t actual_size = 0;
    long ret = 0;

    actual_size = size + *offset > BUFFER_SIZE ? BUFFER_SIZE - *offset : size;
    ret = copy_to_user(buf, g_buf + *offset, actual_size);
    if (ret != 0) {
        return -EFAULT;
    }

    *offset += actual_size;

    pr_info("[MRTDBG] generic read is called\n");

    return actual_size;
}

static ssize_t generic_write(struct file* filp, const char* buf, size_t size, loff_t* offset)
{
    int actual_size = 0;
    long ret = 0;

    actual_size = size + *offset > BUFFER_SIZE ? BUFFER_SIZE - *offset : size;
    ret = copy_from_user((void*)g_buf + *offset, buf, actual_size);
    if (ret != 0) {
        return -EFAULT;
    }

    *offset += actual_size;

    pr_info("[MRTDBG] generic write is called\n");

    return actual_size;
}

static loff_t generi_llseek(struct file* filp, loff_t off, int whence)
{
    loff_t toff;

    switch (whence) {
    case SEEK_SET:
        toff = off;
        break;
    case SEEK_CUR:
        toff = filp->f_pos + off;
        break;
    case SEEK_END:
        toff = BUFFER_SIZE + off;
        break;
    default:
        return -EINVAL;
    }
    pr_info("toff info : %lld", toff);
    if (toff > BUFFER_SIZE || toff < 0)
        return -EINVAL;

    filp->f_pos = toff;

    pr_info("[MRTDBG] generic llseek is called\n");
    return toff;
}

module_init(helloworld_init);
module_exit(helloworld_exit);