
#ifndef CHARACTER_DEV_H
#define CHARACTER_DEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define IOCTL_GET_PCI_DEV _IOR(MAJOR_NUM, 0, char *)
#define IOCTL_GET_VM_AREA_STRUCT _IOR(MAJOR_NUM, 1, char *)

struct pci_dev_info
{
    int find_device;
    unsigned short device;
};

struct vm_area_pos_info
{
    unsigned long vm_start;
    unsigned long vm_end;
    unsigned long permissions;
    unsigned long rb_subtree_gap;
};
struct vm_area_struct_info
{
    int pid;
    int actual_count;
    struct vm_area_pos_info vapi[30];
};
#define DEVICE_NAME "lab_character_device"

#endif