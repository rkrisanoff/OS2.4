#include "character_dev.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
    int fd;

    if (argc < 2 || (strcmp(argv[1], "help") == 0))
    {
        printf("Usage %s <PID> <PAGE-NUMBER>\n", argv[0]);
        printf("<PID> must be integer more than zero\n");

        return 0;
    }
    int pid = atoi(argv[1]);
    if (pid)
    {
        printf("Entered <PID> is %d\n", pid);
    }
    else
    {
        printf("Wrong <PID>\n");
        return 1;
    }

    fd = open(DEVICE_NAME, 0);

    if (fd < 0)
    {
        printf("Can't open device file: %s\n", DEVICE_NAME);
        exit(2);
    }
    int ret_val = ioctl(fd, IOCTL_GET_PCI_DEV, NULL);


    // struct lab_syscall_info_data *lsysid = malloc(sizeof(struct lab_syscall_info_data));

    // lsysid->pid = pid;

    // int ret_val = ioctl(fd, IOCTL_GET_SIGNAL_INFO, lsysid);
    // if (ret_val != 0)
    // {
    //     printf("IOCTL_GET_SYSCALL_INFO failed %d: process with <PID> = %d doesn't exist\n", ret_val, lsysid->pid);
    //     exit(ret_val);
    // }

    // printf("<-- SYSCALL INFO -->\n");
    // printf("FOR SYSCALL INFO WITH PID = %d\n", lsysid->pid);
    // printf("STACK POINTER = %llu\n", lsysid->result.sp);
    // printf("NR = %d\n", lsysid->result.data.nr);
    // printf("INSTRUCTION POINTER = %llu\n", lsysid->result.data.instruction_pointer);

    // struct lab_signal_struct_data *lsigsd = malloc(sizeof(struct lab_signal_struct_data));

    // lsigsd->pid = pid;

    // ret_val = ioctl(fd, IOCTL_GET_SIGNAL_INFO, lsigsd);
    // if (ret_val != 0)
    // {
    //     printf("IOCTL_GET_SYSCALL_INFO failed %d: process with <PID> = %d doesn't exist\n", ret_val, lsigsd->pid);
    //     exit(ret_val);
    // }

    // printf("<-- SIGNAL STRUCT -->\n");
    // printf("FOR SIGNAL_STRUCT WITH PID = %d\n", lsigsd->pid);
    // printf("FLASG = %x\n", lsigsd->result.flags);
    // printf("GROUP EXIT CODE = %d\n", lsigsd->result.group_exit_code);
    // printf("LEADER = %d\n", lsigsd->result.leader);
    // printf("NOTIFY COUNT = %d\n", lsigsd->result.notify_count);
    // printf("NR THREAD = %d\n", lsigsd->result.nr_threads);

    return 0;
}
