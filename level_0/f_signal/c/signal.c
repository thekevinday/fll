#include "signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_signal_close_
  f_status_t f_signal_close(f_signal_t *signal) {
    #ifndef _di_level_0_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!signal->id) {
      return F_data_not;
    }

    if (close(signal->id) < 0) {
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

#ifndef _di_f_signal_open_
  f_status_t f_signal_open(f_signal_t *signal) {
    #ifndef _di_level_0_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = signalfd(-1, &signal->set, signal->flags);

    if (result < 0) {
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

#ifndef _di_f_signal_read_
  f_status_t f_signal_read(const f_signal_t signal, struct signalfd_siginfo *information) {

    if (!signal.id) {
      return F_data_not;
    }

    struct pollfd data_poll;
    memset(&data_poll, 0, sizeof(struct pollfd));

    data_poll.fd = signal.id;
    data_poll.events = POLLIN;

    struct pollfd polls[] = { data_poll };

    const int result = poll(polls, 1, 0);

    if (result < 0) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }
    else if (result) {
      const ssize_t total = read(signal.id, information, sizeof(struct signalfd_siginfo));

      if (total < 0) {
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

    return F_none;
  }
#endif // _di_f_signal_read_

#ifndef _di_f_signal_send_
  f_status_t f_signal_send(const int signal, const pid_t process_id) {

    if (kill(process_id, signal) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_send_

#ifndef _di_f_signal_set_add_
  f_status_t f_signal_set_add(const int signal, sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigaddset(set, signal) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_add_

#ifndef _di_f_signal_set_delete_
  f_status_t f_signal_set_delete(const int signal, sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigdelset(set, signal) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_delete_

#ifndef _di_f_signal_set_empty_
  f_status_t f_signal_set_empty(sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigemptyset(set) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_empty_

#ifndef _di_f_signal_set_fill_
  f_status_t f_signal_set_fill(sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigfillset(set) < 0) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_fill_

#ifndef _di_f_signal_mask_
  f_status_t f_signal_mask(const int how, const sigset_t *next, sigset_t *current) {
    #ifndef _di_level_0_parameter_checking_
      if (!next && !current) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigprocmask(how, next, current) < 0) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_mask_

#ifndef _di_f_signal_queue_
  f_status_t f_signal_queue(const pid_t id, const int signal, const union sigval value) {

    if (sigqueue(id, signal, value) < 0) {
      if (errno == EAGAIN) return F_status_set_error(F_resource_not);
      if (errno == ENOSYS) return F_status_set_error(F_supported_not);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_queue_

#ifndef _di_f_signal_set_has_
  f_status_t f_signal_set_has(const int signal, const sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int result = sigismember(set, signal);

    if (result < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return result ? F_true : F_false;
  }
#endif // _di_f_signal_set_has_

#ifdef __cplusplus
} // extern "C"
#endif
