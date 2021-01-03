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

  #define f_macro_account_t_delete(status, account) \
    f_macro_string_dynamic_t_delete(status, account.home); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, account.label); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, account.name); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, account.password); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, account.shell);

  #define f_macro_account_t_destroy(status, account) \
    f_macro_string_dynamic_t_destroy(status, account.home); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, account.label); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, account.name); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, account.password); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, account.shell);

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

  #define f_macro_accounts_t_clear(accounts) \
    accounts.array = 0; \
    accounts.size = 0; \
    accounts.used = 0;

  #define f_macro_accounts_new(status, accounts, length) \
    f_macro_accounts_clear(accounts) \
    status = f_memory_new((void **) & accounts.array, sizeof(f_account_t), length); \
    if (status == F_none) { \
      accounts.size = length; \
      accounts.used = 0; \
    }

  #define f_macro_string_accounts_t_delete(status, accounts) \
    status = F_none; \
    accounts.used = accounts.size; \
    while (accounts.used) { \
      accounts.used--; \
      f_macro_account_t_delete(status, accounts.array[accounts.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & accounts.array, sizeof(f_account_t), accounts.size); \
    if (status == F_none) accounts.size = 0;

  #define f_macro_string_accounts_t_destroy(status, accounts) \
    status = F_none; \
    accounts.used = accounts.size; \
    while (accounts.used) { \
      accounts.used--; \
      f_macro_account_t_destroy(status, accounts.array[accounts.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & accounts.array, sizeof(f_account_t), accounts.size); \
    if (status == F_none) accounts.size = 0;

  #define f_macro_string_accounts_t_delete_simple(accounts) \
    accounts.used = accounts.size; \
    while (accounts.used) { \
      accounts.used--; \
      f_macro_account_t_delete_simple(accounts.array[accounts.used]); \
    } \
    f_memory_delete((void **) & accounts.array, sizeof(f_account_t), accounts.size); \
    accounts.size = 0;

  #define f_macro_string_accounts_t_destroy_simple(accounts) \
    accounts.used = accounts.size; \
    while (accounts.used > 0) { \
      accounts.used--; \
      f_macro_account_t_destroy_simple(accounts.array[accounts.used]); \
    } \
    f_memory_destroy((void **) & accounts.array, sizeof(f_account_t), accounts.size); \
    accounts.size = 0;

  #define f_macro_string_accounts_t_resize(status, accounts, new_length) \
    status = F_none; \
    if (new_length < accounts.size) { \
      for (f_array_length_t _macro__i = accounts.size - new_length; _macro__i < accounts.size; _macro__i++) { \
        f_macro_account_t_delete(status, accounts.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & accounts.array, sizeof(f_account_t), accounts.size, new_length); \
    if (status == F_none) { \
      accounts.size = new_length; \
      if (accounts.used > accounts.size) accounts.used = new_length; \
    }

  #define f_macro_string_accounts_t_adjust(status, accounts, new_length) \
    status = F_none; \
    if (new_length < accounts.size) { \
      for (f_array_length_t _macro__i = accounts.size - new_length; _macro__i < accounts.size; _macro__i++) { \
        f_macro_account_t_destroy(status, accounts.array[_macro__i], f_account_t); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & accounts.array, sizeof(f_account_t), accounts.size, new_length); \
    if (status == F_none) { \
      accounts.size = new_length; \
      if (accounts.used > accounts.size) accounts.used = new_length; \
    }
#endif // _di_f_accounts_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_common_h
