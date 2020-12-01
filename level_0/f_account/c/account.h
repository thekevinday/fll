/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides account related functionality (users, groups, roles, etc..).
 *
 * @todo POSIX as of POSIX.1-2001, at least getpwnam() does not call "not found" an error.
 *       For now, using getpwnam_r() in place of getpwnam() (and similar) seems the safest way to avoid this bad design.
 */
#ifndef _F_account_h
#define _F_account_h

// libc includes
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

// fll-0 account includes
#include <level_0/account-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the group account id by the group name.
 *
 * @param name
 *   The group name.
 * @param id
 *   The id associated with the given name.
 *
 * @return
 *   F_none on success.
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_exist_non if no group by that name exists.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other failure.
 *
 * @see getgrnam_r()
 */
#ifndef _di_f_account_id_group_by_name_
  extern f_return_status f_account_id_group_by_name(const f_string_t name, gid_t *id);
#endif // _di_f_account_id_group_by_name_

/**
 * Get the user account id by the user name.
 *
 * @param name
 *   The user name.
 * @param id
 *   The id associated with the given name.
 *
 * @return
 *   F_none on success.
 *   F_buffer_too_small (with error bit) if the buffer is too small to store the account data.
 *   F_exist_non if no user by that name exists.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other failure.
 *
 * @see getpwnam_r()
 */
#ifndef _di_f_account_id_user_by_name_
  extern f_return_status f_account_id_user_by_name(const f_string_t name, uid_t *id);
#endif // _di_f_account_id_user_by_name_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_h
