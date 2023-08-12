/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by account related functionality.
 *
 * This is auto-included by account.h and should not need to be explicitly included.
 */
#ifndef _F_account_common_h
#define _F_account_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Custom defines for f_account.
 *
 * F_account_pwd_length_fallback_*:
 *   - first:  provide a fallback max length for when sysconf(_SC_GETPW_R_SIZE_MAX) return -1 (aka: infinite).
 *   - second: provide a fallback max length for when F_account_pwd_length_fallback_first_d is too small.
 */
#ifndef _di_f_account_d_
  #define F_account_pwd_length_fallback_first_d  8192
  #define F_account_pwd_length_fallback_second_d 32767
#endif // _di_f_account_d_

/**
 * Provide a complete standard password account structure.
 *
 * Properties:
 *   - id_user:  The user ID.
 *   - id_group: The group ID.
 *   - home:     The user's home directory.
 *   - label:    The user's display name (gecos).
 *   - name:     The user's account name.
 *   - password: The user's password.
 *   - shell:    The user's shell program.
 */
#ifndef _di_f_account_t_
  typedef struct {
    uid_t id_user;
    gid_t id_group;

    f_string_dynamic_t home;
    f_string_dynamic_t label;
    f_string_dynamic_t name;
    f_string_dynamic_t password;
    f_string_dynamic_t shell;
  } f_account_t;

  #define f_account_t_initialize { \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize \
  }

  #define macro_f_account_t_clear(account) \
    account.id_user = 0; \
    account.id_group = 0; \
    macro_f_account_t_clear(account.home); \
    macro_f_account_t_clear(account.label); \
    macro_f_account_t_clear(account.name); \
    macro_f_account_t_clear(account.password); \
    macro_f_account_t_clear(account.shell);

  #define macro_f_account_t_delete_simple(accounts)  f_account_delete(&accounts);
  #define macro_f_account_t_destroy_simple(accounts) f_account_destroy(&accounts);
#endif // _di_f_account_t_

/**
 * An array of accounts.
 *
 * Properties:
 *   - array: The array of accounts.
 *   - size:  Total amount of space available.
 *   - used:  Total number of space used.
 */
#ifndef _di_f_accounts_t_
  typedef struct {
    f_account_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_accounts_t;

  #define f_accounts_t_initialize { 0, 0, 0 }

  #define macro_f_accounts_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_accounts_t_initialize_2(array, length) { array, length, length }

  #define macro_f_accounts_t_clear(accounts) macro_f_memory_structures_clear(accounts)
#endif // _di_f_accounts_t_

/**
 * An array of f_accounts_t.
 *
 * Properties:
 *   - array: The array of f_accounts_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_accounts_t_
  typedef struct {
    f_accounts_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_accountss_t;

  #define f_accountss_t_initialize { 0, 0, 0 }

  #define macro_f_accountss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_accountss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_accountss_t_clear(accountss) macro_f_memory_structures_clear(accountss)
#endif // _di_f_accountss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_common_h
