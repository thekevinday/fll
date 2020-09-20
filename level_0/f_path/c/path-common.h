/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project path.
 *
 * This is auto-included by path.h and should not need to be explicitly included.
 */
#ifndef _F_path_common_h
#define _F_path_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Standard path defines.
 *
 * The path separator, intended to be represented as a single character.
 * The path separator length must be a 1-byte wide character.
 *
 * The "current" path separator "." represents a part of the path that potentially may represent the current path.
 * This is expected to be followed by a separator "/".
 *
 * The path variable separator is intended to represent the path separator used in the PATH environment variable.
 * PATH="/bin:/usr/bin", the path variable separator is ':'.
 * The path variable separator must be a 1-byte wide character.
 *
 * The path extension separator is for the separator that separates the main part of a file path with its extension (which is generally a '.').
 */
#ifndef _di_f_path_defines_
  #define f_path_separator          "/"
  #define f_path_separator_current  "."
  #define f_path_separator_variable ":"

  #define f_path_separator_length          1
  #define f_path_separator_current_length  1
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_path_common_h
