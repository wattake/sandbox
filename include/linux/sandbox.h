
struct proc_in_sandbox{
    pid_t pid;
    struct list_head node;
};

static LIST_HEAD(proc_in_sandbox_head);

struct syscall_in_sandbox{
    int nr;
    struct list_head node;
};

static LIST_HEAD(syscall_in_sandbox_head);

unsigned long is_proc_in_sandbox(pid_t pid);
unsigned long add_proc_to_sandbox(pid_t pid);
unsigned long del_proc_from_sandbox(pid_t pid);

unsigned long is_syscall_in_sandbox(int nr);
unsigned long add_syscall_to_sandbox(int nr);
unsigned long del_syscall_from_sandbox(int nr);