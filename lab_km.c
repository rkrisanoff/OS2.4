
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/version.h>
#include <linux/fs.h>

#include "character_dev.h"

#include <asm/uaccess.h>
#include <linux/list.h>
#include <linux/syscalls.h>
#include <linux/pci.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL");
MODULE_VERSION("2.0.22");
MODULE_AUTHOR("Uzbek");
MODULE_DESCRIPTION("OS LAB2");

static int lab_dev_open(struct inode *inode, struct file *file);
static int lab_dev_release(struct inode *inode, struct file *file);
static ssize_t lab_dev_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t lab_dev_write(struct file *filp, const char *buf, size_t len, loff_t *off);
static long lab_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
/*
** This function will be called when we open the Device file
*/
static int lab_dev_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device File Opened...!!!\n");
    return 0;
}
/*
** This function will be called when we close the Device file
*/
static int lab_dev_release(struct inode *inode, struct file *file)
{

    printk(KERN_INFO "Device File Closed...!!!\n");
    return 0;
}
/*
** This function will be called when we read the Device file
*/
static ssize_t lab_dev_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Read Function\n");
    return 0;
}
/*
** This function will be called when we write the Device file
*/
static ssize_t lab_dev_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Write function\n");
    return len;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35))
static int device_ioctl(struct inode *inode,
                        struct file *file,
                        unsigned int ioctl_num,
                        unsigned long ioctl_param)
#else
static long lab_dev_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
#endif
{
    printk(KERN_INFO "lab_dev_ioctl(%p,%lu,%lu)", file, ioctl_num, ioctl_param);
    if (ioctl_num == IOCTL_GET_PCI_DEV)
    {

        struct pci_dev_info *pdi = vmalloc(sizeof(struct pci_dev_info));
        int i = 0;
        struct pci_dev *dev = NULL; ;
        while ((dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, dev)) && (i<MAX_COUNT_PCI_DEV))
        {
            pdi->devices[i] = dev->device;
            i++;
        };
        pdi->actual_count = i - 1;
        copy_to_user((struct pci_dev_info *)ioctl_param, pdi, sizeof(struct pci_dev_info));
        vfree(pdi);
    }
    if (ioctl_num == IOCTL_GET_VM_AREA_STRUCT)
    {

        struct vm_area_struct_info *vasi = vmalloc(sizeof(struct vm_area_struct_info));
        copy_from_user(vasi, (struct vm_area_struct_info *)ioctl_param, sizeof(struct vm_area_struct_info));
        struct task_struct *task;

        task = get_pid_task(find_get_pid(vasi->pid), PIDTYPE_PID);
        if (task == NULL)
        {
            pr_err("labmod: process not found\n");
            return 3;
        }

        if (task->mm == NULL)
        {
            printk(KERN_INFO "Can't find vm_area_struct with this pid\n");
            return 39;
        }
        struct mm_struct *mm;
        struct vm_area_struct *vm_area;
        printk(KERN_INFO "vm area struct\n");
        struct vm_area_struct *pos = NULL;
        int i = 0;
        for (pos = task->mm->mmap, i = 0; pos != NULL && i<MAX_COUNT_VM_AREA_STRUCTES; pos = pos->vm_next, i++)
        {
            vasi->vapi[i].permissions = pos->vm_flags;
            vasi->vapi[i].vm_start = pos->vm_start;
            vasi->vapi[i].vm_end = pos->vm_end;
            vasi->vapi[i].rb_subtree_gap = pos->rb_subtree_gap;
        }
        vasi->actual_count = i - 1;
        copy_to_user((struct vm_area_struct_info *)ioctl_param, vasi, sizeof(struct vm_area_struct_info));
        vfree(vasi);
    }
    return 0;
}

struct file_operations file_ops =
    {
        .owner = THIS_MODULE,
        .read = lab_dev_read,
        .write = lab_dev_write,
        .open = lab_dev_open,
        .release = lab_dev_release,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35))
        .ioctl = device_ioctl
#else
        .unlocked_ioctl = lab_dev_ioctl
#endif
};

int init_module()
{
    int ret_val;
    ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &file_ops);
    if (ret_val < 0)
    {
        printk(KERN_ALERT "%s failed with %d\n", "Sorry, registering the character device \n", ret_val);
        return ret_val;
    }

    return 0;
}

void cleanup_module()
{
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}