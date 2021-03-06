/**
 * FLL - Level 0
 *
 * Project: Environment
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides environment processing functionality, such as environment variable handling.
 */
#ifndef _F_environment_h
#define _F_environment_h

// libc includes
#include <stdio.h>
#include <sys/stat.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// fll-0 environment includes
#include <fll/level_0/environment-common.h>

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
  extern f_status_t f_environment_clear();
#endif // _di_f_environment_clear_

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
 *   The value will not be null terminated.
 *   The value will be appended (set value->used to 0 to replace).
 *
 * @return
 *   F_true on success and environment variable exists.
 *   F_false on success and environment variable does not exist.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see getenv()
 */
#ifndef _di_f_environment_exists_
  extern f_status_t f_environment_exists(const f_string_t name);
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
 *   The value will not be null terminated.
 *   The value will be appended (set value->used to 0 to replace).
 *
 * @return
 *   F_none on success.
 *   F_exist_not if name does not exist.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 * @see getenv()
 */
#ifndef _di_f_environment_get_
  extern f_status_t f_environment_get(const f_string_t name, f_string_dynamic_t *value);
#endif // _di_f_environment_get_

/**
 * Get a single environment variable.
 *
 * The variable is copied into a new dynamically allocated string and is safe to alter.
 *
 * @param name
 *   The name of the environment variable to get.
 *   The name string must not contain the '=' character.
 *   The name need not be NULL terminated.
 * @param value
 *   The value associated with name.
 *   The value will not be null terminated.
 *   The value will be appended (set value->used to 0 to replace).
 *
 * @return
 *   F_none on success.
 *   F_data_not if name.used is 0.
 *   F_exist_not if name does not exist.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 * @see getenv()
 */
#ifndef _di_f_environment_get_dynamic_
  extern f_status_t f_environment_get_dynamic(const f_string_static_t name, f_string_dynamic_t *value);
#endif // _di_f_environment_get_dynamic_

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
 *
 *   F_valid_not (with error bit) if name is an invalid string.
 *   F_memory_not (with error bit) on out of memory.
 *   F_failure (with error bit) on any other error.
 *
 * @see setenv()
 */
#ifndef _di_f_environment_set_
  extern f_status_t f_environment_set(const f_string_t name, const f_string_t value, const bool replace);
#endif // _di_f_environment_set_

/**
 * Assign the given value to the named environment variable.
 *
 * If the name does not exist, then it is created.
 *
 * @param name
 *   The name of the environment variable to set.
 *   The name string must not contain the '=' character.
 *   The name need not be NULL terminated.
 * @param value
 *   The value to assign to name.
 *   The value need not be NULL terminated.
 * @param replace
 *   Set to TRUE to replace value if name already exists.
 *   Set to FALSE to not replace value if name already exists.
 *
 * @return
 *   F_none on success.
 *   F_data_not if name.used is 0.
 *
 *   F_valid_not (with error bit) if name is an invalid string.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see setenv()
 */
#ifndef _di_f_environment_set_dynamic_
  extern f_status_t f_environment_set_dynamic(const f_string_static_t name, const f_string_static_t value, const bool replace);
#endif // _di_f_environment_set_dynamic_

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
 *
 *   F_valid_not (with error bit) if name is an invalid string.
 *   F_memory_not (with error bit) on out of memory.
 *   F_failure (with error bit) on any other error.
 *
 * @see unsetenv()
 */
#ifndef _di_f_environment_unset_
  extern f_status_t f_environment_unset(const f_string_t name);
#endif // _di_f_environment_unset_

/**
 * Remove the name environment variable.
 *
 * @param name
 *   The name of the environment variable to remove.
 *   The name string must not contain the '=' character.
 *   The name need not be NULL terminated.
 *
 * @return
 *   F_none on success.
 *
 *   F_valid_not (with error bit) if name is an invalid string.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see unsetenv()
 */
#ifndef _di_f_environment_unset_dynamic_
  extern f_status_t f_environment_unset_dynamic(const f_string_static_t name);
#endif // _di_f_environment_unset_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_environment_h
