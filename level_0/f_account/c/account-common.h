/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * f_account_pwd_length_fallback_first: provide a fallback max length for when sysconf(_SC_GETPW_R_SIZE_MAX) return -1 (aka: infinite).
 * f_account_pwd_length_fallback_second: provide a fallback max length for when f_account_pwd_length_fallback_first is too small.
 */
#ifndef _di_f_account_defines_
  #define f_account_pwd_length_fallback_first  8192
  #define f_account_pwd_length_fallback_second 32767
#endif // _di_f_account_defines_

/**
 * Provide a complete standard password account structure.
 *
 * id_user:  The user ID.
 * id_group: The group ID.
 * home:     The user's home directory.
 * label:    The user's display name (gecos).
 * name:     The user's account name.
 * password: The user's password.
 * shell:    The user's shell program.
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

  #define f_account_t_initialize { 0, 0, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define f_macro_account_t_clear(account) \
    account.id_user = 0; \
    account.id_group = 0; \
    f_macro_account_t_clear(account.home); \
    f_macro_account_t_clear(account.label); \
    f_macro_account_t_clear(account.name); \
    f_macro_account_t_clear(account.password); \
    f_macro_account_t_clear(account.shell);

  #define f_macro_account_t_delete_simple(account) \
    f_macro_string_dynamic_t_delete_simple(account.home); \
    f_macro_string_dynamic_t_delete_simple(account.label); \
    f_macro_string_dynamic_t_delete_simple(account.name); \
    f_macro_string_dynamic_t_delete_simple(account.password); \
    f_macro_string_dynamic_t_delete_simple(account.shell);

  #define f_macro_account_t_destroy_simple(account) \
    f_macro_string_dynamic_t_destroy_simple(account.home); \
    f_macro_string_dynamic_t_destroy_simple(account.label); \
    f_macro_string_dynamic_t_destroy_simple(account.name); \
    f_macro_string_dynamic_t_destroy_simple(account.password); \
    f_macro_string_dynamic_t_destroy_simple(account.shell);
#endif // _di_f_account_t_

/**
 * An array of accounts.
 *
 * array: the array of accounts.
 * size: total amount of space available.
 * used: total number of space used.
 */
#ifndef _di_f_accounts_t_
  typedef struct {
    f_account_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_accounts_t;

  #define f_accounts_t_initialize { 0, 0, 0 }

  #define f_macro_accounts_t_clear(accounts) f_macro_memory_structure_clear(accounts)

  #define f_macro_string_accounts_t_resize(status, accounts, length) f_macro_memory_structure_resize(status, values, sizeof(f_account_t), length)
  #define f_macro_string_accounts_t_adjust(status, accounts, length) f_macro_memory_structure_adjust(status, values, sizeof(f_account_t), length)

  #define f_macro_string_accounts_t_delete_simple(accounts)  f_macro_memory_structure_delete_simple(values, sizeof(f_account_t), 0)
  #define f_macro_string_accounts_t_destroy_simple(accounts) f_macro_memory_structure_destroy_simple(values, sizeof(f_account_t), 0)

  #define f_macro_string_accounts_t_increase(status, values)            f_macro_memory_structure_increase(status, values, f_account_t)
  #define f_macro_string_accounts_t_increase_by(status, values, amount) f_macro_memory_structure_increase_by(status, values, f_account_t, amount)
  #define f_macro_string_accounts_t_decrease_by(status, values, amount) f_macro_memory_structure_decrease_by(status, values, f_account_t, amount)
  #define f_macro_string_accounts_t_decimate_by(status, values, amount) f_macro_memory_structure_decimate_by(status, values, f_account_t, amount)
#endif // _di_f_accounts_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_common_h
