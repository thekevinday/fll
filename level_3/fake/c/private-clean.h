/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_clean_h
#define _PRIVATE_clean_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the clean operation.
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_clean_operate_
  extern f_status_t fake_clean_operate(const fake_main_t main) f_attribute_visibility_internal;
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
  extern int fake_clean_remove_recursively_verbosely(const char *path, const struct stat *file_stat, int type, struct FTW *entity) f_attribute_visibility_internal;
#endif // !defined(_di_fake_clean_operate_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_clean_h
