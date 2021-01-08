/**
 * FLL - Level 2
 *
 * Project: Environment
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides environment-related functionality.
 */
#ifndef _FLL_environment_h
#define _FLL_environment_h

// libc includes
#include <stdio.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/environment.h>

// fll-1 includes
#include <level_1/string.h>

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
#ifndef _di_fll_environment_load_name_
  extern f_status_t fll_environment_load_name(const f_string_t name, const f_string_length_t length, f_string_maps_t *environment);
#endif // _di_fll_environment_load_name_

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
#ifndef _di_fll_environment_load_names_
  extern f_status_t fll_environment_load_names(const f_string_dynamics_t names, f_string_maps_t *environment);
#endif // _di_fll_environment_load_names_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_environment_h
