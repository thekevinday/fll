#include "signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_signal_action_
  f_status_t f_signal_action(const f_signal_t signal, const struct sigaction * const action, struct sigaction *previous) {
    #ifndef _di_level_0_parameter_checking_
      if (!action && !previous) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigaction(signal.id, action, previous) == -1) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_action_

#ifndef _di_f_signal_close_
  f_status_t f_signal_close(f_signal_t * const signal) {
    #ifndef _di_level_0_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (signal->id == -1) {
      return F_data_not;
    }

    if (close(signal->id) == -1) {
      if (errno == EBADF) return F_status_set_error(F_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOSPC) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    signal->id = 0;

    return F_none;
  }
#endif // _di_f_signal_close_

#ifndef _di_f_signal_mask_
  f_status_t f_signal_mask(const int how, const sigset_t * const next, sigset_t * const current) {
    #ifndef _di_level_0_parameter_checking_
      if (!next && !current) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigprocmask(how, next, current) == -1) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_mask_

#ifndef _di_f_signal_open_
  f_status_t f_signal_open(f_signal_t * const signal) {
    #ifndef _di_level_0_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int result = signalfd(signal->id, &signal->set, signal->flags);

    if (result == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENODEV) return F_status_set_error(F_device);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    signal->id = result;

    return F_none;
  }
#endif // _di_f_signal_open_

#ifndef _di_f_signal_pause_
  f_status_t f_signal_pause(void) {

    pause();

    return F_none;
  }
#endif // _di_f_signal_pause_

#ifndef _di_f_signal_queue_
  f_status_t f_signal_queue(const pid_t id, const int signal, const union sigval value) {

    if (sigqueue(id, signal, value) == -1) {
      if (errno == EAGAIN) return F_status_set_error(F_resource_not);
      if (errno == ENOSYS) return F_status_set_error(F_support_not);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_queue_

#ifndef _di_f_signal_read_
  f_status_t f_signal_read(const f_signal_t signal, const int timeout, struct signalfd_siginfo * const information) {
    #ifndef _di_level_0_parameter_checking_
      if (!information) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct pollfd data_poll;
    memset(&data_poll, 0, sizeof(struct pollfd));

    data_poll.fd = signal.id;
    data_poll.events = POLLIN;

    const int result = poll(&data_poll, 1, timeout);

    if (result == -1) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    if (result) {
      if (data_poll.revents & POLLNVAL) {
        return F_status_set_error(F_parameter);
      }

      if (data_poll.revents & POLLHUP) {
        return F_status_set_error(F_file_closed);
      }

      if (data_poll.revents & POLLERR) {
        return F_status_set_error(F_stream);
      }

      if (data_poll.revents & POLLIN) {
        const ssize_t total = read(signal.id, information, sizeof(struct signalfd_siginfo));

        if (total == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_failure);
        }

        return F_signal;
      }
    }

    return F_none;
  }
#endif // _di_f_signal_read_

#ifndef _di_f_signal_send_
  f_status_t f_signal_send(const int signal, const pid_t process_id) {

    if (kill(process_id, signal) == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_send_

#ifndef _di_f_signal_set_add_
  f_status_t f_signal_set_add(const int signal, sigset_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigaddset(set, signal) == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_add_

#ifndef _di_f_signal_set_delete_
  f_status_t f_signal_set_delete(const int signal, sigset_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigdelset(set, signal) == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_delete_

#ifndef _di_f_signal_set_empty_
  f_status_t f_signal_set_empty(sigset_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigemptyset(set) == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_empty_

#ifndef _di_f_signal_set_fill_
  f_status_t f_signal_set_fill(sigset_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigfillset(set) == -1) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_fill_

#ifndef _di_f_signal_set_has_
  f_status_t f_signal_set_has(const int signal, const sigset_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int result = sigismember(set, signal);

    if (result == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return result ? F_true : F_false;
  }
#endif // _di_f_signal_set_has_

#ifndef _di_f_signal_suspend_
  f_status_t f_signal_suspend(const sigset_t * const mask) {
    #ifndef _di_level_0_parameter_checking_
      if (!mask) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int result = sigsuspend(mask);

    if (result == -1) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_suspend_

#ifndef _di_f_signal_wait_
  f_status_t f_signal_wait(const sigset_t * const set, siginfo_t * const information) {

    if (sigwaitinfo(set, information) == -1) {
      if (errno == EINTR) return F_interrupt;
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_wait_

#ifndef _di_f_signal_wait_until_
  f_status_t f_signal_wait_until(const sigset_t * const set, const struct timespec * timeout, siginfo_t * const information) {

    if (sigtimedwait(set, information, timeout) == -1) {
      if (errno == EAGAIN) return F_time_out;
      if (errno == EINTR) return F_interrupt;
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_wait_until_

#ifdef __cplusplus
} // extern "C"
#endif
