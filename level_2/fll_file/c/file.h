/**
 * FLL - Level 2
 *
 * Project: File
 * API Version: 0.5
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
 * @param mode
 *   The new mode to use.
 * @param depth_max
 *   The max recursion depth.
 *
 * @return
 *   F_none on success.
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
  extern f_status_t fll_file_mode_set_all(const f_string_static_t path, const mode_t mode, const f_number_unsigned_t depth_max);
#endif // _di_fll_file_mode_set_all_

/**
 * Move a file.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * This attempts to rename a file but if the file is on another file system then it tries to clone the file or directory.
 * If the file or directory is cloned, then the original is deleted after a successful copy.
 *
 * When this calls the additional functions, if the clone succeeds but the remove fails the source may exist.
 * Therefore, if there is an error during remove, then the file should be checked for existence and possibly be manually removed.
 *
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 * @param recurse
 *   The directory recurse data.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_empty_not (with error bit) if the destination is a non-empty directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_file_type_directory (with error bit) if destination is a directory but source is not.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_link (with error bit) if source or destination has the maxiumum associated links.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error, failures might be populated with individual status codes.
 *
 *   Errors (with error bit) from: f_directory_remove_custom().
 *   Errors (with error bit) from: f_file_is().
 *   Errors (with error bit) from: f_file_remove().
 *   Errors (with error bit) from: f_file_rename().
 *   Errors (with error bit) from: fl_directory_clone().
 *
 * @see f_directory_remove()
 * @see f_directory_remove_custom()
 * @see f_file_is()
 * @see f_file_remove()
 * @see f_file_rename()
 * @see fl_directory_clone()
 */
#ifndef _di_fll_file_move_
  extern f_status_t fll_file_move(const f_string_static_t source, const f_string_static_t destination, const fl_directory_recurse_t recurse);
#endif // _di_fll_file_move_

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
