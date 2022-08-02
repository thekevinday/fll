/**
 * FLL - Level 2
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides structures and data types for a file I/O.
 * Provides operations for opening/closing files.
 */
#ifndef _PRIVATE_FLL_file_h
#define _PRIVATE_FLL_file_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fll_file_mode_set_all().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param mode
 *   The new mode to use.
 * @param depth_max
 *   The max recursion depth.
 * @param depth
 *   The current depth.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_access_mode (with error bit) if the current user does not have access to assign the file mode.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_recurse (with error bit) if recursion failed, due to max depth reached.
 *   F_failure (with error bit) for any other error.
 */
#if !defined(_di_fll_file_mode_set_all_)
  extern f_status_t private_fll_file_mode_set_all(const f_string_static_t path, const bool dereference, const mode_t mode, const f_number_unsigned_t depth_max, const f_number_unsigned_t depth) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_file_mode_set_all_)

/**
 * Private implementation of fll_file_role_change_all().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 * @param gid
 *   The new group id to use.
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param depth_max
 *   The max recursion depth.
 * @param depth
 *   The current depth.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_access_group (with error bit) if the current user does not have access to assign the specified group.
 *   F_access_owner (with error bit) if the current user does not have access to assign the specified owner.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 */
#if !defined(_di_fll_file_role_change_all_)
  extern f_status_t private_fll_file_role_change_all(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max, const f_number_unsigned_t depth) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_file_role_change_all_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_file_h
