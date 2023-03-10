
#ifndef CHARACTER_DEV_H
#define CHARACTER_DEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100
#define MAX_COUNT_VM_AREA_STRUCTES 50
#define MAX_COUNT_PCI_DEV 20


#define IOCTL_GET_PCI_DEV _IOR(MAJOR_NUM, 0, char *)
#define IOCTL_GET_VM_AREA_STRUCT _IOR(MAJOR_NUM, 1, char *)

struct pci_dev_info
{
    int actual_count;
    unsigned short devices[MAX_COUNT_PCI_DEV];
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
    struct vm_area_pos_info vapi[MAX_COUNT_VM_AREA_STRUCTES];
};
#define DEVICE_NAME "lab_character_device"

#endif