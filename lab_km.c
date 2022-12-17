
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/version.h>
#include <linux/fs.h>

#include "character_dev.h"
#include <linux/if_tun.h>
#include <linux/if_macvlan.h>
#include <linux/signal.h>
#include <linux/pagemap.h>
#include <linux/page-flags.h>
#include <linux/mm_types.h>
#include "linux/mm.h"
#include <asm/pgtable.h>
#include <asm/page.h>

#include <asm/uaccess.h>
#include <linux/netdevice.h>
#include <linux/list.h>
#include <asm/siginfo.h>
#include <linux/rcupdate.h>
#include <linux/sched.h>
#include <linux/ptrace.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/pid.h>
#include <linux/types.h>
#include <linux/export.h>
#include <asm/syscall.h>

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
    struct task_struct *t = NULL;
    switch (ioctl_num)
    {

    case IOCTL_GET_PCI_DEV:
        // ndi = vmalloc(sizeof(struct n_dev_info));
        struct net_device *n_dev;
        read_lock(&dev_base_lock);
        n_dev = first_net_device(&init_net);
        if (!n_dev)
            return 0;
        // if (!n_dev)
        // {
        //     strcat(output, "No network devices ;(((");
        // }
        int count = 0;
        char buff_int[10];
        while (n_dev)
        {
            // sprintf(buff_int, "%d", c);
            // strcat(output, "Number of net device: ");
            // strcat(output, buff_int);
            // strcat(output, "\n");
            // sprintf(buff_int, "%s", n_dev->name);
            // strcat(output, buff_int);
            // strcat(output, "\n");
            // strcat(output, "State: ");
            // sprintf(buff_int, "%d", n_dev->state);
            // strcat(output, buff_int);
            printk(KERN_INFO "%s",n_dev->name);
            n_dev = next_net_device(n_dev);
            int count = 0;

            // c++;
            // strcat(output, "\n\n");
        }
        // strcat(output, "Total number of ");
        // sprintf(buff_int, "%d", c);
        // strcat(output, buff_int);
        read_unlock(&dev_base_lock);

        // ndi->size = c;

        // msg = vmalloc(sizeof(struct message));
        // msg->si = *si;
        // msg->ndi = *ndi;
        break;

        // case IOCTL_GET_SYSCALL_INFO:

        //     struct lab_syscall_info_data *lsysid = vmalloc(sizeof(struct lab_syscall_info_data));
        //     copy_from_user(lsysid, (struct lab_syscall_info_data *)ioctl_param, sizeof(struct lab_syscall_info_data));
        //     t = get_pid_task(find_get_pid(lsysid->pid), PIDTYPE_PID);
        //     if (t == NULL)
        //     {
        //         printk(KERN_ERR "task_struct with pid=%d does not exist\n", lsysid->pid);
        //         vfree(lsysid);
        //         return 1;
        //     };
        //     struct syscall_info *info=  vmalloc(sizeof(struct syscall_info));
        //     struct pt_regs *regs;
        //     regs = task_pt_regs(lsysid->pid);
        //     info->sp = user_stack_pointer(regs);
        //     info->data.instruction_pointer = instruction_pointer(regs);

        //     info->data.nr = syscall_get_nr(lsysid->pid, regs);

        //     lsysid->result.sp = info->sp;
        //     lsysid->result.data.instruction_pointer =  info->data.instruction_pointer;
        //     lsysid->result.data.nr =  info->data.nr;

        //     copy_to_user((struct lab_syscall_info_data *)ioctl_param, lsysid, sizeof(struct lab_syscall_info_data));
        //     vfree(info);
        //     vfree(lsysid);
        //     break;
        // case IOCTL_GET_SIGNAL_INFO:

        //     struct lab_signal_struct_data *lsigsd = vmalloc(sizeof(struct lab_signal_struct_data));
        //     copy_from_user(lsigsd, (struct lab_signal_struct_data *)ioctl_param, sizeof(struct lab_signal_struct_data));
        //     t = get_pid_task(find_get_pid(lsigsd->pid), PIDTYPE_PID);
        //     if (t == NULL)
        //     {
        //         printk(KERN_ERR "task_struct with pid=%d does not exist\n", lsigsd->pid);
        //         vfree(lsigsd);
        //         return 2;
        //     };
        //     lsigsd->result.flags = t->signal->flags;
        //     lsigsd->result.group_exit_code = t->signal->group_exit_code;
        //     lsigsd->result.leader = t->signal->leader;
        //     lsigsd->result.notify_count = t->signal->notify_count;

        //     lsigsd->result.nr_threads = t->signal->nr_threads;
        //     copy_to_user((struct lab_signal_struct_data *)ioctl_param, lsigsd, sizeof(struct lab_signal_struct_data));
        //     vfree(lsigsd);
        //     break;
    }
    return 0;
}

struct file_operations file_ops = {
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