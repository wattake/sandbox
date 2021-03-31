#include<linux/kernel.h>
#include<linux/syscalls.h>

SYSCALL_DEFINE0(retconst)
{
    return 123;
}

SYSCALL_DEFINE0(hello)
{
    printk("Hello World.\n");
    return 0;
}

SYSCALL_DEFINE1(ptr5000, int __user*, val)
{
    int buf = 0;   
    int tmp = 0;
    if(copy_from_user(&buf, val, sizeof(buf))!=0){
        printk("copy_from_user err\n");
        return buf;
    }
    tmp = buf; 
    buf = 5000;
    if(copy_to_user(val, &buf, sizeof(buf))!=0){
        printk("copy_to_user err\n");
        return buf;
    }
    return tmp;
}

SYSCALL_DEFINE1(argptr, void *, ptr)
{
    if(ptr){
        return 0;
    }

    printk("err\n");    
    return 1;
}

SYSCALL_DEFINE0(getstate)
{
    struct task_struct *tsk = current;
    return tsk->state;
}
