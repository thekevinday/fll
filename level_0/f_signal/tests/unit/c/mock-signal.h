/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the signal project.
 */
#ifndef _MOCK__signal_h
#define _MOCK__signal_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/signal.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
extern int __wrap_close(int fd);
extern int __wrap_kill(pid_t pid, int sig);
extern int __wrap_pause(void);
extern int __wrap_poll(struct pollfd *fds, nfds_t nfds, int timeout);
extern ssize_t __wrap_read(int fd, void *buf, size_t count);
extern int __wrap_sigaddset(sigset_t *set, int signum);
extern int __wrap_sigdelset(sigset_t *set, int signum);
extern int __wrap_sigemptyset(sigset_t *set);
extern int __wrap_sigfillset(sigset_t *set);
extern int __wrap_sigismember(const sigset_t *set, int signum);
extern int __wrap_signalfd(int fd, const sigset_t *mask, int flags);
extern int __wrap_sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
extern int __wrap_sigqueue(pid_t pid, int sig, const union sigval value);
extern int __wrap_sigsuspend(const sigset_t *mask);
extern int __wrap_sigtimedwait(const sigset_t *set, siginfo_t *info, const struct timespec *timeout);
extern int __wrap_sigwaitinfo(const sigset_t *set, siginfo_t *info);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__signal_h
