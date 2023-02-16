/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common defines.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_define_h
#define _fake_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/***
 * Default allocations.
 *
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 *
 * fake_default_allocation_*_d:
 *   - large: A buffer size used for large allocations.
 *   - pipe:  A buffer size used for processing piped data.
 *   - small: A buffer size used for small allocations.
 */
#ifndef _di_fake_default_d_
  #define fake_default_allocation_large_d 64
  #define fake_default_allocation_pipe_d  16384
  #define fake_default_allocation_small_d 8
#endif // _di_fake_default_d_

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
