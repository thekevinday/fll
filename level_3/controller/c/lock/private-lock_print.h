/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_lock_print_h
#define _PRIVATE_lock_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a r/w lock related error message, locking the print mutex during the print.
 *
 * This will ignore F_interrupt and not print any messages, if passed.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param read
 *   If TRUE, then this is for a read lock.
 *   If FALSE, then this is for a write lock.
 * @param thread
 *   The thread data.
 */
#ifndef _di_controller_lock_print_error_critical_
  extern void controller_lock_print_error_critical(const fl_print_t print, const f_status_t status, const bool read, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_print_error_critical_

/**
 * Lock the mutex and the stream.
 *
 * This is implemented as a compliment to controller_unlock_print_flush() for consistency reasons.
 *
 * @param to
 *   The file stream to lock.
 * @param thread
 *   The thread containing the print mutex to lock.
 *
 * @see flockfile()
 *
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_lock_print_
  extern void controller_lock_print(const f_file_t to, controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_print_

/**
 * Flush the stream buffer and then unlock the mutex.
 *
 * This unlocks both the stream and the mutex locks.
 *
 * Weird behavior was observed when piping data from this program.
 * The behavior appears related to how this handles locks in addition to the file streams own locking mechanisms.
 *
 * As a work-around, this performs a flush immediately before unlocking the print mutex.
 *
 * @param to
 *   The file stream to unlock and flush.
 * @param thread
 *   The thread containing the print mutex to unlock.
 *
 * @see funlockfile()
 *
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_unlock_print_flush_
  void controller_unlock_print_flush(const f_file_t to, controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_unlock_print_flush_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_lock_print_h
