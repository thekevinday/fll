#include "mock-signal.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_close(int fd) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_kill(pid_t pid, int sig) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_pause(void) {

  return -1;
}

int __wrap_poll(struct pollfd *fds, nfds_t nfds, int timeout) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  fds->revents = mock_type(short);

  return mock_type(int);
}

ssize_t __wrap_read(int fd, void *buf, size_t count) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_sigaddset(sigset_t *set, int signum) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigdelset(sigset_t *set, int signum) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigemptyset(sigset_t *set) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigfillset(sigset_t *set) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigismember(const sigset_t *set, int signum) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_signalfd(int fd, const sigset_t *mask, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigqueue(pid_t pid, int sig, const union sigval value) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigsuspend(const sigset_t *mask) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigtimedwait(const sigset_t *set, siginfo_t *info, const struct timespec *timeout) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sigwaitinfo(const sigset_t *set, siginfo_t *info) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif
