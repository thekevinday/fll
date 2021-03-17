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
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/type_array.h>
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_compare()
 */
#ifndef _di_f_capability_compare_
  extern f_status_t f_capability_compare(const f_capability_t capability1, const f_capability_t capability2, int *flags);
#endif // _di_f_capability_compare_

/**
 * Copy an internally represented capability into an externally represented capability.
 *
 * @param capability
 *   The (internal) capability the (external) capability is copied from.
 * @param max
 *   The the maximum buffer length (in bytes) allowed in the (external) capability.
 *   Use f_capability_size() to determine the maximum size required to hold capability.
 * @param external
 *   The (external) capability the (internal) capability is copied to.
 * @param size
 *   (optional) The size (in bytes) copied into the (external) capability.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_range_not (with error bit) on out of range when processing (external) capability.
 *
 *   F_failure (with error bit) on failure to get size.
 *
 * @see cap_copy_ext()
 */
#ifndef _di_f_capability_copy_external_
  extern f_status_t f_capability_copy_external(const f_capability_t capability, const ssize_t max, void *external, ssize_t *size);
#endif // _di_f_capability_copy_external_

/**
 * Copy an externally represented capability into an internally represented capability.
 *
 * @param external
 *   A pointer to user allocated memory representing the (external) capability.
 *   This must have been popilated by cap_copy_ext() or f_capability_copy_external().
 * @param capability
 *   The (internal) capability the (external) capability is copied into.
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_range_not (with error bit) on out of range when processing (external) capability.
 *
 *   F_failure (with error bit) on failure to get size.
 *
 * @see cap_copy_int()
 */
#ifndef _di_f_capability_copy_internal_
  extern f_status_t f_capability_copy_internal(const void *external, f_capability_t *capability);
#endif // _di_f_capability_copy_internal_

/**
 * Free the capability structure.
 *
 * @param capability
 *   The capability to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory (which doesn't make sense here but man page includes this).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_free()
 */
#ifndef _di_f_capability_delete_
  extern f_status_t f_capability_delete(f_capability_t *capability);
#endif // _di_f_capability_delete_

/**
 * Duplicate (copy) the capability structure.
 *
 * @param source
 *   The capability to duplicate.
 * @param destination
 *   The capability to copy to.
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
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
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
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
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_from_text()
 */
#ifndef _di_f_capability_from_text_
  extern f_status_t f_capability_from_text(const f_string_t text, f_capability_t *capability);
#endif // _di_f_capability_from_text_

/**
 * Get the capability of a file represented by a file path.
 *
 * @param path
 *   The file path.
 * @param capability
 *   The retrieved capability.
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_descriptor_not (with error bit) if the file descriptor is invalid.
 *   F_directory_not (with error bit) if a directory containing the file does not exist.
 *   F_file_found_not (with error bit) if file was not found.
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_name_not (with error bit) if the file name is too long.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *   F_supported_not (with error bit) if the filesystem does not support this operation.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_get_file()
 */
#ifndef _di_f_capability_get_file_
  extern f_status_t f_capability_get_file(const f_string_t path, f_capability_t *capability);
#endif // _di_f_capability_get_file_

/**
 * Get the capability of a file represented by a file descriptor.
 *
 * @param descriptor
 *   The file descriptor.
 * @param capability
 *   The retrieved capability.
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_descriptor_not (with error bit) if the file descriptor is invalid.
 *   F_directory_not (with error bit) if a directory containing the file does not exist.
 *   F_file_found_not (with error bit) if file was not found.
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_name_not (with error bit) if the file name is too long.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *   F_supported_not (with error bit) if the filesystem does not support this operation.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_get_fd()
 */
#ifndef _di_f_capability_get_file_descriptor_
  extern f_status_t f_capability_get_file_descriptor(const int descriptor, f_capability_t *capability);
#endif // _di_f_capability_get_file_descriptor_

/**
 * Initialize the capability structure.
 *
 * @param capability
 *   The capability to initialize.
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on failure to initialize.
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_known_not (with error bit) if the code is unknown to the current system.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
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
 * @param capability
 *   The determined capability.
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
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
 * @param id
 *   The process ID (pid) to get capabilities of.
 *   If set to 0, then get the capabilities of the calling process (similar to f_capability_process_get()).
 * @param capability
 *   The determined capability.
 *   This must be freed via f_capability_delete() when finished with.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_set_proc()
 */
#ifndef _di_f_capability_process_set_
  extern f_status_t f_capability_process_set(const f_capability_t capability);
#endif // _di_f_capability_process_set_

/**
 * Set the capability of a file represented by a file path.
 *
 * @param path
 *   The file path.
 * @param capability
 *   The capability to set.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_descriptor_not (with error bit) if the file descriptor is invalid.
 *   F_directory_not (with error bit) if a directory containing the file does not exist.
 *   F_file_found_not (with error bit) if file was not found.
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_name_not (with error bit) if the file name is too long.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *   F_supported_not (with error bit) if the filesystem does not support this operation.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_set_file()
 */
#ifndef _di_f_capability_set_file_
  extern f_status_t f_capability_set_file(const f_string_t path, const f_capability_t capability);
#endif // _di_f_capability_set_file_

/**
 * Set the capability of a file represented by a file descriptor.
 *
 * @param descriptor
 *   The file descriptor.
 * @param capability
 *   The capability to set.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_descriptor_not (with error bit) if the file descriptor is invalid.
 *   F_directory_not (with error bit) if a directory containing the file does not exist.
 *   F_file_found_not (with error bit) if file was not found.
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_name_not (with error bit) if the file name is too long.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *   F_supported_not (with error bit) if the filesystem does not support this operation.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_set_fd()
 */
#ifndef _di_f_capability_set_file_descriptor_
  extern f_status_t f_capability_set_file_descriptor(const int descriptor, const f_capability_t capability);
#endif // _di_f_capability_set_file_descriptor_

/**
 * Get the total length (in bytes) the capability would take up when converted to external representation.
 *
 * @param capability
 *   The capability to get size of.
 * @param size
 *   The size of the external representation of capability.
 *   Size may be set to -1 on error.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_range_not (with error bit) on out of range when processing size.
 *
 *   F_failure (with error bit) on failure to get size.
 *
 * @see cap_size()
 */
#ifndef _di_f_capability_size_
  extern f_status_t f_capability_size(const f_capability_t capability, ssize_t *size);
#endif // _di_f_capability_size_

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
 * Check if the capabilitiy code is supported, using special libcap function/macro.
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
 * Check if capabilities support ambient, using special libcap function/macro.
 *
 * @param code
 *   The capability code.
 *
 * @return
 *   TRUE if ambient is supported.
 *   FALSE otherwise.
 *
 * @see CAP_AMBIENT_SUPPORTED()
 */
#ifndef _di_f_capability_supported_ambient_
  extern bool f_capability_supported_ambient();
#endif // _di_f_capability_supported_ambient_

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
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   F_failure (with error bit) on any other failure.
 *
 *   Errors (with error bit) from f_string_dynamic_resize().
 *
 * @see cap_free()
 * @see cap_to_name()
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_capability_to_name_
  extern f_status_t f_capability_to_name(const f_capability_value_t code, f_string_dynamic_t *name);
#endif // _di_f_capability_to_name_

/**
 * Convert the capability to a human-readable NULL terminated string.
 *
 * This will append the string to text.
 *
 * @param capability
 *   The capability code.
 * @param text
 *   The determined human-readable NULL terminated string.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   F_failure (with error bit) on any other failure.
 *
 *   Errors (with error bit) from f_string_dynamic_resize().
 *
 * @see cap_free()
 * @see cap_to_text()
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_capability_to_text_
  extern f_status_t f_capability_to_text(const f_capability_t capability, f_string_dynamic_t *text);
#endif // _di_f_capability_to_text_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_capability_h
