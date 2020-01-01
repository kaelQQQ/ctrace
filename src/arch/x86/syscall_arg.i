void get_syscall_args(tinfo *ti, struct user_regs_struct *regs) {
    ti->regs[0] = regs->rdi;
    ti->regs[1] = regs->rsi;
    ti->regs[2] = regs->rdx;
    ti->regs[3] = regs->r10;
    ti->regs[4] = regs->r8;
    ti->regs[5] = regs->r9;
    ti->syscall = regs->orig_rax;
}

void get_syscall_ret(tinfo *ti, struct user_regs_struct *regs) {
    ti->ret = regs->rax;
}
