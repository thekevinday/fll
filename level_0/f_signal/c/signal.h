/**
 * FLL - Level 0
 *
 * Project: Signal
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides signal processing functionality, such as signal variable handling.
 */
#ifndef _F_signal_h
#define _F_signal_h

// libc includes
#include <poll.h>
#include <signal.h>
#include <string.h>
#include <sys/signalfd.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>

// fll-0 signal includes
#include <level_0/signal-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Close an open signal descriptor.
 *
 * The signal.id is set to 0 on success.
 *
 * @param signal
 *   The signal settings.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but no descriptor was provided to close.
 *   F_descriptor (with error bit) if id is an invalid descriptor.
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see close()
 */
#ifndef _di_f_signal_close_
  extern f_return_status f_signal_close(f_signal_t *signal);
#endif // _di_f_signal_close_

/**
 * Open a signal descriptor, listening for the given set of signals.
 *
 * The signal.id is assigned with the signal descriptor on success.
 *
 * @param signal
 *   The signal settings.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_device (with error bit) if could not mount the internal inode device.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see signalfd()
 */
#ifndef _di_f_signal_open_
  extern f_return_status f_signal_open(f_signal_t *signal);
#endif // _di_f_signal_open_

/**
 * Read a current process signal, if one exists, in a non-blocking manner.
 *
 * @param signal
 *   The signal settings.
 * @param information
 *   The signal data to be populated if a signal is found during read.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_data_not on success, but no descriptor was provided to read.
 *   F_signal on success and signal found.
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_descriptor (with error bit) if the signal descriptor is invalid.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_input_output (with error bit) on I/O error.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_failure (with error bit) for any other error.
 *
 * @see poll()
 * @see read()
 */
#ifndef _di_f_signal_read_
  extern f_return_status f_signal_read(const f_signal_t signal, struct signalfd_siginfo *information);
#endif // _di_f_signal_read_

/**
 * Add a signal to the given set of signals.
 *
 * @param signal
 *   The signal to add.
 * @param set
 *   The set of signals to add to.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see sigaddset()
 */
#ifndef _di_f_signal_set_add_
  extern f_return_status f_signal_set_add(const int signal, sigset_t *set);
#endif // _di_f_signal_set_add_

/**
 * Delete a signal from a given set of signals.
 *
 * @param signal
 *   The signal to add.
 * @param set
 *   The set of signals to delete from.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see sigdelset()
 */
#ifndef _di_f_signal_set_delete_
  extern f_return_status f_signal_set_delete(const int signal, sigset_t *set);
#endif // _di_f_signal_set_delete_

/**
 * Clear a given set of signals.
 *
 * @param set
 *   The set of signals to clear.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see sigemptyset()
 */
#ifndef _di_f_signal_set_empty_
  extern f_return_status f_signal_set_empty(sigset_t *set);
#endif // _di_f_signal_set_empty_

/**
 * Add all known signals to a given set of signals.
 *
 * @param set
 *   The set of signals to fully populate.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see sigfillset()
 */
#ifndef _di_f_signal_set_fill_
  extern f_return_status f_signal_set_fill(sigset_t *set);
#endif // _di_f_signal_set_fill_

/**
 * Get the current signal set in use.
 *
 * @param set
 *   The current set of signals being handled.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see pthread_sigmask()
 */
#ifndef _di_f_signal_set_get_
  extern f_return_status f_signal_set_get(sigset_t *set);
#endif // _di_f_signal_set_get_

/**
 * Designate how to handle or not handle a set of signals designated by the set.
 *
 * @param how
 *   How to process the signal, such as SIG_BLOCK, SIG_UNBLOCK, or SIG_SETMASK.
 * @param set
 *   The set of signals to handle.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see pthread_sigmask()
 */
#ifndef _di_f_signal_set_handle_
  extern f_return_status f_signal_set_handle(const int how, const sigset_t *set);
#endif // _di_f_signal_set_handle_

/**
 * Check to see if the given signal set has a given signal.
 *
 * @param signal
 *   The signal to search for.
 * @param set
 *   The set of signals to search in.
 *
 * @return
 *   F_true if signal is found.
 *   F_false if signal is not found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see sigismember()
 */
#ifndef _di_f_signal_set_has_
  extern f_return_status f_signal_set_has(const int signal, const sigset_t *set);
#endif // _di_f_signal_set_has_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_signal_h
