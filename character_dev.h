
#ifndef CHARACTER_DEV_H
#define CHARACTER_DEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define IOCTL_GET_SIGNAL_INFO _IOR(MAJOR_NUM, 0, char *)
#define IOCTL_GET_SYSCALL_INFO _IOR(MAJOR_NUM, 1, char *)
#define IOCTL_GET_PCI_DEV _IOR(MAJOR_NUM, 2, char *)


struct lab_seccomp_data
{
    int nr;
    unsigned long long instruction_pointer;
    unsigned long long args[6];
};

struct lab_syscall_info
{
    unsigned long long sp;
    struct lab_seccomp_data data;
};
struct lab_syscall_info_data
{
    int pid;
    struct lab_syscall_info result;
};

struct lab_signal_struct
{
    int nr_threads;
    int group_exit_code;
    int notify_count;
    unsigned int flags;
    int leader;
};
struct lab_signal_struct_data
{
    int pid;
    struct lab_signal_struct result;
};
#define DEVICE_NAME "lab_character_device"
#endif