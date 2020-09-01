/**
 * FLL - Level 1
 *
 * Project: Environment
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides environment processing functionality, such as environment variable handling.
 */
#ifndef _FL_environment_h
#define _FL_environment_h

#include <stdio.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/environment.h>
#include <level_0/path.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 *   F_none on success.
 *   F_buffer_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_
  extern f_return_status fl_environment_path_explode(const f_string_t path, f_string_dynamics_t *paths);
#endif // _di_fl_environment_path_explode_

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
 *   F_none on success.
 *   F_buffer_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_dynamic_
  extern f_return_status fl_environment_path_explode_dynamic(const f_string_static_t path, f_string_dynamics_t *paths);
#endif // _di_fl_environment_path_explode_dynamic_

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
 *   F_none on success.
 *   F_buffer_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_reverse_
  extern f_return_status fl_environment_path_explode_reverse(const f_string_t path, f_string_dynamics_t *paths);
#endif // _di_fl_environment_path_explode_reverse_

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
 *   F_none on success.
 *   F_buffer_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_reverse_dynamic_
  extern f_return_status fl_environment_path_explode_reverse_dynamic(const f_string_static_t path, f_string_dynamics_t *paths);
#endif // _di_fl_environment_path_explode_reverse_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_environment_h
