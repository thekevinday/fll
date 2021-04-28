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
 *
 * The libcap documentation claims that the Linux kernel fails to honor the  POSIX semantics for setting capabilities and securebits in the presence of pthreads.
 * This is because changing capability sets, by default, only affects the running thread.
 * The libcap documentation further claims that "To be meaningfully secure, however, the capability sets should be mirrored by all threads...".
 * This is untrue and should be considered with caution (for example, a init program (like sysvinit) may want to run different threads with different capabilities).
 * The libcap povides a separate libray "libpsx", for threads and then suggests linking with "-lcap -lpsx -lpthread --wrap=pthread_create" to "work-around" the perceived limitation.
 * Use such a work-around with caution.
 * This project makes no assumptions that all threads must share capabilities.
 * This project instead recommends explicitly setting the capabilities for each thread (when capabilities change, then change all appropriate threads).
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
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>

// fll-0 capability includes
#include <fll/level_0/capability-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the ambient capability.
 *
 * @param value
 *   The capability value.
 * @param ambient
 *   The retrieved ambient value.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the system does not support ambient capabilities.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_set_ambient()
 */
#ifndef _di_f_capability_ambient_get_
  extern f_status_t f_capability_ambient_get(const f_capability_value_t value, int *ambient);
#endif // _di_f_capability_ambient_get_

/**
 * Reset the ambient capability.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_reset_ambient()
 */
#ifndef _di_f_capability_ambient_reset_
  extern f_status_t f_capability_ambient_reset();
#endif // _di_f_capability_ambient_reset_

/**
 * Set the ambient capability.
 *
 * @param value
 *   The capability value.
 * @param value_flag
 *   The capability flag value.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the filesystem does not permit this operation.
 *
 *   F_failure (with error bit) on any other failure.
 *
 * @see cap_set_ambient()
 */
#ifndef _di_f_capability_ambient_set_
  extern f_status_t f_capability_ambient_set(const f_capability_value_t value, const f_capability_flag_value_t value_flag);
#endif // _di_f_capability_ambient_set_

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
 * Copy the capability structure.
 *
 * @param source
 *   The capability to copy from.
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
#ifndef _di_f_capability_copy_
  extern f_status_t f_capability_copy(const f_capability_t source, f_capability_t *destination);
#endif // _di_f_capability_copy_

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
#ifndef _di_f_capability_file_descriptor_get_
  extern f_status_t f_capability_file_descriptor_get(const int descriptor, f_capability_t *capability);
#endif // _di_f_capability_file_descriptor_get_

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
#ifndef _di_f_capability_file_descriptor_set_
  extern f_status_t f_capability_file_descriptor_set(const int descriptor, const f_capability_t capability);
#endif // _di_f_capability_file_descriptor_set_

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
#ifndef _di_f_capability_file_get_
  extern f_status_t f_capability_file_get(const f_string_t path, f_capability_t *capability);
#endif // _di_f_capability_file_get_

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
#ifndef _di_f_capability_file_set_
  extern f_status_t f_capability_file_set(const f_string_t path, const f_capability_t capability);
#endif // _di_f_capability_file_set_

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
 * Set the group IDs.
 *
 * This is the same as setuid(), except:
 * 1) Helps ensure the correct effective capability is used to perform the operation.
 * 2) All "effective" capabilities are lowered after this call.
 *
 * @param id_group
 *   The group ID (as in setgid()).
 * @param total
 *   The total number of groups in id_groups.
 * @param id_groups
 *   The array of supplementary group IDs (as in setgroups()).
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
 * @see cap_setgroups()
 * @see setgid()
 * @see setgroups()
 */
#ifndef _di_f_capability_groups_set_
  extern f_status_t f_capability_groups_set(const gid_t id_group, const size_t total, const gid_t id_groups[]);
#endif // _di_f_capability_groups_set_

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
 * Get the mode for the current process.
 *
 * @param mode
 *   The capability mode.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_mode()
 */
#ifndef _di_f_capability_mode_get_
  extern f_status_t f_capability_mode_get(f_capability_mode_t *mode);
#endif // _di_f_capability_mode_get_

/**
 * Get the name of the mode.
 *
 * @param mode
 *   The capability mode.
 * @param name
 *   The name of the mode.
 *   This is a NULL terminated string.
 *   This is not an allocated string.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_mode()
 */
#ifndef _di_f_capability_mode_get_name_
  extern f_status_t f_capability_mode_get_name(const f_capability_mode_t mode, f_string_constant_t *name);
#endif // _di_f_capability_mode_get_name_

/**
 * Set the mode for the current process.
 *
 * @param mode
 *   The capability mode.
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
 * @see cap_set_mode()
 */
#ifndef _di_f_capability_mode_set_
  extern f_status_t f_capability_mode_set(const f_capability_mode_t mode);
#endif // _di_f_capability_mode_set_

/**
 * Get the namespace owner for the current process.
 *
 * @param capability
 *   The capability.
 * @param id_user
 *   The ID of the user.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_owner()
 */
#ifndef _di_f_capability_owner_get_
  extern f_status_t f_capability_owner_get(const f_capability_t capability, uid_t *id_user);
#endif // _di_f_capability_owner_get_

/**
 * Set the namespace owner for the current process.
 *
 * @param capability
 *   The capability.
 * @param id_user
 *   The ID of the user.
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
 *   F_failure (with error bit) on any other error.
 *
 *   Note: the return codes may not make sense.
 *         the documentation for cap_set_owner() designates them as the return codes.
 *         however, it is suspected that this is not the case.
 *         For consistency with the documentation, return the codes anyway.
 *
 * @see cap_set_owner()
 */
#ifndef _di_f_capability_owner_set_
  extern f_status_t f_capability_owner_set(const f_capability_t capability, const uid_t id_user);
#endif // _di_f_capability_owner_set_

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
 * Get the security bits for the current process.
 *
 * @param bits
 *   The security bits.
 *
 * @return
 *   F_none on success.
 *
 *   F_implemented_not (with error bit) if this function is not available (due to not having libcap support compiled in).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see cap_get_secbits()
 */
#ifndef _di_f_capability_security_bits_get_
  extern f_status_t f_capability_security_bits_get(f_capability_bits_t *bits);
#endif // _di_f_capability_security_bits_get_

/**
 * Set the security bits for the current process.
 *
 * @param bits
 *   The security bits.
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
 * @see cap_set_secbits()
 */
#ifndef _di_f_capability_security_bits_set_
  extern f_status_t f_capability_security_bits_set(const f_capability_bits_t bits);
#endif // _di_f_capability_security_bits_set_

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

/**
 * Set the user ID.
 *
 * This is the same as setuid(), except:
 * 1) Helps ensure the correct effective capability is used to perform the operation.
 * 2) Preserves availability of permitted capabilities after the user ID changes.
 * 3) All "effective" capabilities are lowered after this call.
 *
 * @param id_user
 *   The ID of the user.
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
 * @see cap_setuid()
 * @see setuid()
 */
#ifndef _di_f_capability_user_set_
  extern f_status_t f_capability_user_set(const uid_t id_user);
#endif // _di_f_capability_user_set_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_capability_h
