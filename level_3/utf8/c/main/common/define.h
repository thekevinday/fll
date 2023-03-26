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
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_utf8_default_d_
  #define utf8_default_allocation_step_d 16
#endif // _di_utf8_default_d_

/**
 * The program defines.
 *
 * utf8_*_d:
 *   - allocation_console: An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_small:   An allocation step used for buffers that are anticipated to have small buffers.
 *   - signal_check:       Number of iterations before performing signal check in non-threaded signal handling.
 */
#ifndef _di_utf8_d_
  #define utf8_allocation_console_d 4
  #define utf8_allocation_large_d   256
  #define utf8_allocation_small_d   16
  #define utf8_signal_check_d       20000
#endif // _di_utf8_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_define_h
