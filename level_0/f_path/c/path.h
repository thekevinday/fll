/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provide path-related functionality.
 */
#ifndef _F_path_h
#define _F_path_h

// Libc includes.
#include <limits.h>
#include <stdlib.h>
#include <string.h>

// If limits.h does not provide PATH_MAX, define it instead of relying on <linux/limits.h>.
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif /* PATH_MAX */

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// FLL-0 path includes.
#include <fll/level_0/path/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Change to a path.
 *
 * @param path
 *   The file path.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see chdir()
 */
#ifndef _di_f_path_change_
  extern f_status_t f_path_change(const f_string_static_t path);
#endif // _di_f_path_change_

/**
 * Change to a path at the given open file descriptor.
 *
 * @param at_id
 *   An open directory file descriptor, in which path is relative to.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see fchdir()
 */
#ifndef _di_f_path_change_at_
  extern f_status_t f_path_change_at(const int at_id);
#endif // _di_f_path_change_at_

/**
 * Get the current path.
 *
 * @param real
 *   If F_true, then get the real path and will result in an absolute path (resolving symlinks, etc..).
 *   Otherwise, this gets the path as it appears to be.
 * @param path
 *   The (allocated) file path.
 *   This will have a max size of F_path_length_max_d + 1.
 *   This will be NULL terminated at real->used + 1.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the path.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see getcwd()
 */
#ifndef _di_f_path_current_
  extern f_status_t f_path_current(const bool real, f_string_dynamic_t * const path);
#endif // _di_f_path_current_

/**
 * Ensure that the given directory path string doesn't have redundant path separators.
 *
 * The directory path is not validated to exist.
 *
 * The path to a directory has the following very basic cleanup operations performed:
 *   - Ensures that the directory always ends in a '/'.
 *   - Ensures that multiple consecutive '/' in the path are reduced to a single '/'.
 *   - Ensures that multiple consecutive '/' following './' is reduced to only './' ('.////' would become './').
 *   - Ensures that multiple consecutive '/' following '../' is reduced to only '../' ('..////' would become '../').
 *
 * The directory string will be NULL terminated after directory.used.
 *
 * @param source
 *   The south path to cleanup.
 * @param directory
 *   The cleaned up directory string.
 *   The directory string is replaced by this function.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _f_path_directory_cleanup_
  extern f_status_t f_path_directory_cleanup(const f_string_static_t source, f_string_dynamic_t * const directory);
#endif // _f_path_directory_cleanup_

/**
 * Identify whether or not a string represents a path string.
 *
 * This does not check to see if the path exists or not.
 * This does not stop on NULL (NULL characters are ignored).
 *
 * A string without any path parts that could be a path is not considered a path by this function.
 * That is to say "my_file.txt" is not a path string but "./my_file.txt" is a path string.
 *
 * @param path
 *   The string that may or may not represent a path.
 *
 * @return
 *   F_true if the string is a path string.
 *   F_false if the string is not a path string.
 *   F_data_not if the string has a length of 0 or the string is NULL.
 */
#ifndef _di_f_path_is_
  extern f_status_t f_path_is(const f_string_static_t path);
#endif // _di_f_path_is_

/**
 * Identify whether or not a string represents an absolute path string.
 *
 * This does not check to see if the path exists or not.
 * This does not stop on NULL (NULL characters are ignored).
 *
 * A string with path parts that start with '/' is an absolute path.
 * That is to say "/my_file.txt" is an absolute path string.
 *
 * @param path
 *   The string that may or may not represent an absolute path.
 *
 * @return
 *   F_true if the string is an absolute path string.
 *   F_false if the string is not an absolute path string.
 *   F_data_not if the string has a length of 0 or the string is NULL.
 */
#ifndef _di_f_path_is_absolute_
  extern f_status_t f_path_is_absolute(const f_string_static_t path);
#endif // _di_f_path_is_absolute_

/**
 * Identify whether or not a string represents a relative path string.
 *
 * This does not check to see if the path exists or not.
 * This does not stop on NULL (NULL characters are ignored).
 *
 * A string without any path parts that could be a path is considered a relative path by this function.
 * That is to say "my_file.txt" is a relative path string.
 *
 * @param path
 *   The string that may or may not represent a relative path.
 *
 * @return
 *   F_true if the string is a relative path string.
 *   F_false if the string is not a relative path string.
 *   F_data_not if the string has a length of 0 or the string is NULL.
 */
#ifndef _di_f_path_is_relative_
  extern f_status_t f_path_is_relative(const f_string_static_t path);
#endif // _di_f_path_is_relative_

/**
 * Identify whether or not a string explicitly represents a relative path string to the current working directory.
 *
 * This does not check to see if the path exists or not.
 * This does not stop on NULL (NULL characters are ignored).
 *
 * A string that is explicitly relative to the current working directory must begin with one of "./" or "../".
 *
 * This does not return true for paths that are implicitly relative, such as "abc".
 *
 * @param path
 *   The string that may or may not represent a relative path.
 *
 * @return
 *   F_true if the string is a relative path string.
 *   F_false if the string is not a relative path string.
 *   F_data_not if the string has a length of 0 or the string is NULL.
 */
#ifndef _di_f_path_is_relative_current_
  extern f_status_t f_path_is_relative_current(const f_string_static_t path);
#endif // _di_f_path_is_relative_current_

/**
 * Get the real path for the given path.
 *
 * This does check to see if the path exists or not (path must exist).
 * This processes all relative parts.
 * This processes all symbolic links.
 * This has a max size of F_path_length_max_d + 1.
 *
 * @param path
 *   The source path to determine what the real path is.
 *   This is a NULL terminated string.
 * @param real
 *   The (allocated) real file path.
 *   This will have a max size of F_path_length_max_d + 1.
 *   This will be NULL terminated at real->used + 1.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the path.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_found_not if the path was not found.
 *   F_failure (with error bit) for any other error.
 *
 * @see realpath()
 */
#ifndef _di_f_path_real_
  extern f_status_t f_path_real(const f_string_static_t path, f_string_dynamic_t * const real);
#endif // _di_f_path_real_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_path_h
