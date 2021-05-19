/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 */
#ifndef _di_iki_read_common_
  #define iki_read_common_allocation_large 256
  #define iki_read_common_allocation_small 16
#endif // _di_iki_read_common_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
