/**
 * FLL - Level 0
 *
 * Project: Signal
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides signal processing functionality, such as signal variable handling.
 */
#ifndef _F_signal_h
#define _F_signal_h

// Libc includes.
#include <poll.h>
#include <signal.h>
#include <string.h>
#include <sys/signalfd.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>

// FLL-0 signal includes.
#include <fll/level_0/signal/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get or set the signal action handlers.
 *
 * @param signal
 *   The signal settings.
 * @param action
 *   (optional) The signal action to use.
 *   Set to NULL to not use.
 *   Both action and previous may not be NULL.
 * @param previous
 *   (optional) The previous signal action.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_buffer (with error bit) if the buffer is invalid (action or previous point to invalid memory).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigaction()
 */
#ifndef _di_f_signal_action_
  extern f_status_t f_signal_action(const f_signal_t signal, const struct sigaction * const action, struct sigaction *previous);
#endif // _di_f_signal_action_

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
 *
 *   F_descriptor (with error bit) if id is an invalid descriptor.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see close()
 */
#ifndef _di_f_signal_close_
  extern f_status_t f_signal_close(f_signal_t * const signal);
#endif // _di_f_signal_close_

/**
 * Get or assign the current signal set in use.
 *
 * Either set or previous may be NULL but not both (at least one is required).
 *
 * @param how
 *   How to handle the signal.
 *   Set this to 0 when only trying to get the current signal set.
 * @param next
 *   (optional) The new set of signals to handle.
 *   Set to NULL to not use.
 * @param current
 *   (optional) The current set of signals being handled.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigprocmask()
 */
#ifndef _di_f_signal_mask_
  extern f_status_t f_signal_mask(const int how, const sigset_t * const next, sigset_t * const current);
#endif // _di_f_signal_mask_

/**
 * Open a signal descriptor, listening for the given set of signals.
 *
 * The signal.id is assigned with the signal descriptor on success.
 *
 * @param signal
 *   The signal settings.
 *
 *   If signal.id is -1, then a new file descriptor is created.
 *   Otherwise, signal.id is used as the file descriptor.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_device (with error bit) if could not mount the internal inode device.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see signalfd()
 */
#ifndef _di_f_signal_open_
  extern f_status_t f_signal_open(f_signal_t * const signal);
#endif // _di_f_signal_open_

/**
 * Pause the current process until a signal is received.
 *
 * @return
 *   The received signal.
 *
 * @see pause()
 */
#ifndef _di_f_signal_pause_
  extern f_status_t f_signal_pause(void);
#endif // _di_f_signal_pause_

/**
 * Send the signal and value to the given process.
 *
 * @param id
 *   The PID to signal.
 * @param signal
 *   The signal to send to the thread.
 * @param value
 *   The signal value to send.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_found_not (with error bit) if the given PID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if the max signals is reached.
 *   F_supported_not (with error bit) if this action is not supported by the current OS.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigqueue()
 */
#ifndef _di_f_signal_queue_
  extern f_status_t f_signal_queue(const pid_t id, const int signal, const union sigval value);
#endif // _di_f_signal_queue_

/**
 * Read a current process signal, if one exists.
 *
 * @param signal
 *   The signal settings.
 * @param timeout
 *   Block for the number of milliseconds, waiting for a signal.
 *   A value of 0 means that this will not block.
 * @param information
 *   The signal data to be populated if a signal is found during read.
 *
 * @return
 *   F_none on success but no signal found.
 *   F_data_not on success, but no descriptor was provided to read.
 *   F_signal on success and signal found.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_descriptor (with error bit) if the signal descriptor is invalid.
 *   F_file_closed (with error bit) if the signal descriptor stream is closed.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_stream (with error bit) when the poll() returns POLLERR (file stream error).
 *   F_input_output (with error bit) on I/O error.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see poll()
 * @see read()
 */
#ifndef _di_f_signal_read_
  extern f_status_t f_signal_read(const f_signal_t signal, const int timeout, struct signalfd_siginfo * const information);
#endif // _di_f_signal_read_

/**
 * Send a signal to a process.
 *
 * @param signal
 *   The signal to send
 * @param process_id
 *   The process id (PID) that will receive the signal.
 *   This may also be a process group id.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to send signals to the given process.
 *   F_found_not (with error bit) if the given process was not found.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see kill()
 */
#ifndef _di_f_signal_send_
  extern f_status_t f_signal_send(const int signal, const pid_t process_id);
#endif // _di_f_signal_send_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigaddset()
 */
#ifndef _di_f_signal_set_add_
  extern f_status_t f_signal_set_add(const int signal, sigset_t * const set);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigdelset()
 */
#ifndef _di_f_signal_set_delete_
  extern f_status_t f_signal_set_delete(const int signal, sigset_t * const set);
#endif // _di_f_signal_set_delete_

/**
 * Clear a given set of signals.
 *
 * @param set
 *   The set of signals to clear.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigemptyset()
 */
#ifndef _di_f_signal_set_empty_
  extern f_status_t f_signal_set_empty(sigset_t * const set);
#endif // _di_f_signal_set_empty_

/**
 * Add all known signals to a given set of signals.
 *
 * @param set
 *   The set of signals to fully populate.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigfillset()
 */
#ifndef _di_f_signal_set_fill_
  extern f_status_t f_signal_set_fill(sigset_t * const set);
#endif // _di_f_signal_set_fill_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigismember()
 */
#ifndef _di_f_signal_set_has_
  extern f_status_t f_signal_set_has(const int signal, const sigset_t * const set);
#endif // _di_f_signal_set_has_

/**
 * Suspend the current process until one of the provided signals is received.
 *
 * @param mask
 *   The signal mask.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_buffer (with error bit) if the mask is pointing to invalid memory.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigsuspend()
 */
#ifndef _di_f_signal_suspend_
  extern f_status_t f_signal_suspend(const sigset_t * const mask);
#endif // _di_f_signal_suspend_

/**
 * Wait until any signal in a set of signals is received.
 *
 * @param set
 *   The set of signals to wait for.
 * @param information
 *   (optional) The resulting signal information.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none if signal is found.
 *
 *   F_interrupt (with error bit) if interrupted by a signal other than one specified in the signal set.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigwaitinfo()
 */
#ifndef _di_f_signal_wait_
  extern f_status_t f_signal_wait(const sigset_t * const set, siginfo_t * const information);
#endif // _di_f_signal_wait_

/**
 * Wait until any signal in a set of signals is received until the given time out is reached.
 *
 * @param set
 *   The set of signals to wait for.
 * @param timeout
 *   The amount of time to wait.
 * @param information
 *   (optional) The resulting signal information.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none if signal is found before time out.
 *   F_time_out if no signal is find by the time out.
 *
 *   F_interrupt (with error bit) if interrupted by a signal other than one specified in the signal set.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sigtimedwait()
 */
#ifndef _di_f_signal_wait_until_
  extern f_status_t f_signal_wait_until(const sigset_t * const set, const struct timespec *timeout, siginfo_t * const information);
#endif // _di_f_signal_wait_until_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_signal_h
