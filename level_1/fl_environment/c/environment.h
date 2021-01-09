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
 * Append the given environment variable name and value pair into the given map.
 *
 * If the environment variable name is not found, then it is not added to the map.
 * If the environment variable name is found but has an empty value, then it is added to the map with an empty value.
 *
 * This does not check for uniqueness in the map.
 *
 * @param name
 *   A string representing the environment variable name.
 * @param length
 *   The length of the environment variable name string.
 * @param environment
 *   An array of maps generated from the loaded environment variable names.
 *
 * @return
 *   F_none on success.
 *   F_data_not if name length is 0.
 *   F_exist_not if name does not exist.
 *
 *   Errors (with error bit) from: f_environment_get_dynamic().
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_maps_increase_by().
 *
 * @see f_environment_get_dynamic()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_maps_increase_by()
 */
#ifndef _di_fl_environment_load_name_
  extern f_status_t fl_environment_load_name(const f_string_t name, const f_string_length_t length, f_string_maps_t *environment);
#endif // _di_fl_environment_load_name_

/**
 * Append the given environment variable name and value pairs into the given map.
 *
 * If the environment variable name is not found, then it is not added to the map.
 * If the environment variable name is found but has an empty value, then it is added to the map with an empty value.
 *
 * This does not check for uniqueness in the map.
 *
 * @param names
 *   An array of valid environment variable names.
 * @param environment
 *   An array of maps generated from the loaded environment variable names.
 *   All environment names loaded are appended to this.
 *
 * @return
 *   F_none on success.
 *   F_data_not if names.used is 0.
 *
 *   Errors (with error bit) from: f_environment_get_dynamic().
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_maps_increase_by().
 *
 * @see f_environment_get_dynamic()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_maps_increase_by()
 */
#ifndef _di_fl_environment_load_names_
  extern f_status_t fl_environment_load_names(const f_string_dynamics_t names, f_string_maps_t *environment);
#endif // _di_fl_environment_load_names_

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
 *   F_array_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_
  extern f_status_t fl_environment_path_explode(const f_string_t path, f_string_dynamics_t *paths);
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
 *   F_array_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_dynamic_
  extern f_status_t fl_environment_path_explode_dynamic(const f_string_static_t path, f_string_dynamics_t *paths);
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
 *   F_array_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_reverse_
  extern f_status_t fl_environment_path_explode_reverse(const f_string_t path, f_string_dynamics_t *paths);
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
 *   F_array_too_large (with error bit) if paths array is too large for further addressing.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_environment_path_explode_reverse_dynamic_
  extern f_status_t fl_environment_path_explode_reverse_dynamic(const f_string_static_t path, f_string_dynamics_t *paths);
#endif // _di_fl_environment_path_explode_reverse_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_environment_h
