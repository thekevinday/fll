/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides account related functionality (users, groups, roles, etc..).
 *
 * POSIX as of POSIX.1-2001, at least getpwnam() does not call "not found" an error.
 * This uses getpwnam_r() in place of getpwnam() (and similar) as the safest way to avoid this bad design.
 */
#ifndef _F_account_h
#define _F_account_h

// Libc includes.
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// FLL-0 account includes.
#include <fll/level_0/account/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the user account by the user id.
 *
 * @param id
 *   The id of the user.
 * @param account
 *   This is replaced with by the account information.
 *   All strings will be NULL terminated.
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see getpwuid_r()
 */
#ifndef _di_f_account_by_id_
  extern f_status_t f_account_by_id(const uid_t id, f_account_t *account);
#endif // _di_f_account_by_id_

/**
 * Get the user account by the user name.
 *
 * @param name
 *   The user name.
 *   The name must be NULL terminated.
 * @param account
 *   This is replaced with by the account information.
 *   All strings will be NULL terminated.
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see getpwnam_r()
 */
#ifndef _di_f_account_by_name_
  extern f_status_t f_account_by_name(const f_string_t name, f_account_t *account);
#endif // _di_f_account_by_name_

/**
 * Get the account group id by the group name.
 *
 * @param name
 *   The group name.
 *   The name must be NULL terminated.
 * @param id
 *   The id associated with the given name.
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see getgrnam_r()
 */
#ifndef _di_f_account_group_id_by_name_
  extern f_status_t f_account_group_id_by_name(const f_string_t name, gid_t *id);
#endif // _di_f_account_group_id_by_name_

/**
 * Get the account group name by the group id.
 *
 * @param id
 *   The id of the group.
 * @param name
 *   This is replaced with by the group name.
 *   The name will be NULL terminated.
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see getgrgid_r()
 */
#ifndef _di_f_account_group_name_by_id_
  extern f_status_t f_account_group_name_by_id(const gid_t id, f_string_dynamic_t *name);
#endif // _di_f_account_group_name_by_id_

/**
 * Get the user account id by the user name.
 *
 * @param name
 *   The user name.
 *   The name must be NULL terminated.
 * @param id
 *   The id associated with the given name.
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see getpwnam_r()
 */
#ifndef _di_f_account_id_by_name_
  extern f_status_t f_account_id_by_name(const f_string_t name, uid_t *id);
#endif // _di_f_account_id_by_name_

/**
 * Get the user account name by the user id.
 *
 * @param id
 *   The id of the user.
 * @param name
 *   This is replaced with by the user name.
 *   The name will be NULL terminated.
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see getpwuid_r()
 */
#ifndef _di_f_account_name_by_id_
  extern f_status_t f_account_name_by_id(const uid_t id, f_string_dynamic_t *name);
#endif // _di_f_account_name_by_id_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_h
