/**
 * FLL - Level 0
 *
 * Project: Environment
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides environment processing functionality, such as environment variable handling.
 */
#ifndef _F_environment_h
#define _F_environment_h

// Libc includes.
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef _di_libcap_
  #include <sys/capability.h>
#endif // _di_libcap_

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// FLL-0 environment includes.
#include <fll/level_0/environment/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Delete all environment variables.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure.
 *
 * @see clearenv()
 */
#ifndef _di_f_environment_clear_
  extern f_status_t f_environment_clear(void);
#endif // _di_f_environment_clear_

/**
 * Get a single environment variable.
 *
 * The variable is copied into a new dynamically allocated string and is safe to alter.
 *
 * @param name
 *   The name of the environment variable to check the existence of.
 *   The name string must not contain the '=' character.
 *   The name must be NULL terminated.
 *
 * @return
 *   F_data_not if name.used is 0.
 *   F_true on success and environment variable exists.
 *   F_false on success and environment variable does not exist.
 *
 * @see getenv()
 */
#ifndef _di_f_environment_exists_
  extern f_status_t f_environment_exists(const f_string_static_t name);
#endif // _di_f_environment_exists_

/**
 * Get a single environment variable.
 *
 * The variable is copied into a new dynamically allocated string and is safe to alter.
 *
 * @param name
 *   The name of the environment variable to get.
 *   The name string must not contain the '=' character.
 *   The name must be NULL terminated.
 * @param value
 *   The value associated with name.
 *   The value is be null terminated.
 *   The value is be appended (set value->used to 0 before calling this to fully replace).
 *
 * @return
 *   F_none on success.
 *   F_data_not if name.used is 0.
 *   F_exist_not if name does not exist.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see getenv()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_environment_get_
  extern f_status_t f_environment_get(const f_string_static_t name, f_string_dynamic_t * const value);
#endif // _di_f_environment_get_

/**
 * Get all environment variables.
 *
 * The variables are copied into a new dynamically allocated map and is safe to alter.
 *
 * @param environment
 *   An array of maps containing all available environment variable name and value pairs.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_maps_append().
 *
 * @see f_string_maps_append()
 */
#ifndef _di_f_environment_get_all_
  extern f_status_t f_environment_get_all(f_string_maps_t * const environment);
#endif // _di_f_environment_get_all_

/**
 * Check to see if the environment is secure for calling getenv() safely for "secure execution".
 *
 * This is intended to closely mimic the checks secure_getenv().
 *
 * Any of these conditions must be true for secure environment:
 * - The process' effective UID matches the real UID and the effective GID matches the real GID.
 * - The process has the effective CAP_SETUID set.
 *
 * The documentation for secure_getenv() is unclear on which capabilities are expected to be set.
 * This takes a conservative approach and only returns true for the above mentioned capabilities.
 *
 * @return
 *   F_true if the environment is secure according to the described rules.
 *   F_false if the environment is not secure according to the described rules.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if name is an invalid string.
 *   F_prohibited (with error bit) if the file system does not permit this operation (usually due to the cap_get_proc() call).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_flag()
 * @see cap_get_proc()
 * @see getegid()
 * @see geteuid()
 * @see getgid()
 * @see getuid()
 */
#ifndef _di_f_environment_secure_is_
  extern f_status_t f_environment_secure_is(void);
#endif // _di_f_environment_secure_is_

/**
 * Assign the given value to the named environment variable.
 *
 * If the name does not exist, then it is created.
 *
 * @param name
 *   The name of the environment variable to set.
 *   The name string must not contain the '=' character.
 *   The name must be NULL terminated.
 * @param value
 *   The value to assign to name.
 *   The name must be NULL terminated.
 * @param replace
 *   Set to TRUE to replace value if name already exists.
 *   Set to FALSE to not replace value if name already exists.
 *
 * @return
 *   F_none on success.
 *   F_data_not if name.used is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if name is an invalid string.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see setenv()
 */
#ifndef _di_f_environment_set_
  extern f_status_t f_environment_set(const f_string_static_t name, const f_string_static_t value, const bool replace);
#endif // _di_f_environment_set_

/**
 * Remove the name environment variable.
 *
 * @param name
 *   The name of the environment variable to remove.
 *   The name string must not contain the '=' character.
 *   The name must be NULL terminated.
 *
 * @return
 *   F_none on success.
 *   F_data_not if name.used is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if name is an invalid string.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see unsetenv()
 */
#ifndef _di_f_environment_unset_
  extern f_status_t f_environment_unset(const f_string_static_t name);
#endif // _di_f_environment_unset_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_environment_h
