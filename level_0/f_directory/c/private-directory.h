/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides operations for directory handling.
 */
#ifndef _PRIVATE_F_directory_h
#define _PRIVATE_F_directory_h

#ifdef __cplusplus
extern "C" {
#endif

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
#if !defined(_di_f_directory_remove_)
  extern int private_f_directory_remove_recursively(const char *path, const struct stat *file_stat, int type, struct FTW *entity) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_directory_remove_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_directory_h
