/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides capability related functionality.
 *
 * Capabilities are POSIX compliant as of POSIX 1003.1e (as a draft).
 * Because it is only in POSIX as a draft, they are available via libcap instead of libc.
 * Special linking is necessary and this project provides a wrapper that makes capabilities easier to work with whether libcap (and therefore capabilities) is available or not.
 *
 * When _di_libcap_ is defined (-D_di_libcap_) then many of the structures and functions provided here are stubs.
 * Compilations with _di_libcap_ will not be binary compatible with compilations without _di_libcap_.
 */
#ifndef _F_capability_h
#define _F_capability_h

// libc includes
#include <string.h>
#include <sys/types.h>

#ifndef _di_libcap_
  #include <sys/capability.h>
#endif // _di_libcap_

// fll-0 includes
#include <level_0/type.h>
#include <level_0/type_array.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

// fll-0 capability includes
#include <level_0/capability-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Clear the capability structure.
 *
 * @param capability
 *   The capability to clear.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure to duplicate.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_clear()
 */
#ifndef _di_f_capability_clear_
  extern f_status_t f_capability_clear(f_capability_t *capability);
#endif // _di_f_capability_clear_

/**
 * Clear the capability flag.
 *
 * @param flag
 *   The flag to clear.
 * @param capability
 *   The capability to clear the flag of.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure to duplicate.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_clear_flag()
 */
#ifndef _di_f_capability_clear_flag_
  extern f_status_t f_capability_clear_flag(const f_capability_flag_t flag, f_capability_t *capability);
#endif // _di_f_capability_clear_flag_

/**
 * Compare two capability structures.
 *
 * @param capability1
 *   The first capability to compare.
 * @param capability2
 *   The second capability to compare.
 * @param flags
 *   (optional) This represents which of the flags that differ on miss.
 *   Set to NULL to not use.
 *
 * @return
 *   F_equal_to on match.
 *   F_equal_to_not on miss.
 *   F_failure (with error bit) on failure to duplicate.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_compare()
 */
#ifndef _di_f_capability_compare_
  extern f_status_t f_capability_compare(const f_capability_t capability1, const f_capability_t capability2, int *flags);
#endif // _di_f_capability_compare_

/**
 * Free the capability structure.
 *
 * @param capability
 *   The capability to delete.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure to free memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_free()
 */
#ifndef _di_f_capability_delete_
  extern f_status_t f_capability_delete(f_capability_t *capability);
#endif // _di_f_capability_delete_

/**
 * Duplicate (copy) the capability structure.
 *
 * Be sure to call f_capability_delete() when finished.
 *
 * @param source
 *   The capability to duplicate.
 * @param destination
 *   The capability to copy to.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure to duplicate.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_dup()
 */
#ifndef _di_f_capability_duplicate_
  extern f_status_t f_capability_duplicate(const f_capability_t source, f_capability_t *destination);
#endif // _di_f_capability_duplicate_

/**
 * Get the value of a flag from the capability structure.
 *
 * @param capability
 *   The capability to get the code of.
 * @param code
 *   The capability code to get the flag of.
 * @param flag
 *   The flag of the capability code to get the value of.
 * @param enabled
 *   The determined capability code flag value.
 *   This is TRUE when the flag is enabled and FALSE otherwise.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure to free memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_get_flag()
 */
#ifndef _di_f_capability_flag_get_
  extern f_status_t f_capability_flag_get(const f_capability_t capability, const f_capability_value_t code, const f_capability_flag_t flag, f_capability_flag_value_t *enabled);
#endif // _di_f_capability_flag_get

/**
 * Set the value of a flags from the capability structure.
 *
 * @param flag
 *   The flag of the capability code to set the value of.
 * @param enabled
 *   The capability code flag value to set.
 *   This is TRUE when the flag is enabled and FALSE otherwise.
 * @param codes
 *   An array of codes to set the capability flag value of.
 * @param capability
 *   The capability to set the flag of.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure to free memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_set_flag()
 */
#ifndef _di_f_capability_flag_set_
  extern f_status_t f_capability_flag_set(const f_capability_flag_t flag, const f_capability_flag_value_t enabled, const f_int32s_t codes, f_capability_t *capability);
#endif // _di_f_capability_flag_set_

/**
 * Get the capability code from the capability name.
 *
 * @param name
 *   The name of the capability (must be all lower case).
 * @param code
 *   (optional) The determined code.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success and name is known.
 *   F_known_not on success and name is unknown (and no code is provided).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_from_name()
 */
#ifndef _di_f_capability_from_name_
  extern f_status_t f_capability_from_name(const f_string_t name, f_capability_value_t *code);
#endif // _di_f_capability_from_name_

/**
 * Get the capability represented by the given string.
 *
 * @param text
 *   The human-readable NULL terminated string representing the capabilities (such as "cap_chown+ep").
 * @param capability
 *   The determined capabilities.
 *   This must be freed via f_capability_delete() when finished with it.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_from_text()
 */
#ifndef _di_f_capability_from_text_
  extern f_status_t f_capability_from_text(const f_string_t text, f_capability_t *capability);
#endif // _di_f_capability_from_text_

/**
 * Initialize the capability structure.
 *
 * Be sure to call f_capability_delete() when finished.
 *
 * @param capability
 *   The capability to initialize.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure to initialize.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 * @see cap_init()
 */
#ifndef _di_f_capability_initialize_
  extern f_status_t f_capability_initialize(f_capability_t *capability);
#endif // _di_f_capability_initialize_

/**
 * Drop the bound for the process.
 *
 * This will lower the specified bounding set capability if appropriate permission exist (the  prevailing  effective capability set must have a raised CAP_SETPCAP).
 *
 * @param code
 *   The capability code to get the bound for.
 * @param bound
 *   The determined bound value.
 *
 * @return
 *   F_none on success.
 *   F_supported_not if the given code is not supported by the current system.
 *   F_known_not (with error bit) if the code is unknown.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_drop_bound()
 */
#ifndef _di_f_capability_process_bound_drop_
  extern f_status_t f_capability_process_bound_drop(f_capability_value_t code, int *bound);
#endif // _di_f_capability_process_bound_drop_

/**
 * Get the bound for the process.
 *
 * @param code
 *   The capability code to get the bound for.
 * @param bound
 *   The determined bound value.
 *
 * @return
 *   F_none on success.
 *   F_supported_not if the given code is not supported by the current system.
 *   F_known_not (with error bit) if the code is unknown.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_bound()
 */
#ifndef _di_f_capability_process_bound_get_
  extern f_status_t f_capability_process_bound_get(f_capability_value_t code, int *bound);
#endif // _di_f_capability_process_bound_get_

/**
 * Get the capability for the current process.
 *
 * Be sure to call f_capability_delete() when finished.
 *
 * @param capability
 *   The determined capability.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_proc()
 */
#ifndef _di_f_capability_process_get_
  extern f_status_t f_capability_process_get(f_capability_t *capability);
#endif // _di_f_capability_process_get_

/**
 * Get the capability for the process represented by the given PID.
 *
 * Be sure to call f_capability_delete() when finished.
 *
 * @param id
 *   The process ID (pid) to get capabilities of.
 * @param capability
 *   The determined capability.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_pid()
 */
#ifndef _di_f_capability_process_get_by_id_
  extern f_status_t f_capability_process_get_by_id(const pid_t id, f_capability_t *capability);
#endif // _di_f_capability_process_get_by_id_

/**
 * Set the capability for the current process.
 *
 * @param capability
 *   The capability to assign.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if system does not support a capability code specified.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_set_proc()
 */
#ifndef _di_f_capability_process_set_
  extern f_status_t f_capability_process_set(const f_capability_t capability);
#endif // _di_f_capability_process_set_

/**
 * Check if capabilities are supported.
 *
 * @return
 *   TRUE if supported.
 *   FALSE otherwise.
 */
#ifndef _di_f_capability_supported_
  extern bool f_capability_supported();
#endif // _di_f_capability_supported_

/**
 * Check if capabilities are supported.
 *
 * @param code
 *   The capability code.
 *
 * @return
 *   TRUE if the code is supported.
 *   FALSE otherwise.
 *
 * @see CAP_IS_SUPPORTED()
 */
#ifndef _di_f_capability_supported_code_
  extern bool f_capability_supported_code(f_capability_value_t code);
#endif // _di_f_capability_supported_code_

/**
 * Convert the capability code to a name (string).
 *
 * @param code
 *   The capability code.
 * @param name
 *   The determined name.
 *   The name is appended into this variable.
 *   This is not NULL terminated.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_free()
 * @see cap_to_name()
 */
#ifndef _di_f_capability_to_name_
  extern f_status_t f_capability_to_name(const f_capability_value_t code, f_string_dynamic_t *name);
#endif // _di_f_capability_to_name_

/**
 * Convert the capability to a human-readable NULL terminated string.
 *
 * @param capability
 *   The capability code.
 * @param text
 *   The determined human-readable NULL terminated string.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *   F_supported_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_free()
 * @see cap_to_text()
 */
#ifndef _di_f_capability_to_text_
  extern f_status_t f_capability_to_text(const f_capability_t capability, f_string_dynamic_t *text);
#endif // _di_f_capability_to_text_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_capability_h
