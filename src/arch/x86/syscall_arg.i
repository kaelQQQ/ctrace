void get_syscall_args(ctinfo *ci, struct user_regs_struct *regs) {
    ci->regs[0] = regs->rdi;
    ci->regs[1] = regs->rsi;
    ci->regs[2] = regs->rdx;
    ci->regs[3] = regs->r10;
    ci->regs[4] = regs->r8;
    ci->regs[5] = regs->r9;
    ci->syscall = regs->orig_rax;
}

void get_syscall_ret(ctinfo *ci, struct user_regs_struct *regs) {
    ci->ret = regs->rax;
}
