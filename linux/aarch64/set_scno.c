#ifndef NT_ARM_SYSTEM_CALL
# define NT_ARM_SYSTEM_CALL 0x404
#endif

static int
arch_set_scno(struct tcb *tcp, long scno)
{
	unsigned int n = (uint16_t) scno;
	const struct iovec io = {
		.iov_base = &n,
		.iov_len = sizeof(n)
	};
	int rc = ptrace(PTRACE_SETREGSET, tcp->pid, NT_ARM_SYSTEM_CALL, &io);
	if (rc && errno != ESRCH)
		perror_msg("arch_set_scno: NT_ARM_SYSTEM_CALL pid:%d scno:%#x",
			   tcp->pid, n);
	return rc;
}