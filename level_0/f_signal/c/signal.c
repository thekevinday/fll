#include "signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_signal_close_
  f_return_status f_signal_close(f_signal_t *signal) {
    #ifndef _di_level_0_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!signal->id) {
      return F_data_not;
    }

    if (close(signal->id) < 0) {
      if (errno == EBADF) return F_status_set_error(F_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOSPC) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    signal->id = 0;
    return F_none;
  }
#endif // _di_f_signal_close_

#ifndef _di_f_signal_open_
  f_return_status f_signal_open(f_signal_t *signal) {
    #ifndef _di_level_0_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = signalfd(-1, &signal->set, signal->flags);

    if (result < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENODEV) return F_status_set_error(F_device);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);

      return F_status_set_error(F_failure);
    }

    signal->id = result;
    return F_none;
  }
#endif // _di_f_signal_open_

#ifndef _di_f_signal_read_
  f_return_status f_signal_read(const f_signal_t signal, struct signalfd_siginfo *information) {

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
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);

      return F_status_set_error(F_failure);
    }
    else if (result) {
      const ssize_t total = read(signal.id, information, sizeof(struct signalfd_siginfo));

      if (total < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupted);
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

#ifndef _di_f_signal_set_add_
  f_return_status f_signal_set_add(const int signal, sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigaddset(set, signal) < 0) {
      if (errno == EINVAL) {
        return F_status_set_error(F_parameter);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_add_

#ifndef _di_f_signal_set_delete_
  f_return_status f_signal_set_delete(const int signal, sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigdelset(set, signal) < 0) {
      if (errno == EINVAL) {
        return F_status_set_error(F_parameter);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_delete_

#ifndef _di_f_signal_set_empty_
  f_return_status f_signal_set_empty(sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sigemptyset(set) < 0) {
      if (errno == EINVAL) {
        return F_status_set_error(F_parameter);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_signal_set_empty_

#ifndef _di_f_signal_set_fill_
  f_return_status f_signal_set_fill(sigset_t *set) {
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

#ifndef _di_f_signal_set_get_
  f_return_status f_signal_set_get(sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    #ifdef _threadsafe_f_signal_handle
      #define f_macro_signal_set_get_sigmask pthread_sigmask
    #else
      #define f_macro_signal_set_get_sigmask sigprocmask
    #endif

    if (f_macro_signal_set_get_sigmask(0, NULL, set) < 0) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    #undef f_macro_signal_set_get_sigmask

    return F_none;
  }
#endif // _di_f_signal_set_get_

#ifndef _di_f_signal_set_handle_
  f_return_status f_signal_set_handle(const int how, const sigset_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    #ifdef _threadsafe_f_signal_handle
      #define f_macro_signal_set_get_sigmask pthread_sigmask
    #else
      #define f_macro_signal_set_get_sigmask sigprocmask
    #endif

    if (f_macro_signal_set_get_sigmask(how, set, NULL) < 0) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    #undef f_macro_signal_set_get_sigmask

    return F_none;
  }
#endif // _di_f_signal_set_handle_

#ifndef _di_f_signal_set_has_
  f_return_status f_signal_set_has(const int signal, const sigset_t *set) {
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
