/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_clean_h
#define _PRIVATE_clean_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the clean operation.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_clean_operate_
  extern f_status_t fake_clean_operate(fake_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fake_clean_operate_

/**
 * A special function intended to be used directly by nftw().
 *
 * This is intended to be used by the specified function as a function pointer and therefore follows the required structure.
 *
 * This is essentially a wrapper to remove().
 *
 * @param path
 *   The file path.
 * @param file_stat
 *   The file stat.
 * @param type
 *   The file type.
 * @param entity
 *   The FTW entity.
 *
 * @return
 *   0 on success.
 *   -1 on failure.
 *   Check errno for details.
 *
 * @see f_directory_remove()
 * @see nftw()
 * @see remove()
 */
#if !defined(_di_fake_clean_operate_)
  extern int fake_clean_remove_recursively_verbosely(const char * const path, const struct stat *file_stat, int type, struct FTW *entity) F_attribute_visibility_internal_d;
#endif // !defined(_di_fake_clean_operate_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_clean_h
