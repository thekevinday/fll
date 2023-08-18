/**
 * FLL - Level 2
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides file-related functionality.
 */
#ifndef _FLL_file_h
#define _FLL_file_h

// Libc includes.
#include <stdio.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/color.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Change mode of a given file or directory at the specified path.
 *
 * This does not set mode based on umask(), be sure to apply umask if so desired.
 * (such as: mode & ~mask).
 *
 * If the file is a directory then recurse into that directory and apply mode to all files within.
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
 *
 * @return
 *   F_okay on success.
 *   F_data_not if path.used is 0.
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
 *   F_failure (with error bit) for any other error.
 *
 *   Errors (with error bit) from: f_file_mode_set().
 *   Errors (with error bit) from: f_directory_exists().
 *   Errors (with error bit) from: fl_directory_list().
 */
#ifndef _di_fll_file_mode_set_all_
  extern f_status_t fll_file_mode_set_all(const f_string_static_t path, const bool dereference, const mode_t mode, const f_number_unsigned_t depth_max);
#endif // _di_fll_file_mode_set_all_

/**
 * Change owner and/or group of a given file at the specified path.
 *
 * At least one of uid or gid must not be -1.
 *
 * If the file is a directory then recurse into that directory and apply mode to all files within.
 *
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 *   Set to -1 to not change.
 * @param gid
 *   The new group id to use.
 *   Set to -1 to not change.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param depth_max
 *   The max recursion depth.
 *
 * @return
 *   F_okay on success.
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
 *
 *   Errors (with error bit) from: f_directory_is().
 *   Errors (with error bit) from: f_file_role_change().
 *   Errors (with error bit) from: fl_directory_list().
 */
#ifndef _di_fll_file_role_change_all_
  extern f_status_t fll_file_role_change_all(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max);
#endif // _di_fll_file_role_change_all_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_file_h
