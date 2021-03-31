#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/sandbox.h>

SYSCALL_DEFINE1(register_proc_with_sandbox, pid_t __user, pid)
{
    if(is_proc_in_sandbox(pid)){
        return 1;
    }

    return add_proc_to_sandbox(pid);   
}

SYSCALL_DEFINE1(unregister_proc_with_sandbox, pid_t __user, pid)
{
    return del_proc_from_sandbox(pid);
}

//for check registered pid
SYSCALL_DEFINE1(register_syscall_with_sandbox, int __user, nr)
{
    if(is_syscall_in_sandbox(nr)){
        return 1;
    }

    return add_syscall_to_sandbox(nr);       
}

SYSCALL_DEFINE1(unregister_syscall_with_sandbox, int __user, nr)
{
    return del_syscall_from_sandbox(nr);
}

unsigned long is_proc_in_sandbox(pid_t pid){
    struct proc_in_sandbox *entry;
    list_for_each_entry(entry, &proc_in_sandbox_head, node){
        if(entry->pid == pid){
            return 1;
        }
    }
    return 0;
}

unsigned long add_proc_to_sandbox(pid_t pid){
    struct proc_in_sandbox *proc;
    proc = kmalloc(sizeof(struct proc_in_sandbox), GFP_KERNEL);
    proc->pid = pid;
    list_add(&proc->node, &proc_in_sandbox_head);
    return 0;
}

unsigned long del_proc_from_sandbox(pid_t pid){
    struct proc_in_sandbox *entry;
    list_for_each_entry(entry, &proc_in_sandbox_head, node){
        if(entry->pid == pid){
            list_del(&entry->node);
            return 0;
        }
    }
    return 1;
}

unsigned long is_syscall_in_sandbox(int nr){
    struct syscall_in_sandbox *entry;
    list_for_each_entry(entry, &syscall_in_sandbox_head, node){
        if(entry->nr == nr){
            return 1;
        }
    }
    return 0;
}

unsigned long add_syscall_to_sandbox(int nr){
    struct syscall_in_sandbox *syscall;
    syscall = kmalloc(sizeof(struct syscall_in_sandbox), GFP_KERNEL);
    syscall->nr= nr;
    list_add(&syscall->node, &syscall_in_sandbox_head);
    return 0;
}

unsigned long del_syscall_from_sandbox(int nr){
    struct syscall_in_sandbox *entry;
    list_for_each_entry(entry, &syscall_in_sandbox_head, node){
        if(entry->nr == nr){
            list_del(&entry->node);
            return 0;
        }
    }
    return 1;
}
