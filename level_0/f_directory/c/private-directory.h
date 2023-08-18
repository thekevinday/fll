/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides operations for directory handling.
 */
#ifndef _PRIVATE_F_directory_h
#define _PRIVATE_F_directory_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_directory_create().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The file path to the directory.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_okay on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see f_directory_create()
 * @see f_directory_touch()
 */
#if !defined(_di_f_directory_create_) || !defined(_di_f_directory_touch_)
  extern f_status_t private_f_directory_create(const f_string_static_t path, const mode_t mode) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_directory_create_) || !defined(_di_f_directory_touch_)

/**
 * Private implementation of f_directory_create_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The file path to the directory.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_okay on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see f_directory_create_at()
 * @see f_directory_touch_at()
 */
#if !defined(_di_f_directory_create_at_) || !defined(_di_f_directory_touch_at_)
  extern f_status_t private_f_directory_create_at(const int at_id, const f_string_static_t path, const mode_t mode) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_directory_create_at_) || !defined(_di_f_directory_touch_at_)

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
 */
#if !defined(_di_f_directory_remove_)
  extern int private_f_directory_remove_recursively(const char * const path, const struct stat *file_stat, int type, struct FTW *entity) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_directory_remove_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_directory_h
