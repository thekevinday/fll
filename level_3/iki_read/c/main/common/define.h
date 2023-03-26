/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common define types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_define_h
#define _iki_read_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program defines.
 *
 * iki_read_*_d:
 *   - allocation_console: An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_small:   An allocation step used for buffers that are anticipated to have small buffers.
 *   - block_max:          The max block read size before checking for interrupt.
 *   - block_read_small:   The block read size for small files.
 *   - block_read_large:   The block read size for large files.
 *   - signal_check:       Number of iterations before performing signal check in non-threaded signal handling.
 */
#ifndef _di_iki_read_d_
  #define iki_read_allocation_console_d 4
  #define iki_read_allocation_large_d   256
  #define iki_read_allocation_small_d   16
  #define iki_read_block_max            16777216
  #define iki_read_block_read_small     8192
  #define iki_read_block_read_large     65536
  #define iki_read_signal_check_d       20000
#endif // _di_iki_read_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_define_h
