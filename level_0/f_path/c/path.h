/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide path-related functionality.
 */
#ifndef _F_path_h
#define _F_path_h

// libc includes
#include <limits.h>
#include <linux/limits.h> // defines PATH_MAX
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Standard path defines.
 *
 * The path separator, intended to be represented as a single character.
 * The path separator length must be a 1-byte wide character.
 *
 * The path variable separator is intended to represent the path separator used in the PATH environment variable.
 * PATH="/bin:/usr/bin", the path variable separator is ':'.
 * The path variable separator must be a 1-byte wide character.
 *
 * The path extension separator is for the separator that separates the main part of a file path with its extension (which is generally a '.').
 */
#ifndef _di_f_path_defines_
  #define f_path_separator          "/"
  #define f_path_separator_variable ":"

  #define f_path_separator_length          1
  #define f_path_separator_variable_length 1

  #define f_path_extension_separator "."

  #define f_path_extension_separator_length 1

  #define f_path_environment         "PATH"
  #define f_path_home_wildcard       "~"
  #define f_path_present_working     "PWD"
  #define f_path_present_working_old "OLDPWD"

  #define f_path_environment_length         4
  #define f_path_home_wildcard_length       1
  #define f_path_present_working_length     3
  #define f_path_present_working_old_length 6

  #define f_path_max PATH_MAX
#endif // _di_f_path_defines_

/**
 * Change to a path.
 *
 * @param path
 *   The file path.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see chdir()
 */
#ifndef _di_f_path_change_
  extern f_return_status f_path_change(const f_string_t path);
#endif // _di_f_path_change_

/**
 * Change to a path at the given open file descriptor.
 *
 * @param at_id
 *   An open directory file descriptor, in which path is relative to.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see fchdir()
 */
#ifndef _di_f_path_change_at_
  extern f_return_status f_path_change_at(const int at_id);
#endif // _di_f_path_change_at_

/**
 * Get the current path.
 *
 * @param real
 *   If F_true, then get the real path and will result in an absolute path (resolving symlinks, etc..).
 *   Otherwise, this gets the path as it appears to be.
 * @param path
 *   The (allocated) file path.
 *   This will have a max size of f_path_max + 1.
 *   This will be NULL terminated at real->used + 1.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the path.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see getcwd()
 */
#ifndef _di_f_path_current_
  extern f_return_status f_path_current(const bool real, f_string_dynamic_t *path);
#endif // _di_f_path_current_

/**
 * Get the real path for the given path.
 *
 * This does check to see if the path exists or not (path must exist).
 * This processes all relative parts.
 * This processes all symbolic links.
 * This has a max size of f_path_max + 1.
 *
 * @param path
 *   The source path to determine what the real path is.
 *   This is a NULL terminated string.
 * @param real
 *   The (allocated) real file path.
 *   This will have a max size of f_path_max + 1.
 *   This will be NULL terminated at real->used + 1.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the path.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see realpath()
 */
#ifndef _di_f_path_real_
  extern f_return_status f_path_real(const f_string_t path, f_string_dynamic_t *real);
#endif // _di_f_path_real_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_path_h
