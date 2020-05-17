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
#include <linux/limits.h> // defines PATH_MAX
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

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
 */
#ifndef _di_f_path_defines_
  #define f_path_separator          "/"
  #define f_path_separator_variable ":"

  #define f_path_separator_length          1
  #define f_path_separator_variable_length 1

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
 * Separate a given PATH-style string into multiple separate paths.
 *
 * @param path
 *   The string to process that is expected to follow the traditional Linux standard PATH environment variable.
 *   Each seperate path is separated by a single ':'.
 *   Must not contain NULLs except for the terminating NULL.
 *   Must be NULL terminated.
 * @param paths
 *   All of the strings exploded from PATH.
 *   Each exploded path, when not empty, is guaranteed to have a trailing '/'.
 *   Each exploded path is not NULL terminated.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_buffer_too_large (with error bit) if paths array is too large for further addressing.
 */
#ifndef _di_f_path_explode_
  extern f_return_status f_path_explode(const f_string path, f_string_dynamics *paths);
#endif // _di_f_path_explode_

/**
 * Separate a given PATH-style string into multiple separate paths.
 *
 * @param path
 *   The string to process that is expected to follow the traditional Linux standard PATH environment variable.
 *   Each seperate path is separated by a single ':'.
 *   Need not be NULL terminated.
 *   NULLs are ignored and are not copied into the exploded paths.
 * @param paths
 *   All of the strings exploded from PATH.
 *   Each exploded path, when not empty, is guaranteed to have a trailing '/'.
 *   Each exploded path is not NULL terminated.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_buffer_too_large (with error bit) if paths array is too large for further addressing.
 */
#ifndef _di_f_path_explode_dynamic_
  extern f_return_status f_path_explode_dynamic(const f_string_static path, f_string_dynamics *paths);
#endif // _di_f_path_explode_dynamic_

/**
 * Separate a given PATH-style string into multiple separate paths.
 *
 * The paths are created in reverse order.
 *
 * @param path
 *   The string to process that is expected to follow the traditional Linux standard PATH environment variable.
 *   Each seperate path is separated by a single ':'.
 *   Must not contain NULLs except for the terminating NULL.
 *   Must be NULL terminated.
 * @param paths
 *   All of the strings exploded from PATH.
 *   Each exploded path, when not empty, is guaranteed to have a trailing '/'.
 *   Each exploded path is not NULL terminated.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_buffer_too_large (with error bit) if paths array is too large for further addressing.
 */
#ifndef _di_f_path_explode_reverse_
  extern f_return_status f_path_explode_reverse(const f_string path, f_string_dynamics *paths);
#endif // _di_f_path_explode_reverse_

/**
 * Separate a given PATH-style string into multiple separate paths.
 *
 * The paths are created in reverse order.
 *
 * @param path
 *   The string to process that is expected to follow the traditional Linux standard PATH environment variable.
 *   Each seperate path is separated by a single ':'.
 *   Need not be NULL terminated.
 *   NULLs are ignored and are not copied into the exploded paths.
 * @param paths
 *   All of the strings exploded from PATH.
 *   Each exploded path, when not empty, is guaranteed to have a trailing '/'.
 *   Each exploded path is not NULL terminated.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_buffer_too_large (with error bit) if paths array is too large for further addressing.
 */
#ifndef _di_f_path_explode_reverse_dynamic_
  extern f_return_status f_path_explode_reverse_dynamic(const f_string_static path, f_string_dynamics *paths);
#endif // _di_f_path_explode_reverse_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_path_h
