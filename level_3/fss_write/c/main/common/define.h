/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_common_define_h
#define _fss_write_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program default defines.
 *
 * fss_write_*:
 *   - allocation_console: An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_small:   An allocation step used for buffers that are anticipated to have small buffers.
 *   - signal_check:       Number of iterations before performing signal check in non-threaded signal handling.
 */
#ifndef _di_fss_write_d_
  #define fss_write_allocation_console_d 4
  #define fss_write_allocation_large_d   2048
  #define fss_write_allocation_small_d   128
  #define fss_write_signal_check_d       20000
#endif // _di_fss_write_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_common_define_h
