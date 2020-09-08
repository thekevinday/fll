/**
 * FLL - Level 2
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides file-related functionality.
 */
#ifndef _FLL_file_h
#define _FLL_file_h

// libc includes
#include <stdio.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/directory.h>
#include <level_0/file.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print file error messages.
 *
 * @param file
 *   The file to write to, such as f_type_output or f_type_error.
 * @param context
 *   The color context information to use when printing.
 * @param function_name
 *   The name of the function responsible for the error.
 * @param file_name
 *   The name of the file with the error.
 * @param status
 *   The status code representing the error.
 *   The status code should be passed through F_status_set_fine() if it contains error or warning bits.
 *
 * @return
 *   F_true if error message was printed.
 *   F_false if no error message was printed.
 */
#ifndef _di_fll_file_error_print_
  extern f_return_status fll_file_error_print(FILE *file, const fl_color_context_t context, const f_string_t function_name, const f_string_t file_name, const f_status_t status);
#endif // _di_fll_file_error_print_

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
 *   F_access_denied (with error bit) on access denied.
 *   F_access_mode (with error bit) if the current user does not have access to assign the file mode.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 */
#ifndef _di_fll_file_mode_set_all_
  extern f_return_status fll_file_mode_set_all(const f_string_t path, const mode_t mode, const f_number_unsigned_t depth_max);
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
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_access_group (with error bit) if the current user does not have access to assign the specified group.
 *   F_access_owner (with error bit) if the current user does not have access to assign the specified owner.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 */
#ifndef _di_fll_file_role_change_all_
  extern f_return_status fll_file_role_change_all(const f_string_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max);
#endif // _di_fll_file_role_change_all_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_file_h
