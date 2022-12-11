/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide common/generic definitions.
 *
 * iki_read_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 *
 * iki_read_block_*:
 *   - max:        The max block read size before checking for interrupt.
 *   - read_small: The block read size for small files.
 *   - read_large: The block read size for large files.
 */
#ifndef _di_iki_read_common_
  #define iki_read_common_allocation_large_d 256
  #define iki_read_common_allocation_small_d 16

  #define iki_read_block_max        16777216
  #define iki_read_block_read_small 8192
  #define iki_read_block_read_large 65536
#endif // _di_iki_read_common_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
