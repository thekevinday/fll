/**
 * FLL - Level 0
 *
 * Project: Environment
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides environment processing functionality, such as environment variable handling.
 */
#ifndef _PRIVATE_F_environment_h
#define _PRIVATE_F_environment_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 * @see f_environment_get()
 * @see f_environment_get_dynamic()
 */
#if !defined(_di_f_environment_get_) || !defined(_di_f_environment_get_dynamic_)
  extern f_status_t private_f_environment_get(const f_string_t name, f_string_dynamic_t *value) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_environment_get_) || !defined(_di_f_environment_get_dynamic_)

/**
 * Assign the given value to the named environment variable.
 *
 * If the name does not exist, then it is created.
 *
 * @param name
 *   The name of the environment variable to set.
 *   The name string must not contain the '=' character.
 * @param value
 *   The value to assign to name.
 * @param replace
 *   Set to TRUE to replace value if name already exists.
 *   Set to FALSE to not replace value if name already exists.
 *
 * @return
 *   F_none on success.
 *   F_valid_not (with error bit) if name is an invalid string.
 *   F_memory_not (with error bit) on out of memory.
 *   F_failure (with error bit) on any other error.
 *
 * @see f_environment_set()
 * @see f_environment_set_dynamic()
 */
#if !defined(_di_f_environment_set_) || !defined(_di_f_environment_set_dynamic_)
  extern f_status_t private_f_environment_set(const f_string_t name, const f_string_t value, const bool replace) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_environment_set_) || !defined(_di_f_environment_set_dynamic_)

/**
 * Remove the name environment variable.
 *
 * @param name
 *   The name of the environment variable to remove.
 *   The name string must not contain the '=' character.
 *
 * @return
 *   F_none on success.
 *   F_valid_not (with error bit) if name is an invalid string.
 *   F_memory_not (with error bit) on out of memory.
 *   F_failure (with error bit) on any other error.
 *
 * @see f_environment_unset()
 * @see f_environment_unset_dynamic()
 */
#if !defined(_di_f_environment_unset_) || !defined(_di_f_environment_unset_dynamic_)
  extern f_status_t private_f_environment_unset(const f_string_t name) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_environment_unset_) || !defined(_di_f_environment_unset_dynamic_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_environment_h
