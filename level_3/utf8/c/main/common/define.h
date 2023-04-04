/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common define types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_define_h
#define _utf8_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program allocation defines.
 *
 * utf8_allocation_*_d:
 *   - console: An allocation step used for small buffers specifically for console parameter.
 *   - large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - pipe:    A buffer size used for processing piped data.
 *   - small:   An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_utf8_allocation_d_
  #define utf8_allocation_console_d 4
  #define utf8_allocation_large_d   256
  #define utf8_allocation_pipe_d    16384
  #define utf8_allocation_small_d   16
#endif // _di_utf8_allocation_d_

/**
 * The program signal defines.
 *
 * utf8_signal_*_d:
 *   - check:          Number of iterations before performing signal check in non-threaded signal handling.
 *   - check_failsafe: When using threads, how many consecutive failures to check signal before aborting (as a recursion failsafe).
 *   - check_tiny:     The tiny check.
 *   - check_short:    The short signal check.
 */
#ifndef _di_utf8_signal_d_
  #define utf8_signal_check_d          500000
  #define utf8_signal_check_failsafe_d 20000
  #define utf8_signal_check_tiny_d     4
  #define utf8_signal_check_short_d    16
#endif // _di_utf8_signal_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_define_h
