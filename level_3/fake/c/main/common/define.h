/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common define functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_define_h
#define _fake_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program defines.
 *
 * fake_*_d:
 *   - allocation_console: An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_pipe:    A buffer size used for processing piped data.
 *   - allocation_small:   An allocation step used for buffers that are anticipated to have small buffers.
 *   - signal_check:       Number of iterations before performing signal check in non-threaded signal handling.
 */
#ifndef _di_fake_d_
  #define fake_allocation_console_d 4
  #define fake_allocation_large_d   256
  #define fake_allocation_pipe_d    16384
  #define fake_allocation_small_d   16
  #define fake_signal_check_d       20000
#endif // _di_fake_d_

/**
 * The program defines.
 *
 * fake_signal_*_d:
 *   - check:       The normal signal check.
 *   - check_tiny:  The tiny check.
 *   - check_short: The short signal check.
 */
#ifndef _di_fake_signal_d_
  #define fake_signal_check_d       500000
  #define fake_signal_check_tiny_d  4
  #define fake_signal_check_short_d 16
#endif // _di_fake_signal_d_

/**
 * Provide common/generic definitions.
 *
 * _di_fake_common_*_d:
 *   - allocation_large:    Large allocation block size.
 *   - allocation_small:    Small allocation block size.
 *   - max_initial_buffer:  Max size to maintain the buffer (to avoid buffer bloat after an overly large allocation) (131072 = 128k).
 *   - max_operation:       Maximum number of operations.
 *   - max_recursion_depth: Maximum recursion depth.
 *   - max_stack:           Maximum stack call depth.
 */
#ifndef _di_fake_common_d_
  #define fake_common_allocation_large_d    256
  #define fake_common_allocation_small_d    16
  #define fake_common_max_initial_buffer_d  131072
  #define fake_common_max_operation_d       35
  #define fake_common_max_recursion_depth_d 65535
  #define fake_common_max_stack_d           8192
#endif // _di_fake_common_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_define_h
