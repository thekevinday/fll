/**
 * FLL - Level 3
 *
 * Project: FSS Basic List Write
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
 * basic_list_write_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_fss_basic_list_write_common_
  #define fss_basic_list_write_common_allocation_large_d 2048
  #define fss_basic_list_write_common_allocation_small_d 128
#endif // _di_fss_basic_list_write_common_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
